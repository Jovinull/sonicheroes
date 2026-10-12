// unbrBobcontObjectCreate, the factory the editor record for
// TObjBobcontUnbreakable points at.
//
// It is the same 78 instructions in the thirteen stage modules that share the
// engine core, at their own address in each, so each module's splits.txt names
// its own range.
//
// It is rel/wood_container_create.cpp on the bobsleigh crate base: material 2,
// the module's own model and debris, light set 0x10 in stages 0x1A to 0x1C and
// the placement's light everywhere else. The stage is named three times in the
// test for the reason written up there, and the light bits are read through a
// volatile access for the reason written up in rel/itembaloon_create.cpp.

#define UNBR_BOBCONT_CTOR inline
#include "src/rel/unbr_bobcont_class.inc"

extern "C" void unbrBobcontObjectCreate(void)
{
	new TObjBobcontUnbreakable(lbl_8042C110);
}
