#include "types.h"

// ObjBigringSubstance::Disp (the PS2 build's name, by its place in the PS2
// order; bigRingsElementDisp here): a ring shown (states 1 and 2) draws its
// clump.

typedef struct RpClump RpClump;

typedef struct BigRingsElement {
	u8 unk00[0x8];  // 0x00
	s32 state;      // 0x08
	u8 unk0C[0x1C]; // 0x0C
	RpClump* clump; // 0x28
} BigRingsElement;

extern "C" void fn_8014FF2C(RpClump* clump);

extern "C" void bigRingsElementDisp(BigRingsElement* element)
{
	switch (element->state) {
		case 1:
		case 2:
			fn_8014FF2C(element->clump);
			break;
	}
}
