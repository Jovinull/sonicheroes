// xxxsignCreate, the factory the editor record for TObjXxxSign points at, in stage05D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. The class has the collision block as its third base, as
// in rel/warp_create.cpp, though nothing here gives it a shape.
//
// It is rel/water_plant_create.cpp for "s05_k_signo.dff": clone the module's model and,
// unless it is already in, add it to the world slot the model file names. The
// model file is reached through a local pointer, which the original keeps in a
// saved register across the clone.

#define XXX_SIGN_CTOR inline
#include "src/rel/xxx_sign_class.inc"

extern "C" void xxxsignCreate(void)
{
	new TObjXxxSign(lbl_8042C110);
}
