// ironballCreate, the factory rel/ironball_register.cpp puts in the editor
// record for TObjIronball.
//
// It is the same 164 instructions in the thirteen stage modules that share the
// engine core, at their own address in each, so each module's splits.txt names
// its own range.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// The placement's parameter block picks a single ball (0) or a chain, and gives
// two sizes. A single ball clones the module's first model; a chain clones the
// second once, the third twice and the fourth twice, and lights and places all
// five; the PS2 build names that step CloneClump. Outside the editor the
// collision takes one shape of the module's table for a ball and four for a
// chain.
//
// The light bits are read through a volatile access for the reason written up
// in rel/itembaloon_create.cpp; the zero is the module's own float, read as an
// external.

#define IRONBALL_CTOR inline
#include "src/rel/ironball_class.inc"

extern "C" void ironballCreate(void)
{
	new TObjIronball(lbl_8042C110);
}
