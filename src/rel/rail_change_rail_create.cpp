// railchangerailCreate, the factory rel/railchangerail_register.cpp puts in the
// editor record for TObjRailChangeRail, in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what gives
// the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp has
// the long form. The class has the collision block as its third base, as in
// rel/warp_create.cpp, and it takes the module's shape through InitShare, as
// rel/key_object_create.cpp does.
//
// It is rel/tenkyu_create.cpp for "obj0708_changeRail.dff": clone the module's
// model and, unless it is already in, add it to the world slot the model file
// names, reaching the model file through a local pointer.

#define RAIL_CHANGE_RAIL_CTOR inline
#include "src/rel/rail_change_rail_class.inc"

extern "C" void railchangerailCreate(void)
{
	new TObjRailChangeRail(lbl_8042C110);
}
