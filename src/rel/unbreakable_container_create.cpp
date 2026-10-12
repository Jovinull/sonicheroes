// unbreakableContainerCreate, the factory the editor record for
// TObjContUnbreakable points at.
//
// It is the same 71 instructions in the thirteen stage modules that share the
// engine core, at their own address in each, so each module's splits.txt names
// its own range.
//
// It is rel/iron_container_create.cpp with material 2, its own model and
// debris, and one step more: once the collision base has a shape, bit 0x4000 of
// the shape's attributes is cleared, which is what keeps this one from
// breaking.
//
// The light bits are read through a volatile access for the reason written up
// in rel/itembaloon_create.cpp.

#define UNBREAKABLE_CONTAINER_CTOR inline
#include "src/rel/unbreakable_container_class.inc"

extern "C" void unbreakableContainerCreate(void)
{
	new TObjContUnbreakable(lbl_8042C110);
}
