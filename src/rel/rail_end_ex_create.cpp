// railendexCreate, the factory rel/railendex_register.cpp puts in the editor
// record for TObjRailEndEx, in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what gives
// the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp has
// the long form. The class has the collision block as its third base, as in
// rel/warp_create.cpp.
//
// It is rel/rail_cap_ex_create.cpp for 2 models, starting with
// "dobj0708_railend_ex.dff": each is cloned into its own part and added once to
// the world slot its file names.

#define RAIL_END_EX_CTOR inline
#include "src/rel/rail_end_ex_class.inc"

extern "C" void railendexCreate(void)
{
	new TObjRailEndEx(lbl_8042C110);
}
