// bigdiceCreate, the factory the editor record for TObjBigDice points at, in
// stage05D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. The class has the collision block as its third base, as
// in rel/warp_create.cpp.
//
// The dice clones the four models the module keeps for
// "stg05_pn_ksaikoro01.dff" and its siblings into four parts, none of them in
// the world yet, and then applies its placement through its own EditOnChange,
// a virtual call through the first vtable.

#define BIG_DICE_CTOR inline
#include "src/rel/big_dice_class.inc"

extern "C" void bigdiceCreate(void)
{
	new TObjBigDice(lbl_8042C110);
}
