#include "game/rw_types.h"

// Classifies how a player meets a wall from a rail (0: no wall, rail or wall direction; else 1..4
// from the widest to the narrowest angle, over 0x6000, 0x3400 and 0x1400): never with action flag
// 0x4000. The wall direction comes from fn_800E27D8 and the rail direction from fn_8004102C; the
// rail's yaw is taken on the plane of the gravity (lbl_80242B38: with zero Y gravity the plane
// picked by lbl_8042C4A0/lbl_8042C4A4, mirrored when those angles point backward, else the XZ
// plane, flipped for gravity pointing down). HYPOTHESIS: the roles are UNKNOWN.

struct Gravity800E1F28 {
	RwV3d direction; // 0x0
	u8 padC[0x10 - 0xC];
};

struct Player800E1F28 {
	u8 pad0[0x6F0];
	u8 action[0x760 - 0x6F0]; // 0x6F0 (flags at +0x6)
	u8 record[0x4];           // 0x760
};

extern "C" {
extern Gravity800E1F28 lbl_80242B38;
// Declared volatile here: the retail code reloads them for the DiffAngle calls instead of reusing
// the compared values (whether the originals are volatile is UNKNOWN).
extern volatile s32 lbl_8042C4A0;
extern volatile s32 lbl_8042C4A4;
extern const f32 lbl_8042E1F0; // 0.0f
extern const f32 lbl_8042E210; // radians to 16-bit angle units
double atan2(double y, double x);
s32 fn_800E27D8(void* action, void* record, s32* angle, f32* strength);
s32 fn_8004102C(Player800E1F28* player, RwV3d* direction);
}

// game/misc.h declares DiffAngle returning u16; the callers use the full register.
s32 DiffAngle(s32 first, s32 second);

extern "C" s32 fn_800E1F28(Player800E1F28* player)
{
	void* action = player->action;
	void* record = player->record;
	s32 wall;
	RwV3d rail;
	s32 yaw;

	if (*(s16*)((u8*)action + 0x6) & 0x4000) {
		return 0;
	}
	if (fn_800E27D8(action, record, &wall, NULL) == 0) {
		return 0;
	}
	if (fn_8004102C(player, &rail) == 0) {
		return 0;
	}
	if (lbl_8042E1F0 == lbl_80242B38.direction.y) {
		f32 y;
		f32 x;
		if (lbl_8042C4A0 == 0) {
			y = -rail.z;
			x = -rail.y;
		} else if (lbl_8042C4A4 == 0) {
			y = rail.y;
			x = -rail.x;
		} else {
			y = -rail.z;
			x = rail.x;
		}
		if (DiffAngle(lbl_8042C4A0, 0x4000) > 0x4000) {
			y = -y;
		}
		if (DiffAngle(lbl_8042C4A4, 0x4000) > 0x4000) {
			x = -x;
		}
		yaw = lbl_8042E210 * (f32)atan2(y, x);
	} else if (lbl_80242B38.direction.y >= lbl_8042E1F0) {
		yaw = lbl_8042E210 * (f32)atan2(-rail.z, rail.x);
	} else {
		yaw = lbl_8042E210 * (f32)atan2(-rail.z, -rail.x);
	}
	s32 diff = DiffAngle(wall, yaw);
	if (diff > 0x6000) {
		return 1;
	}
	if (diff > 0x3400) {
		return 2;
	}
	if (diff > 0x1400) {
		return 3;
	}
	return 4;
}
