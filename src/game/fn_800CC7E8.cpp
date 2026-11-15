#include "types.h"

// Starts the stage music on the first stream (lbl_8042B624[0]) when play-mode flag 22 is set:
// stream mode 1 (lbl_8042C470) hands over to fn_800CA85C; a stream with neither mode 2 (+0x2A)
// nor a file name (+0x50) is left alone. A playing stream (+0x3C not 0 or 5) is stopped first;
// the stream becomes state 1 with +0x2C = 2, its loop point (+0x40) comes from the name table
// lbl_80254FD8 (minutes * 100 + seconds, 0 when unlisted), the volume is applied paused and, in
// mode 2, the name table's selected entry (+0x1 into +0x0) starts seamlessly, else the file name
// starts (ADXT_StartFname). The last volume (+0x38) follows +0x34. HYPOTHESIS: names UNKNOWN.

struct StreamNames800CC7E8 {
	s8 current; // 0x0
	s8 next;    // 0x1
	u8 pad2[0x4 - 0x2];
	s32 samples;         // 0x4
	void* adxt;          // 0x8
	char names[8][0x20]; // 0xC
};

struct Stream800CC7E8 {
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
	StreamNames800CC7E8* names; // 0x4C
	char name[0x20];            // 0x50
};

struct Loop800CC7E8 {
	const char* name; // 0x0
	s16 minutes;      // 0x4
	s16 seconds;      // 0x6
};

struct PlayMode800CC7E8 {
	s8 flags[44];
};

extern "C" {
extern PlayMode800CC7E8* lbl_8042C180;
extern Stream800CC7E8* lbl_8042B624[2];
extern s8 lbl_8042C470;
extern Loop800CC7E8 lbl_80254FD8[];
unsigned long strlen(const char* s);
int strcmp(const char* a, const char* b);
void fn_800CA85C(void);
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
static inline void StopStream(Stream800CC7E8* stream)
{
	ADXT_Stop(stream->adxt);
	ADXT_Pause(stream->adxt, 0);
	StreamNames800CC7E8* names = stream->names;
	if (names != NULL) {
		ADXT_ResetEntry(names->adxt);
		names->current = -1;
	}
	stream->state = 0;
	stream->flags &= ~1;
}

static inline s32 LoopPoint(const char* name)
{
	for (Loop800CC7E8* loop = lbl_80254FD8; loop->minutes >= 0; loop++) {
		if (strcmp(loop->name, name) == 0) {
			return loop->seconds + loop->minutes * 100;
		}
	}
	return 0;
}

extern "C" void fn_800CC7E8(void)
{
	if (lbl_8042C180->flags[22] == 0) {
		return;
	}
	if (lbl_8042C470 == 1) {
		fn_800CA85C();
		return;
	}
	Stream800CC7E8* stream = lbl_8042B624[0];
	if (stream == NULL) {
		return;
	}
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
	StreamNames800CC7E8* names;
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
