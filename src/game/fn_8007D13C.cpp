#include "game/rw_types.h"

// Updates the two hand effects of character type 3 (+0x761; HYPOTHESIS: the glow on a power
// character's hands): only in states 6..8 (+0x8B0) without flag 2 (+0x98C) and outside action
// 0x2B; otherwise the effects are released as by fn_8007D064. The effects (+0xA88, +0xA8C)
// follow the points +0x238 and +0x29C with the player's angles (+0x6FC, 0xC000 minus +0x700,
// +0x704; the rest of the angle from lbl_80239E54) and are created with fn_8006298C (type 4)
// when missing; fn_80064380 or fn_80064370 then runs on their +0x28 block by a visibility flag
// that is 0 on both paths of the retail test of the team bit (+0x9BC) in mode switches 0x1F and
// 0x20 of lbl_8042C180. The roles are UNKNOWN.
// NonMatching (10 words): retail copies the followed point through its address in r4 (the one
// it null-checks); MWCC folds the copy into offsets from the player (r30) and tests the address
// in r0. A nested setter inline and opt_propagation/opt_common_subs pragmas did not help.

struct Angle8007D13C {
	s32 x;
	s32 y;
	s32 z;
};

struct Effect8007D13C {
	u8 pad0[0x28];
	u8 block[0x80 - 0x28]; // 0x28
	RwV3d position;        // 0x80
	Angle8007D13C angle;   // 0x8C
};

struct Player8007D13C {
	u8 pad0[0x238];
	RwV3d left; // 0x238
	u8 pad244[0x29C - 0x244];
	RwV3d right; // 0x29C
	u8 pad2A8[0x6F0 - 0x2A8];
	s16 action; // 0x6F0
	u8 pad6F2[0x6FC - 0x6F2];
	s32 angleX; // 0x6FC
	s32 angleY; // 0x700
	s32 angleZ; // 0x704
	u8 pad708[0x761 - 0x708];
	s8 type; // 0x761
	u8 pad762[0x8B0 - 0x762];
	s16 state; // 0x8B0
	u8 pad8B2[0x98C - 0x8B2];
	u32 flags; // 0x98C
	u8 pad990[0x9BC - 0x990];
	s8 team; // 0x9BC
	u8 pad9BD[0xA88 - 0x9BD];
	Effect8007D13C* effects[2]; // 0xA88
};

struct ModeSwitch8007D13C {
	u8 pad0[0x1F];
	s8 unknown1F; // 0x1F
	s8 unknown20; // 0x20
};

extern "C" {
extern ModeSwitch8007D13C* lbl_8042C180;
extern Angle8007D13C lbl_80239E54;
void fn_8005FD8C(Effect8007D13C* effect, s32 unknown);
Effect8007D13C* fn_8006298C(s32 type, RwV3d* position, Angle8007D13C* angle);
void fn_80064370(void* block);
void fn_80064380(void* block);
}

// fn_8007D064.
static inline void Release(Player8007D13C* player)
{
	if (player->type == 3) {
		if (player->effects[0] != NULL) {
			fn_8005FD8C(player->effects[0], -1);
			player->effects[0] = NULL;
		}
		if (player->effects[1] != NULL) {
			fn_8005FD8C(player->effects[1], -1);
			player->effects[1] = NULL;
		}
	}
}

static inline void Follow(Effect8007D13C** slot, RwV3d* position, Angle8007D13C* angle, s32 shown)
{
	Effect8007D13C* effect = *slot;

	if (effect != NULL) {
		if (position != NULL) {
			effect->position.x = position->x;
			effect->position.y = position->y;
			effect->position.z = position->z;
		}
		effect->angle.x = angle->x;
		effect->angle.y = angle->y;
		effect->angle.z = angle->z;
	} else {
		effect = *slot = fn_8006298C(4, position, angle);
	}
	if (effect != NULL) {
		if (shown) {
			fn_80064370(effect->block);
		} else {
			fn_80064380(effect->block);
		}
	}
}

extern "C" void fn_8007D13C(Player8007D13C* player)
{
	if (player->type != 3) {
		return;
	}
	if (!((player->state == 6 || player->state == 7 || player->state == 8) && !(player->flags & 2)
	        && player->action != 0x2B)) {
		Release(player);
	} else {
		s32 mask = ~(1 << player->team);
		s32 shown;
		if (!(mask & lbl_8042C180->unknown1F) && !(mask & lbl_8042C180->unknown20)) {
			shown = 0;
		} else {
			shown = 0;
		}
		Angle8007D13C angle = lbl_80239E54;
		angle.x             = player->angleX;
		angle.y             = 0xC000 - player->angleY;
		angle.z             = player->angleZ;
		Follow(&player->effects[0], &player->left, &angle, shown);
		Follow(&player->effects[1], &player->right, &angle, shown);
	}
}
