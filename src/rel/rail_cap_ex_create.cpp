// railcapexCreate, the factory rel/railcapex_register.cpp puts in the editor
// record for TObjRailCapEx, in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. The class has the collision block as its third base, as
// in rel/warp_create.cpp, though nothing here gives it a shape.
//
// It is rel/tenkyu_create.cpp for two models at once: the module keeps two
// model files for "dobj0708_railcap_ex.dff" side by side, and each one is
// cloned into its own part and added once to the world slot its file names.

#define RAIL_CAP_EX_CTOR inline
#include "src/rel/rail_cap_ex_class.inc"

extern "C" void railcapexCreate(void)
{
	new TObjRailCapEx(lbl_8042C110);
}
