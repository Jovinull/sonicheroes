#include "types.h"

// Applies a sound output mode change: stops the first music stream, then the second (and, outside
// stream mode 1, wakes a first stream waiting in state 6 into state 5) and the two effect streams
// as fn_800CB95C does, sets mono output (ADXT_SetOutputMono) for mode 1 and stereo otherwise, and
// restarts the music (fn_800CD138) when the play mode exists and there was a first stream.
// HYPOTHESIS: called from fn_800B41A0 with the sound mode.
// NonMatching (12 words, registers only): retail keeps each stop's name-table pointer in r26;
// MWCC uses r27..r29. Grouping the second stream and the effects into an inline fixed the other
// registers; a shared name variable and reloading the field did not help (see fn_800CB95C).

struct StreamNames800CA52C {
	s8 unknown0; // 0x0
	u8 pad1[0x8 - 0x1];
	void* adxt; // 0x8
};

struct Stream800CA52C {
	u8 pad0[0x29];
	s8 state; // 0x29
	s8 mode;  // 0x2A
	u8 flags; // 0x2B
	u8 pad2C[0x44 - 0x2C];
	void* adxt; // 0x44
	u8 pad48[0x4C - 0x48];
	StreamNames800CA52C* names; // 0x4C
};

struct Effect800CA52C {
	u8 pad0[0x29];
	s8 state;      // 0x29
	s8 id;         // 0x2A
	u8 flags;      // 0x2B
	s32 unknown2C; // 0x2C
	s32 unknown30; // 0x30
	u8 pad34[0x3C - 0x34];
	void* adxt; // 0x3C
};

extern "C" {
extern Stream800CA52C* lbl_8042B624[2];
extern Effect800CA52C* lbl_8042B634[2];
extern s8 lbl_8042C470;
void ADXT_Stop(void* adxt);
void ADXT_Pause(void* adxt, s32 pause);
void ADXT_ResetEntry(void* adxt);
void ADXT_SetOutputMono(s32 mono);
void fn_800CD138(void);
extern void* lbl_8042C180;
}

static inline void StopStream(Stream800CA52C* stream)
{
	ADXT_Stop(stream->adxt);
	ADXT_Pause(stream->adxt, 0);
	StreamNames800CA52C* names = stream->names;
	if (names != NULL) {
		ADXT_ResetEntry(names->adxt);
		names->unknown0 = -1;
	}
	stream->state = 0;
	stream->flags &= ~1;
}

static inline void StopEffect(Effect800CA52C* effect)
{
	ADXT_Stop(effect->adxt);
	ADXT_Pause(effect->adxt, 0);
	effect->id = effect->unknown30 = effect->unknown2C = -1;
	effect->state                                      = 0;
	effect->flags &= ~1;
}

static inline void StopEffects()
{
	for (s32 i = 0; i < 2; i++) {
		if (lbl_8042B634[i] != NULL) {
			StopEffect(lbl_8042B634[i]);
		}
	}
}

// The second music stream and the effect streams (fn_800CB95C without its first-stream stop).
static inline void StopOthers()
{
	Stream800CA52C* first  = lbl_8042B624[0];
	Stream800CA52C* second = lbl_8042B624[1];
	if (second != NULL) {
		if (lbl_8042C470 == 1) {
			StopStream(second);
		} else {
			StopStream(second);
			if (first != NULL) {
				switch (first->state) {
					case 6:
						first->state = 5;
						break;
				}
			}
		}
	}
	StopEffects();
}

extern "C" void fn_800CA52C(s32 mode)
{
	Stream800CA52C* stream = lbl_8042B624[0];

	if (stream != NULL) {
		StopStream(stream);
	}
	StopOthers();
	switch (mode) {
		case 1:
			ADXT_SetOutputMono(1);
			break;
		default:
			ADXT_SetOutputMono(0);
			break;
	}
	if (lbl_8042C180 != NULL && stream != NULL) {
		fn_800CD138();
	}
}
