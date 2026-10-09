#include "game/obj_flyer_collision.h"

// TObjFlyerCollision::CreateInstance, the static factory the PS2 build names
// CreateInstance__18TObjFlyerCollisionFv: the same new-expression as
// rel/flyer_collision_create.cpp, returning the object. It sits apart from
// that factory in each of the five modules, with the class's other functions
// between them.

TObjFlyerCollision* TObjFlyerCollision::CreateInstance()
{
	return new TObjFlyerCollision(lbl_8042C10C);
}
