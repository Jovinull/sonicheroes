// woodContainerCreate, the factory rel/wood_container_register.cpp puts in the
// editor record for TObjContWood.
//
// It is the same 80 instructions in the thirteen stage modules that share the
// engine core, at their own address in each, so each module's splits.txt names
// its own range.
//
// It is rel/iron_container_create.cpp with material 0, its own model and
// debris, a word from the module for the field at 0xEC, and one difference in
// the lighting: in stages 0x1A to 0x1C the crate takes light set 0x10 instead
// of the one its placement asks for. The test names the stage three times, as
// three equality tests; a local, or a switch, lets the compiler fold them into
// one range check, which the original does not have.
//
// The light bits are read through a volatile access for the reason written up
// in rel/itembaloon_create.cpp.

#define WOOD_CONTAINER_CTOR inline
#include "src/rel/wood_container_class.inc"

extern "C" void woodContainerCreate(void)
{
	new TObjContWood(lbl_8042C110);
}
