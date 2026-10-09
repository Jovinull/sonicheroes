// bumperCreate, the factory the editor record for TObjBumper points at, in
// stage05D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// The bumper clones the four models the module keeps, starting with
// "s05_on_bumper_L.dff", into four parts, takes five of the module's shapes,
// adds only the fourth part to the world slot its file names, applies its
// placement through its own EditOnChange (a virtual call through the first
// vtable) and clears the 0x20 bytes in front of the parts.

#define BUMPER_CTOR inline
#include "src/rel/bumper_class.inc"

extern "C" void bumperCreate(void)
{
	new TObjBumper(lbl_8042C110);
}
