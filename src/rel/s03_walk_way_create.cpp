// s03WalkWayCreate, the factory the editor record for TObjS03WalkWay points
// at, in stage03D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// In the editor an all-zero box in the placement's parameter block becomes
// 150 by 10 by 50, the module's constants. The walkway's direction is the
// parameter block's first float along x, turned by the placement's angle in
// the order Z, X, Y on the matrix stack. It then sets up its collision through
// InitColli, the class's own virtual: the PS2 build lists it after
// EditOnChange in the vtable slots this one calls at 0x38, so it is declared
// first here. The parameter block pointer is read first, before the class
// name.

#define S03_WALK_WAY_CTOR inline
#include "src/rel/s03_walk_way_class.inc"

extern "C" void s03WalkWayCreate(void)
{
	new TObjS03WalkWay(lbl_8042C110);
}
