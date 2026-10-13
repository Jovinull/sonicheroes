#include "types.h"

// TObjGoalring::TDisp (the PS2 build's name): with the game not paused and the
// two-part ring shown, it draws the ring's back part with render states 0xA
// and 0xB set to 2 and 0x14 set to 1, putting the three states back after.

#include "src/rel/goal_ring_class.inc"

extern "C" void fn_8014FF2C(RpClump* clump);
extern "C" void fn_80194294(s32 state, void* value);
extern "C" void fn_80194234(s32 state, s32 value);

void TObjGoalring::TDisp()
{
	if (lbl_8042C180[0x20] == 0 && goalRingHasTwoRings()) {
		s32 src;
		s32 dst;
		s32 cull;

		fn_80194294(0xA, &src);
		fn_80194294(0xB, &dst);
		fn_80194294(0x14, &cull);
		fn_80194234(0xA, 2);
		fn_80194234(0xB, 2);
		fn_80194234(0x14, 1);
		fn_8014FF2C(ringBack);
		fn_80194234(0x14, cull);
		fn_80194234(0xA, src);
		fn_80194234(0xB, dst);
	}
}
