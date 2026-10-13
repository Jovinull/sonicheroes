#include "types.h"

// TObjCage's destructor (the PS2 build's TObjCage::__dt). It kills the
// paralysis effect if it has one, frees both models (DestroyClump, inlined) and
// ends the placement when its condition asks for it.

#include "src/rel/cage_class.inc"

TObjCage::~TObjCage()
{
	if (paralysis != NULL) {
		paralysis->Signal |= 1;
		paralysis = NULL;
	}
	DestroyClump();
	if (TstConditionBit(0x10000)) {
		SetEnd();
	}
}
