// TObjBobJumpCollision's destructor, out of line: it deletes the two material
// records and destroys the two clumps the jump keeps, each only when it is
// there, clearing the clump pointers. The class is in
// game/obj_bob_jump_collision.h.

#include "game/obj_bob_jump_collision.h"

extern "C" void fn_80150958(RpClump* clump);

TObjBobJumpCollision::~TObjBobJumpCollision()
{
	if (unkEC != NULL) {
		delete unkEC;
	}
	if (unkF0 != NULL) {
		delete unkF0;
	}
	if (unkE4 != NULL) {
		fn_80150958(unkE4);
		unkE4 = NULL;
	}
	if (unkE8 != NULL) {
		fn_80150958(unkE8);
		unkE8 = NULL;
	}
}
