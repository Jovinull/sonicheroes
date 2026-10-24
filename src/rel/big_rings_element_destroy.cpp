#include "types.h"

// ObjBigringSubstance::DestroyClone (the PS2 build's name, by its place in the
// PS2 order; bigRingsElementDestroyClone here): the ring's clump is released.

typedef struct RpClump RpClump;

typedef struct BigRingsElement {
	u8 unk00[0x28]; // 0x00
	RpClump* clump; // 0x28
} BigRingsElement;

extern "C" void fn_80150958(RpClump* clump);

extern "C" void bigRingsElementDestroyClone(BigRingsElement* element)
{
	if (element->clump != NULL) {
		fn_80150958(element->clump);
		element->clump = NULL;
	}
}
