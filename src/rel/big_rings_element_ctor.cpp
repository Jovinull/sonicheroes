#include "types.h"

// The constructor of one ring of the big ring group (the PS2 build's
// ObjBigringSubstance; bigRingsElementCtor here), which the group's
// constructor hands to __construct_new_array. The ring has two empty virtual
// bases (at 0x30 and 0x31), whose pointers only a complete object sets up;
// then it is not passed yet (0x24), in mode 1, with a clone of the ring model.

typedef struct RpClump RpClump;

typedef struct BigRingsElement {
	void* base30;   // 0x00
	void* base31;   // 0x04
	s32 mode;       // 0x08
	u8 unk0C[0x18]; // 0x0C
	s32 unk24;      // 0x24
	RpClump* clump; // 0x28
	u8 unk2C[0x4];  // 0x2C
	u8 vbases[2];   // 0x30
} BigRingsElement;

extern "C" RpClump* bigRingsModel;
extern "C" RpClump* fn_80150588(RpClump* clump);

extern "C" BigRingsElement* bigRingsElementCtor(BigRingsElement* element, s16 complete)
{
	if (complete != 0) {
		element->base30 = &element->vbases[0];
		element->base31 = &element->vbases[1];
	}
	element->unk24 = 0;
	element->mode  = 1;
	element->clump = fn_80150588(bigRingsModel);
	return element;
}
