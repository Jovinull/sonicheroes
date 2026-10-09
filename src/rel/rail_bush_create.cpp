// railbushCreate, the factory rel/railbush_register.cpp puts in the editor
// record for TObjRailBush, in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what gives
// the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp has
// the long form. The class has the collision block as its third base, as in
// rel/warp_create.cpp, though nothing here gives it a shape.
//
// It is rel/tenkyu_create.cpp for "dobj07_bush.dff": clone the module's model
// and, unless it is already in, add it to the world slot the model file names,
// reaching the model file through a local pointer.

#define RAIL_BUSH_CTOR inline
#include "src/rel/rail_bush_class.inc"

extern "C" void railbushCreate(void)
{
	new TObjRailBush(lbl_8042C110);
}
