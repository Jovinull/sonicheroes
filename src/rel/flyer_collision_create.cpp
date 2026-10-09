#include "game/obj_flyer_collision.h"

// flyerColObjectCreate, the factory the editor record for TObjFlyerCollision
// points at; the class is in game/obj_flyer_collision.h.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form.

extern "C" void flyerColObjectCreate(void)
{
	new TObjFlyerCollision(lbl_8042C10C);
}
