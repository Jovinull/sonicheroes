// trainappearCreate, the factory rel/trainappear_register.cpp puts in the editor record for
// TObjTrainAppear, in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// A placed collision volume. The radius of the module's shape comes from the
// first word of the placement's parameter block. The parameter block pointer is
// read first, before the class name, which is where the original loads it.

#define TRAIN_APPEAR_CTOR inline
#include "src/rel/train_appear_class.inc"

extern "C" void trainappearCreate(void)
{
	new TObjTrainAppear(lbl_8042C110);
}
