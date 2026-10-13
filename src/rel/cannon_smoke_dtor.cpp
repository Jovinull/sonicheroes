#include "types.h"

// TObjCannonSmoke's destructor (the PS2 build's TObjCannonSmoke::__dt): it
// frees the effect model.

#include "src/rel/cannon_smoke_class.inc"

extern "C" void fn_80150958(RpClump* clump);

TObjCannonSmoke::~TObjCannonSmoke()
{
	if (clump != NULL) {
		fn_80150958(clump);
		clump = NULL;
	}
}
