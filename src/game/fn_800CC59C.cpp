#include "types.h"

// Starts the stage music `name` and remembers it (HYPOTHESIS: the track fn_800CC354 resumes):
// when play-mode flag 22 is set and there is a first stream (lbl_8042B624[0]), a given name is
// passed to the sound controller lbl_803E774C and copied into the stream's file name (+0x50);
// the name is always copied into the saved name (+0x70). A stream with neither mode 2 (+0x2A)
// nor a file name is left alone; otherwise a playing stream (+0x3C not 0 or 5) is stopped, the
// stream becomes state 1 with +0x2C = 2, its loop point (+0x40) comes from the name table
// lbl_80254FD8, the volume is applied paused and, in mode 2, the name table's selected entry
// starts seamlessly, else the file name starts (ADXT_StartFname). HYPOTHESIS: names UNKNOWN.

struct StreamNames800CC59C {
	s8 current; // 0x0
	s8 next;    // 0x1
	u8 pad2[0x4 - 0x2];
	s32 samples;         // 0x4
	void* adxt;          // 0x8
	char names[8][0x20]; // 0xC
};

struct Stream800CC59C {
	u8 pad0[0x29];
	s8 state;     // 0x29
	s8 mode;      // 0x2A
	u8 flags;     // 0x2B
	s8 unknown2C; // 0x2C
	u8 pad2D[0x34 - 0x2D];
	s32 volume;     // 0x34
	s32 lastVolume; // 0x38
	s32 playState;  // 0x3C
	s32 loopPoint;  // 0x40
	void* adxt;     // 0x44
	u8 pad48[0x4C - 0x48];
	StreamNames800CC59C* names; // 0x4C
	char name[0x20];            // 0x50
	char saved[0x20];           // 0x70
};

struct Loop800CC59C {
	const char* name; // 0x0
	s16 minutes;      // 0x4
	s16 seconds;      // 0x6
};

struct PlayMode800CC59C {
	s8 flags[44];
};

extern "C" {
extern PlayMode800CC59C* lbl_8042C180;
extern Stream800CC59C* lbl_8042B624[2];
extern u8 lbl_803E774C[];
extern Loop800CC59C lbl_80254FD8[];
unsigned long strlen(const char* s);
int strcmp(const char* a, const char* b);
void* memset(void* dst, int value, unsigned long size);
char* strcpy(char* dst, const char* src);
void* fn_80116D2C(void* controller);
void fn_80116E3C(void* sound, const char* name);
void ADXT_Stop(void* adxt);
void ADXT_Pause(void* adxt, s32 pause);
void ADXT_ResetEntry(void* adxt);
void ADXT_SetOutVol(void* adxt, s32 volume);
void ADXT_EntryFname(void* adxt, const char* name);
void ADXT_SetSeamlessLp(void* adxt, s32 loop);
void ADXT_StartSeamless(void* adxt);
s32 ADXT_GetNumSmpl(void* adxt);
void ADXT_StartFname(void* adxt, const char* name);
}

// See fn_800CB95C.
static inline void StopStream(Stream800CC59C* stream)
{
	ADXT_Stop(stream->adxt);
	ADXT_Pause(stream->adxt, 0);
	StreamNames800CC59C* names = stream->names;
	if (names != NULL) {
		ADXT_ResetEntry(names->adxt);
		names->current = -1;
	}
	stream->state = 0;
	stream->flags &= ~1;
}

static inline s32 LoopPoint(const char* name)
{
	for (Loop800CC59C* loop = lbl_80254FD8; loop->minutes >= 0; loop++) {
		if (strcmp(loop->name, name) == 0) {
			return loop->seconds + loop->minutes * 100;
		}
	}
	return 0;
}

extern "C" void fn_800CC59C(const char* name)
{
	Stream800CC59C* stream = lbl_8042B624[0];

	if (lbl_8042C180->flags[22] == 0) {
		return;
	}
	if (stream == NULL) {
		return;
	}
	if (name != NULL) {
		fn_80116E3C(fn_80116D2C(lbl_803E774C), name);
		memset(stream->name, 0, sizeof(stream->name));
		strcpy(stream->name, name);
	}
	memset(stream->saved, 0, sizeof(stream->saved));
	strcpy(stream->saved, name);
	if (stream->mode != 2 && strlen(stream->name) == 0) {
		return;
	}
	switch (stream->playState) {
		case 0:
		case 5:
			break;
		default:
			StopStream(stream);
			break;
	}
	stream->state     = 1;
	stream->unknown2C = 2;
	stream->loopPoint = LoopPoint(stream->name);
	void* adxt        = stream->adxt;
	ADXT_SetOutVol(adxt, stream->volume);
	ADXT_Pause(adxt, 1);
	StreamNames800CC59C* names;
	if (stream->mode == 2 && (names = stream->names) != NULL) {
		s8 next = names->next;
		if (next >= 0 && next <= 8) {
			if (names->current < 0) {
				names->current = next;
			}
			names->next = next;
		}
		if (names->current >= 0) {
			ADXT_EntryFname(names->adxt, names->names[names->current]);
			ADXT_SetSeamlessLp(names->adxt, 0);
			ADXT_StartSeamless(names->adxt);
			names->samples = ADXT_GetNumSmpl(names->adxt);
		}
	} else {
		ADXT_StartFname(adxt, stream->name);
	}
	stream->lastVolume = stream->volume;
}
