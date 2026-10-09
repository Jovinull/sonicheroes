// TObjEnemyStg27Cloud::Create, the static factory the PS2 build names
// Create__19TObjEnemyStg27CloudFRC19sObjEnemyStg27Cloud, in stage26D and
// stage27D: the cloud layers of rel/enemy_cloud_create.cpp, with their heights
// handed in by the caller instead of fixed.
//
// The allocation is a real new-expression of the C++ class with its
// constructor inlined; rel/sample1_create.cpp has the long form. Single base,
// no placement, and the task at lbl_8042C10C.
//
// ResetVariable places the two layers from the module's two vector constants
// and clears the angle and both clumps; the constructor then takes the layers'
// heights from its parameter block, and CloneClump and SetPosition are
// TObjEnemyCloud's.

#define ENEMY_STG27_CLOUD_CTOR inline
#include "src/rel/enemy_stg27_cloud_class.inc"

void TObjEnemyStg27Cloud::Create(const sObjEnemyStg27Cloud& param)
{
	new TObjEnemyStg27Cloud(lbl_8042C10C, param);
}
