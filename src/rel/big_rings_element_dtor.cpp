#include "types.h"

// The destructor of one ring of the big ring group (bigRingsElementDtor here),
// handed to __destroy_new_array by rel/big_rings_dtor.cpp. It frees the ring's
// clump and, when asked to, the ring itself.

typedef struct RpClump RpClump;

typedef struct BigRingsElement {
	u8 unk00[0x28]; // 0x00
	RpClump* clump; // 0x28
} BigRingsElement;

extern "C" void fn_80150958(RpClump* clump);
extern "C" void __dl__FPv(void* memory);

extern "C" BigRingsElement* bigRingsElementDtor(BigRingsElement* element, s16 flags)
{
	if (element != NULL) {
		if (element->clump != NULL) {
			fn_80150958(element->clump);
			element->clump = NULL;
		}
		if (flags > 0) {
			__dl__FPv(element);
		}
	}
	return element;
}
