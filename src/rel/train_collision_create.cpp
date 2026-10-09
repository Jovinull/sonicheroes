// traincollisionCreate, the factory rel/traincollision_register.cpp puts in the editor record for
// TObjTrainCollision, in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// A placed collision volume. The radius of the module's shape comes from the
// first word of the placement's parameter block. The parameter block pointer is
// read together with the position, from the one load of the placement.

#define TRAIN_COLLISION_CTOR inline
#include "src/rel/train_collision_class.inc"

extern "C" void traincollisionCreate(void)
{
	new TObjTrainCollision(lbl_8042C110);
}
