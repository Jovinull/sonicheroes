// s12doorColliObjectCreate, the factory the editor record for TObjS12DoorRangeColli points
// at, in stage11D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// The placement gives the position and, in the first word of its parameter
// block, the radius the module's shape takes. The first range collision of a
// placement also leaves a one-word record on it, built with the global operator
// new and cleared.

#define S12_DOOR_RANGE_COLLI_CTOR inline
#include "src/rel/s12_door_range_colli_class.inc"

extern "C" void s12doorColliObjectCreate(void)
{
	new TObjS12DoorRangeColli(lbl_8042C110);
}
