// s04FloatingPathCreate, the factory rel/s04_floating_path_register.cpp puts
// in the editor record for TObjS04FloatWay, in stage03D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// Unless the collision base already has a shape, it takes the module's. The
// shape is then sized from the placement's parameter block: half its three
// extents, and centred half the last two along y and z with x at 0, the
// module's constants 0.5 and 0. The halfword at 0xB8 comes from the module's
// data.

#define S04_FLOATING_PATH_CTOR inline
#include "src/rel/s04_floating_path_class.inc"

extern "C" void s04FloatingPathCreate(void)
{
	new TObjS04FloatWay(lbl_8042C110);
}
