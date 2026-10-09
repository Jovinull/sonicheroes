// destructrailCreate, the factory the editor record for TObjDestructRail
// points at, in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp, and
// it takes the module's shape through InitShare, as rel/key_object_create.cpp
// does.

#define DESTRUCT_RAIL_CTOR inline
#include "src/rel/destruct_rail_class.inc"

extern "C" void destructrailCreate(void)
{
	new TObjDestructRail(lbl_8042C110);
}
