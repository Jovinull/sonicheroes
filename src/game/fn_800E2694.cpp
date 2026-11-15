#include "types.h"

// Whether a player's action (first argument) should turn: never while the action has flag 0x4000
// or 0x2000 set, the player's state (+0x258, its +0x140) is 2 or 3, the player has flag 0x8000
// (+0x20), or fn_80018EA8 reports the stage (lbl_8029C310) busy. Otherwise it compares the action's
// angle (+0x10) with the slot's yaw (lbl_802AD0B0, +0x1C) when fn_800892B0 accepts the player
// object (lbl_802AD070), or else with the angle fn_800E27D8 finds (none: false), and is true when
// they differ by more than 0x6000 (about 135 degrees). HYPOTHESIS: the roles are UNKNOWN.

struct Action800E2694 {
	u8 pad0[0x6];
	s16 flags; // 0x6
	u8 pad8[0x10 - 0x8];
	s32 angle; // 0x10
};

struct State800E2694 {
	u8 pad0[0x140];
	s32 state; // 0x140
};

struct Player800E2694 {
	s8 index; // 0x0
	u8 pad1[0x20 - 0x1];
	s32 flags; // 0x20
	u8 pad24[0x258 - 0x24];
	State800E2694* state; // 0x258
};

struct Position800E2694 {
	u8 pad0[0x1C];
	s32 yaw; // 0x1C
};

extern "C" {
extern u8 lbl_8029C310[];
extern void* lbl_802AD070[];
extern Position800E2694* lbl_802AD0B0[];
s32 fn_80018EA8(void* stage);
s32 fn_800892B0(void* player);
s32 fn_800E27D8(Action800E2694* action, Player800E2694* player, s32* angle, s32 unknown);
}

// game/misc.h declares it returning u16; the callers here use the full register (no clip), as the
// other units that declare it locally do (fn_800A59C4, fn_8004C160).
s32 DiffAngle(s32 first, s32 second);

extern "C" s32 fn_800E2694(Action800E2694* action, Player800E2694* player)
{
	s32 angle;
	s32 diff;

	if (action->flags & 0x4000) {
		return 0;
	}
	if (action->flags & 0x2000) {
		return 0;
	}
	if (player->state->state == 2 || player->state->state == 3) {
		return 0;
	}
	if (player->flags & 0x8000) {
		return 0;
	}
	if (fn_80018EA8(lbl_8029C310)) {
		return 0;
	}
	if (fn_800892B0(lbl_802AD070[player->index])) {
		diff = DiffAngle(action->angle, lbl_802AD0B0[player->index]->yaw);
	} else {
		if (fn_800E27D8(action, player, &angle, 0) == 0) {
			return 0;
		}
		diff = DiffAngle(action->angle, angle);
	}
	if (diff > 0x6000) {
		return 1;
	}
	return 0;
}
