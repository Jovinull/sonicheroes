#include "game/rw_types.h"

// Pulls a player towards its partner's marked point (HYPOTHESIS: the rope/tether attach of a team
// action; the point is the collision's +0x54 vector, see fn_80021344): only with the action
// control bits (+0x6 & 3) or in action 0x42, while moving (squared length of the motion vector
// +0x0 at least lbl_8042E250) and not rising (+0x64 at most lbl_8042E254). With the offset to the
// point (DistanceP2PL) longer than lbl_8042E294 the action yaw (+0x10, copied to the motion
// +0x1C) turns by the offset's heading in the action frame (atan2), unless that is more than
// 0x4000 off outside action 0x42 (returns 0), and returns 1; otherwise the speed's X and Z
// (+0x60, +0x68) are cleared and it returns 2. Either way the motion vector becomes the speed in
// world space (fn_8003E9B4).
// NonMatching (41 words, saved registers only): retail keeps the three arguments in r29..r31 and
// the yaw and turn in r28/r27; MWCC gives the arguments r27..r29. Declaration orders (perm.py),
// block-scoped locals and a shared speed helper did not change it.

struct Action800EC5AC {
	s16 mode; // 0x0
	u8 pad2[0x6 - 0x2];
	s16 flags; // 0x6
	u8 pad8[0x10 - 0x8];
	s32 yaw; // 0x10
};

struct Motion800EC5AC {
	RwV3d vector; // 0x0
	u8 padC[0x1C - 0xC];
	s32 yaw; // 0x1C
};

struct Record800EC5AC {
	s8 number; // 0x0
	u8 pad1[0x60 - 0x1];
	RwV3d speed; // 0x60
};

struct Player800EC5AC {
	u8 pad0[0x28];
	u8 colli[0x4]; // 0x28
};

extern "C" {
extern Player800EC5AC* lbl_802AD070[8];
extern const f32 lbl_8042E250;
extern const f32 lbl_8042E254; // 0.0f
extern const f32 lbl_8042E260;
extern const f32 lbl_8042E294;
extern const f32 lbl_8042E29C; // radians to 16-bit angle units
extern const f32 lbl_8042E2A0;
double atan2(double y, double x);
f64 __fabs(f64 x);
s32 fn_80021344(void* colli, RwV3d* point);
void fn_801990E0(RwV3d* dst, RwV3d* src);
void fn_8003E9B4(Action800EC5AC* action, RwV3d* vector);
void fn_8003EB18(Action800EC5AC* action, RwV3d* vector);
}

// game/misc.h declares DiffAngle returning u16; the callers use the full register.
s32 DiffAngle(s32 first, s32 second);
f32 DistanceP2PL(const RwV3d* point, const RwV3d* line, RwV3d* offset);

extern "C" s32 fn_800EC5AC(Action800EC5AC* action, Motion800EC5AC* motion, Record800EC5AC* record)
{
	RwV3d point;
	RwV3d offset;
	RwV3d direction;
	RwV3d local;

	if ((action->flags & 3) == 0 && action->mode != 0x42) {
		return 0;
	}
	if (motion->vector.z * motion->vector.z
	        + (motion->vector.x * motion->vector.x + motion->vector.y * motion->vector.y)
	    < lbl_8042E250) {
		return 0;
	}
	if (record->speed.y > lbl_8042E254) {
		return 0;
	}
	if (fn_80021344(lbl_802AD070[record->number]->colli, &point) == 0) {
		return 0;
	}
	DistanceP2PL(&motion->vector, &point, &offset);
	if (offset.z * offset.z + (offset.x * offset.x + offset.y * offset.y) > lbl_8042E294) {
		fn_801990E0(&direction, &offset);
	} else {
		record->speed.x = record->speed.z = direction.x = direction.y = direction.z = lbl_8042E254;
		offset.x = record->speed.x;
		offset.y = record->speed.y;
		offset.z = record->speed.z;
		fn_8003E9B4(action, &offset);
		motion->vector.x = offset.x;
		motion->vector.y = offset.y;
		motion->vector.z = offset.z;
		return 2;
	}
	local = direction;
	fn_8003EB18(action, &local);
	s32 yaw = action->yaw;
	if (local.z * local.z + (local.x * local.x + local.y * local.y) > lbl_8042E260
	    && (f32)__fabs(local.y) < lbl_8042E2A0) {
		s32 turn = lbl_8042E29C * (f32)atan2(local.z, local.x);
		if (DiffAngle(0, turn) > 0x4000 && action->mode != 0x42) {
			return 0;
		}
		yaw += turn;
	}
	action->yaw = yaw;
	motion->yaw = yaw;
	offset.x    = record->speed.x;
	offset.y    = record->speed.y;
	offset.z    = record->speed.z;
	fn_8003E9B4(action, &offset);
	motion->vector.x = offset.x;
	motion->vector.y = offset.y;
	motion->vector.z = offset.z;
	return 1;
}
