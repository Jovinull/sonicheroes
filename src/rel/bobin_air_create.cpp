// bobinairCreate, the factory rel/bobinair_register.cpp puts in the editor
// record for TObjBobinAir, in stage05D.
//
// The allocation is a real new-expression of the C++ class, which is what gives
// the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp has
// the long form. The class has the collision block as its third base, as in
// rel/warp_create.cpp, and it takes the module's shape through InitShare, as
// rel/key_object_create.cpp does.
//
// It is rel/tenkyu_create.cpp for "s05_on_bobinAir.dff": clone the module's
// model and, unless it is already in, add it to the world slot the model file
// names, reaching the model file through a local pointer. It then raises bit
// 0x40 of the collision's flags and clears a word and eight bytes after the
// clump.

#define BOBIN_AIR_CTOR inline
#include "src/rel/bobin_air_class.inc"

extern "C" void bobinairCreate(void)
{
	new TObjBobinAir(lbl_8042C110);
}
