#include "game/rw_types.h"

// Turns a surface normal into a player's surface angles (HYPOTHESIS: aligning to a wall or
// ceiling): a normal mostly along +Z (over lbl_8042E364, or over lbl_8042E320 with |Y| below
// lbl_8042E368) snaps to (0, 0, lbl_8042E250) with X angle 0x4000 and the player's Z angle
// (+0x704); mostly along -Z (below lbl_8042E36C, or lbl_8042E370 with a small |Y|) snaps to
// (0, 0, lbl_8042E298) with 0xC000. Otherwise a normal mostly along +Y or -Y (beyond
// lbl_8042E374/lbl_8042E378) snaps to the Y axis with X angle 0 or 0x8000 and Z angle 0, and any
// other gives X = asin(Z) and Z = -atan2(X, Y) (16-bit units, lbl_8042E29C). The angles flip
// when the Z angle is more than 0x4000 off the player's, and for a player on a vertical X angle
// (+0x6FC 0x4000/0xC000) the Y angle follows the Z angle change.

struct Player800EC828 {
	u8 pad0[0x6FC];
	s32 angleX; // 0x6FC
	u8 pad700[0x704 - 0x700];
	s32 angleZ; // 0x704
};

struct Angle800EC828 {
	s32 x;
	s32 y;
	s32 z;
};

extern "C" {
extern const f32 lbl_8042E250; // 1.0f
extern const f32 lbl_8042E254; // 0.0f
extern const f32 lbl_8042E298; // -1.0f
extern const f32 lbl_8042E29C; // radians to 16-bit angle units
extern const f32 lbl_8042E320;
extern const f32 lbl_8042E364;
extern const f32 lbl_8042E368;
extern const f32 lbl_8042E36C;
extern const f32 lbl_8042E370;
extern const f32 lbl_8042E374;
extern const f32 lbl_8042E378;
double atan2(double y, double x);
double asin(double x);
f64 __fabs(f64 x);
}

// game/misc.h declares DiffAngle returning u16; the callers use the full register.
s32 DiffAngle(s32 first, s32 second);

extern "C" void fn_800EC828(Player800EC828* player, RwV3d* normal, Angle800EC828* angle)
{
	if (normal->z > lbl_8042E364
	    || (normal->z > lbl_8042E320 && (f32)__fabs(normal->y) < lbl_8042E368)) {
		angle->x  = 0x4000;
		angle->z  = player->angleZ;
		normal->x = lbl_8042E254;
		normal->y = lbl_8042E254;
		normal->z = lbl_8042E250;
		return;
	}
	if (normal->z < lbl_8042E36C
	    || (normal->z < lbl_8042E370 && (f32)__fabs(normal->y) < lbl_8042E368)) {
		angle->x  = 0xC000;
		angle->z  = player->angleZ;
		normal->x = lbl_8042E254;
		normal->y = lbl_8042E254;
		normal->z = lbl_8042E298;
		return;
	}
	if (normal->y > lbl_8042E374) {
		angle->x  = 0;
		angle->z  = 0;
		normal->x = lbl_8042E254;
		normal->y = lbl_8042E250;
		normal->z = lbl_8042E254;
	} else if (normal->y < lbl_8042E378) {
		angle->x  = 0x8000;
		angle->z  = 0;
		normal->x = lbl_8042E254;
		normal->y = lbl_8042E298;
		normal->z = lbl_8042E254;
	} else {
		angle->x = (s32)(lbl_8042E29C * (f32)asin(normal->z));
		angle->z = -(s32)(lbl_8042E29C * (f32)atan2(normal->x, normal->y));
	}
	s32 x = angle->x;
	s32 z = angle->z;
	DiffAngle(player->angleX, x);
	if (DiffAngle(player->angleZ, z) > 0x4000) {
		angle->z = z + 0x8000;
		angle->x = 0x8000 - x;
	}
	if ((player->angleX == 0x4000 || player->angleX == 0xC000) && angle->x != 0x4000
	    && angle->x != 0xC000) {
		angle->y = player->angleZ + (angle->y - angle->z);
	}
}
