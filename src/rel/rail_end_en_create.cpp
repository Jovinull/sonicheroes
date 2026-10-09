// railendenCreate, the factory the editor record for TObjRailEndEn points at,
// in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0` (here r28);
// rel/sample1_create.cpp has the long form. The class has the collision block
// as its third base, as in rel/warp_create.cpp.
//
// It is rel/rail_cap_ex_create.cpp for skinned models: each of the module's four
// model files for "dobj0708_railend_en.dff" is cloned into its own part, the
// clone's animation hierarchy (fn_800F3074, as game/effect/eff_crash3d.cpp
// uses it) kept beside it, the clone added once to the world slot its file
// names, and the hierarchy set up (fn_8013F3A4) when there is one. These model
// files carry four more words than the plain ones.

#define RAIL_END_EN_CTOR inline
#include "src/rel/rail_end_en_class.inc"

extern "C" void railendenCreate(void)
{
	new TObjRailEndEn(lbl_8042C110);
}
