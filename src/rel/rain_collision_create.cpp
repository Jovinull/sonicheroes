// raincollisionCreate, the factory rel/raincollision_register.cpp puts in the
// editor record for TObjRainCollision, in stage09D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// A placed collision volume: once the collision base has the module's shape,
// the shape's radius is set from the first word of the placement's parameter
// block and the range recomputed. The parameter block pointer is read first,
// before the class name, and kept across the calls.

#define RAIN_COLLISION_CTOR inline
#include "src/rel/rain_collision_class.inc"

extern "C" void raincollisionCreate(void)
{
	new TObjRainCollision(lbl_8042C110);
}
