#include "types.h"

// Stops the ADX streams without resetting them (see fn_800CCEB0, which also clears their
// settings): the second music stream (lbl_8042B624[1]) first, then, outside stream mode 1
// (lbl_8042C470), a first stream waiting in state 6 is set to 5; then the first music stream and
// the two effect streams of lbl_8042B634 (their ids set to -1). A stopped stream is unpaused, its
// name table's entries are reset (ADXT_ResetEntry) and its state and flag 0x1 (+0x2B) cleared.
// HYPOTHESIS: the state names are UNKNOWN.
// NonMatching (12 words, registers only): with the second-stream part and the effect loop as
// inlines only the name-table pointers differ (retail r28/r29, MWCC others); see fn_800CA52C.

struct StreamNames800CB95C {
	s8 unknown0; // 0x0
	u8 pad1[0x8 - 0x1];
	void* adxt; // 0x8
};

struct Stream800CB95C {
	u8 pad0[0x29];
	s8 state; // 0x29
	s8 mode;  // 0x2A
	u8 flags; // 0x2B
	u8 pad2C[0x44 - 0x2C];
	void* adxt; // 0x44
	u8 pad48[0x4C - 0x48];
	StreamNames800CB95C* names; // 0x4C
};

struct Effect800CB95C {
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
extern Stream800CB95C* lbl_8042B624[2];
extern Effect800CB95C* lbl_8042B634[2];
extern s8 lbl_8042C470;
void ADXT_Stop(void* adxt);
void ADXT_Pause(void* adxt, s32 pause);
void ADXT_ResetEntry(void* adxt);
}

static inline void StopStream(Stream800CB95C* stream)
{
	ADXT_Stop(stream->adxt);
	ADXT_Pause(stream->adxt, 0);
	StreamNames800CB95C* names = stream->names;
	if (names != NULL) {
		ADXT_ResetEntry(names->adxt);
		names->unknown0 = -1;
	}
	stream->state = 0;
	stream->flags &= ~1;
}

static inline void StopEffect(Effect800CB95C* effect)
{
	ADXT_Stop(effect->adxt);
	ADXT_Pause(effect->adxt, 0);
	effect->id = effect->unknown30 = effect->unknown2C = -1;
	effect->state                                      = 0;
	effect->flags &= ~1;
}

static inline void StopSecond()
{
	Stream800CB95C* first  = lbl_8042B624[0];
	Stream800CB95C* second = lbl_8042B624[1];

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
}

static inline void StopEffects()
{
	for (s32 i = 0; i < 2; i++) {
		if (lbl_8042B634[i] != NULL) {
			StopEffect(lbl_8042B634[i]);
		}
	}
}

extern "C" void fn_800CB95C(void)
{
	StopSecond();
	if (lbl_8042B624[0] != NULL) {
		StopStream(lbl_8042B624[0]);
	}
	StopEffects();
}
