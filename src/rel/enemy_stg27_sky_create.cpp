// TObjEnemyStg27Sky::Create, the static factory the PS2 build names
// Create__17TObjEnemyStg27SkyFv, in stage26D and stage27D, where the code is
// the same at different addresses. rel/enemy_sky_create.cpp is stage28D's
// TObjEnemySky, the same shape.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. Single base, no placement, and the task at lbl_8042C10C.
//
// ResetVariable copies the position from a vector constant of the module and
// clears the angle; CloneClump and SetPosition are TObjEnemySky's.

#define ENEMY_STG27_SKY_CTOR inline
#include "src/rel/enemy_stg27_sky_class.inc"

void TObjEnemyStg27Sky::Create()
{
	new TObjEnemyStg27Sky(lbl_8042C10C);
}
