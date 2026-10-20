#include "types.h"

// TObjWeight's Check_Down (the PS2 build's name; weightCheckDown here) and its
// opposite (weightCheckUp here; the PS2 build has no such member). Both answer
// 0 while the game is paused and 1 for the kinds 0 and 3 (and unknown kinds).
// For the kinds 1 and 4 Down answers whether a player in the active state
// stands under the weight, for 2 and 5 whether any player does; Up answers
// the opposite.

#include "src/rel/weight.inc"

extern "C" u8* lbl_8042C180;

extern "C" s32 weightCheckDown(Weight* object)
{
	if ((s8)lbl_8042C180[0x1F] != 0) {
		return 0;
	}
	switch (object->kind) {
		case 0:
		case 3:
			return 1;
		case 1:
		case 4:
			return CheckPlayerTrespassArea(object, 1);
		case 2:
		case 5:
			return CheckPlayerTrespassArea(object, 0);
		default:
			return 1;
	}
}

extern "C" s32 weightCheckUp(Weight* object)
{
	if ((s8)lbl_8042C180[0x1F] != 0) {
		return 0;
	}
	switch (object->kind) {
		case 0:
		case 3:
			return 1;
		case 1:
		case 4:
			return !CheckPlayerTrespassArea(object, 1);
		case 2:
		case 5:
			return !CheckPlayerTrespassArea(object, 0);
		default:
			return 1;
	}
}
