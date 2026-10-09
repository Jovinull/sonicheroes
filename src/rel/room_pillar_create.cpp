// roompillarCreate, the factory rel/roompillar_register.cpp puts in the editor
// record for TObjRoomPillar, in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what gives
// the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp has
// the long form. The class has the collision block as its third base, as in
// rel/warp_create.cpp, and it takes the module's shape through InitShare, as
// rel/key_object_create.cpp does.
//
// It is rel/tenkyu_create.cpp for "dobj08_roompillar.dff": clone the module's
// model and, unless it is already in, add it to the world slot the model file
// names, reaching the model file through a local pointer.

#define ROOM_PILLAR_CTOR inline
#include "src/rel/room_pillar_class.inc"

extern "C" void roompillarCreate(void)
{
	new TObjRoomPillar(lbl_8042C110);
}
