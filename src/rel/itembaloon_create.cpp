// itembaloonObjectCreate, the factory rel/itembaloon_register.cpp puts in the
// editor record for TObjItembaloon.
//
// It is the same 99 instructions in the thirteen stage modules that share the
// engine core, at their own address in each, so each module's splits.txt names
// its own range.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// The placement's parameter block holds the item in its first byte and a size
// offset at 4. The balloon clones the module's model, lights it from the
// placement's light bits, and scales the module's collision shape by its size.
//
// The light bits are read through a volatile access. The original loads them
// into a register before it loads the clone for the call, which is what an
// ordinary local gives before copy propagation folds it back into the
// argument; the volatile keeps the load where it is written. It is a
// reconstruction aid, not a claim about the original source.
//
// The two floats are the module's constants 1 and 0, shared with the rest of
// the class's code, so they are read as externals.

#define ITEMBALOON_CTOR inline
#include "src/rel/itembaloon_class.inc"

extern "C" void itembaloonObjectCreate(void)
{
	new TObjItembaloon(lbl_8042C110);
}
