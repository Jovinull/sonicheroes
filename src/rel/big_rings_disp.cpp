#include "types.h"

// The big rings' Disp (bigRingsDisp here): with the game not paused it draws
// each of the three rings that is showing (state 1 or 2).

typedef struct RpClump RpClump;

typedef struct BigRing {
	u8 unk00[0x8];
	s32 state; // 0x08
	u8 unk0C[0x1C];
	RpClump* clump; // 0x28
	u8 unk2C[0x8];
} BigRing; // 0x34

typedef struct BigRings {
	u8 unk00[0x68];
	BigRing* rings; // 0x68
} BigRings;

extern "C" u8* lbl_8042C180;

extern "C" void fn_8014FF2C(RpClump* clump);

extern "C" void bigRingsDisp(BigRings* object)
{
	if ((s8)lbl_8042C180[0x20] == 0) {
		for (int i = 0; i < 3; i++) {
			BigRing* ring = &object->rings[i];

			switch (ring->state) {
				case 1:
				case 2:
					fn_8014FF2C(ring->clump);
					break;
			}
		}
	}
}
