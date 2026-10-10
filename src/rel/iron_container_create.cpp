// ironContainerCreate, the factory rel/iron_container_register.cpp puts in the
// editor record for TObjContIron.
//
// It is the same 65 instructions in the thirteen stage modules that share the
// engine core, at their own address in each, so each module's splits.txt names
// its own range.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. The class adds nothing to TObjContainer: its constructor
// names the class, marks the material, clones the module's model into the
// world, places it, lights it and hands it the iron debris.
//
// The light bits are read through a volatile access for the reason written up
// in rel/itembaloon_create.cpp.

#define IRON_CONTAINER_CTOR inline
#include "src/rel/iron_container_class.inc"

extern "C" void ironContainerCreate(void)
{
	new TObjContIron(lbl_8042C110);
}
