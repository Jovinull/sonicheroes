// bigslotCreate, the factory rel/bigslot_register.cpp puts in the editor record
// for TObjBigSlot, in stage05D.
//
// The allocation is a real new-expression of the C++ class, which is what gives
// the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp has
// the long form. The class has the collision block as its third base, as in
// rel/warp_create.cpp.
//
// It is rel/rail_cap_ex_create.cpp for 3 models, starting with
// "stg05_on_slot1.dff": each is cloned into its own part and added once to the
// world slot its file names. Three words of each of the three reels after the
// parts are then cleared, and the word in front of them.

#define BIG_SLOT_CTOR inline
#include "src/rel/big_slot_class.inc"

extern "C" void bigslotCreate(void)
{
	new TObjBigSlot(lbl_8042C110);
}
