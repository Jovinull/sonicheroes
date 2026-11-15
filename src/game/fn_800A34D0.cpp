#include "game/misc.h"

// Moves an enemy toward a point; returns whether it arrived. Nothing moves while any of the
// play-mode flags 31..33 (lbl_8042C180) is set. Gravity (+0x1A8) is added to the vertical speed
// (+0x15C) unless the enemy has flag 0x2 (+0x106), which zeroes it; the horizontal speed
// (+0x158/+0x160) is limited to +0x1B8 and the vertical speed kept above +0x1B4. The enemy has
// arrived when its collision flags (+0x30) have 0x8 or AdjustPoint moves its position (+0x140)
// onto the point within |vertical speed|; the speed is then cleared. HYPOTHESIS: a TObjEnemy
// helper (see game/enemy/e_obj_enemy.h); the field names are UNKNOWN.

struct Enemy800A34D0 {
	u8 pad0[0x30];
	u16 colliFlags; // 0x30
	u8 pad32[0x106 - 0x32];
	u16 flags; // 0x106
	u8 pad108[0x140 - 0x108];
	RwV3d position; // 0x140
	u8 pad14C[0x158 - 0x14C];
	RwV3d speed; // 0x158
	u8 pad164[0x1A8 - 0x164];
	f32 gravity; // 0x1A8
	u8 pad1AC[0x1B4 - 0x1AC];
	f32 minFall;  // 0x1B4
	f32 maxSpeed; // 0x1B8
};

struct PlayMode800A34D0 {
	s8 flags[44];
};

extern "C" {
extern PlayMode800A34D0* lbl_8042C180;
extern const f32 lbl_8042DA74; // 0.0f
double __fabs(double x);
f32 fn_801991B4(const RwV3d* v);
f32 fn_801990E0(RwV3d* out, const RwV3d* in);
}

static inline BOOL CanMove()
{
	if (lbl_8042C180->flags[31] != 0) {
		return FALSE;
	}
	if (lbl_8042C180->flags[32] != 0) {
		return FALSE;
	}
	if (lbl_8042C180->flags[33] != 0) {
		return FALSE;
	}
	return TRUE;
}

extern "C" s32 fn_800A34D0(Enemy800A34D0* enemy, const RwV3d* point)
{
	BOOL arrived = FALSE;

	if (!CanMove()) {
		return 0;
	}
	if (!(enemy->flags & 0x2)) {
		enemy->speed.y += enemy->gravity;
	} else {
		enemy->speed.y = lbl_8042DA74;
	}
	RwV3d horizontal = enemy->speed;
	horizontal.y     = lbl_8042DA74;
	if (fn_801991B4(&horizontal) > enemy->maxSpeed) {
		fn_801990E0(&horizontal, &horizontal);
		horizontal.x *= enemy->maxSpeed;
		horizontal.y *= enemy->maxSpeed;
		horizontal.z *= enemy->maxSpeed;
		enemy->speed.x = horizontal.x;
		enemy->speed.z = horizontal.z;
	}
	if (enemy->speed.y < enemy->minFall) {
		enemy->speed.y = enemy->minFall;
	}
	if (enemy->colliFlags & 0x8) {
		arrived        = TRUE;
		enemy->speed.x = enemy->speed.y = enemy->speed.z = lbl_8042DA74;
	} else {
		f64 step = __fabs(enemy->speed.y);
		if (AdjustPoint(&enemy->position, point, step)) {
			arrived        = TRUE;
			enemy->speed.x = enemy->speed.y = enemy->speed.z = lbl_8042DA74;
		}
	}
	return arrived;
}
