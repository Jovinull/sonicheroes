// TObjEnemyCloud::Create, in stage28D: the static factory the PS2 build names
// Create__14TObjEnemyCloudFv, called by the stage's own code. It is the same
// shape as rel/enemy_sky_create.cpp, which shares this class's module data.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. Single base, no placement, and the task at lbl_8042C10C.
//
// ResetVariable places the two cloud layers at heights -500 and -1000, the
// module's constants, and clears the angle and both clumps; CloneClump clones
// the module's second and third models when they are loaded, and SetPosition
// moves each clone's frame to its layer.

#define ENEMY_CLOUD_CTOR inline
#include "src/rel/enemy_cloud_class.inc"

void TObjEnemyCloud::Create()
{
	new TObjEnemyCloud(lbl_8042C10C);
}
