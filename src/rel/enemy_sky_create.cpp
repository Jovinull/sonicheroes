// TObjEnemySky::Create, in stage28D: the static factory the PS2 build names
// Create__12TObjEnemySkyFv, which the stage's own code calls rather than an
// editor record.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. The class has a single base and no placement, so there is
// one vtable store, and it hangs off the task at lbl_8042C10C.
//
// The constructor is the three steps the PS2 build names: ResetVariable clears
// the position and angle, CloneClump clones the module's model when it is
// loaded, and SetPosition moves the clone's frame to the position.

#define ENEMY_SKY_CTOR inline
#include "src/rel/enemy_sky_class.inc"

void TObjEnemySky::Create()
{
	new TObjEnemySky(lbl_8042C10C);
}
