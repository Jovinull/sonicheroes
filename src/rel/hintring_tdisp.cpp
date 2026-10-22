#include "types.h"

// TObjHintRing::TDisp (the PS2 build's name, by its place in the PS2 order):
// unless the game is paused, the ring is drawn with render states 0xA, 0xB
// and 0x14 set to 2, 6 and 1 (the old values kept), then the first two are
// put back, the second model is drawn and the third is put back.

typedef struct RpClump RpClump;

typedef struct HintRing {
	u8 unk00[0x5C];
	RpClump* ring;   // 0x5C
	u8 unk60[0x8];   // 0x60
	RpClump* inside; // 0x68
} HintRing;

extern "C" u8* lbl_8042C180;

extern "C" void fn_80194294(s32 state, s32* value);
extern "C" void fn_80194234(s32 state, s32 value);
extern "C" void fn_8014FF2C(RpClump* clump);

extern "C" void TDisp__12TObjHintRingFv(HintRing* ring)
{
	if ((s8)lbl_8042C180[0x20] == 0) {
		s32 state0A;
		s32 state0B;
		s32 state14;

		fn_80194294(0xA, &state0A);
		fn_80194294(0xB, &state0B);
		fn_80194294(0x14, &state14);
		fn_80194234(0xA, 2);
		fn_80194234(0xB, 6);
		fn_80194234(0x14, 1);
		fn_8014FF2C(ring->ring);
		fn_80194234(0xA, state0A);
		fn_80194234(0xB, state0B);
		fn_8014FF2C(ring->inside);
		fn_80194234(0x14, state14);
	}
}
