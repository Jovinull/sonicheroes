// s23WarpposCreate, the factory rel/s23_warppos_register.cpp puts in the editor
// record for TObjS23WarpPos, in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form.
//
// Each warp position raises its placement by the height in its parameter block
// and joins the end of the chain the class keeps in pTopWarp, the static
// member the PS2 build names; LinkChain is inlined into the constructor here.

#define S23_WARPPOS_CTOR inline
#include "src/rel/s23_warppos_class.inc"

extern "C" void s23WarpposCreate(void)
{
	new TObjS23WarpPos(lbl_8042C110);
}
