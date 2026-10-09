// bigchipCreate, the factory the editor record for TObjBigChip points at, in
// stage05D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. The class has the collision block as its third base, as
// in rel/warp_create.cpp.
//
// It is rel/rail_cap_ex_create.cpp for five models, starting with
// "stg06_on_chip1.dff": each is cloned into its own part and added once to the
// world slot its file names. The chip then applies its placement through its
// own EditOnChange, a virtual call through the first vtable.

#define BIG_CHIP_CTOR inline
#include "src/rel/big_chip_class.inc"

extern "C" void bigchipCreate(void)
{
	new TObjBigChip(lbl_8042C110);
}
