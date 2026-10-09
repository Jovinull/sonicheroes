// s04BallColliCreate, the factory rel/s04_ball_colli_register.cpp puts in the
// editor record for TObjS04BallColli, in stage03D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp, and
// the class adds nothing to its three bases.
//
// A zero radius in the placement's parameter block becomes the module's
// default of 10; the shape takes that radius, and bit 0x40 of the collision's
// flags is cleared. The two floats are the module's constants, read as
// externals.

#define S04_BALL_COLLI_CTOR inline
#include "src/rel/s04_ball_colli_class.inc"

extern "C" void s04BallColliCreate(void)
{
	new TObjS04BallColli(lbl_8042C110);
}
