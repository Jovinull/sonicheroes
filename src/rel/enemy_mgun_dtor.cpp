#include "types.h"

// ENEMY_MGUN's destructor (the PS2 build's ENEMY_MGUN::__dt): it frees the
// flash model; the collision and the object base go with it.

#include "src/rel/enemy_mgun.inc"

extern "C" void fn_80150958(RpClump* clump);

ENEMY_MGUN::~ENEMY_MGUN()
{
	if (clump != NULL) {
		fn_80150958(clump);
		clump = NULL;
	}
}
