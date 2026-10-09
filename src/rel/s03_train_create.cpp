// s03TrainCreate, the factory the editor record for TObjS03Train points at, in
// stage03D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// In the editor an all-zero box in the placement's parameter block becomes
// 100 by 100 by 20, the module's constants. The constructor clears its state,
// and unless the collision base already has a shape it takes the module's,
// sized to the box; that step reads the parameter block again for itself.

#define S03_TRAIN_CTOR inline
#include "src/rel/s03_train_class.inc"

extern "C" void s03TrainCreate(void)
{
	new TObjS03Train(lbl_8042C110);
}
