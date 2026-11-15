#include "game/rw_types.h"

// Turns a player's motion yaw (+0x1C) towards a slope (HYPOTHESIS: the downhill turn of the
// ground actions; see fn_800DCB20): nothing happens for a record with +0x14 set or flag 0x400
// (+0x90); a velocity (motion +0x0) faster than +0xEC that runs against gravity (lbl_80242B38; dot
// product of the normalised velocity below lbl_8042E148) is left alone too. Otherwise gravity is
// taken into the action's frame (fn_8003EB18); when it points down within lbl_8042E150 the yaw
// turns towards its horizontal direction (atan2, half a turn when fn_800D7AE4 of it is negative,
// plus the action's angle +0x10) by a step proportional to its Z (lbl_8042E154 with action flag
// 0x100 at +0x6, lbl_8042E158 otherwise), else it takes the action's angle; then fn_800E1A48 runs.
// Returns fn_800D7AE4 of the slope direction (lbl_8042E09C, 0, when there is none).

struct Action800DAD94 {
	u8 pad0[0x6];
	s16 flags; // 0x6
	u8 pad8[0x10 - 0x8];
	s32 angle; // 0x10
};

struct Motion800DAD94 {
	RwV3d velocity; // 0x0
	u8 padC[0x1C - 0xC];
	s32 yaw; // 0x1C
};

struct Record800DAD94 {
	u8 pad0[0x14];
	s16 unknown14; // 0x14
	u8 pad16[0x90 - 0x16];
	u32 flags; // 0x90
	u8 pad94[0xEC - 0x94];
	f32 speed; // 0xEC
};

struct Gravity800DAD94 {
	RwV3d direction; // 0x0
	u8 padC[0x10 - 0xC];
};

extern "C" {
extern Gravity800DAD94 lbl_80242B38;
extern const f32 lbl_8042E098; // radians to 16-bit angle units
extern const f32 lbl_8042E09C; // 0.0f
extern const f64 lbl_8042E148;
extern const f32 lbl_8042E150;
extern const f32 lbl_8042E154;
extern const f32 lbl_8042E158;
double atan2(double y, double x);
f32 fn_800D7AE4(s32 angle);
void fn_801990E0(RwV3d* dst, RwV3d* src);
void fn_8003EB18(Action800DAD94* action, RwV3d* vector);
void fn_800E1A48(Action800DAD94* action, Motion800DAD94* motion, Record800DAD94* record, s32 yaw);
}

static inline void Abs(f32* value)
{
	if (*value < lbl_8042E09C) {
		*value = -*value;
	}
}

// game/misc.h declares AdjustAngle returning u16; the callers use the full register.
s32 AdjustAngle(s32 first, s32 second, s32 limit);

// Built without common subexpressions: retail reloads lbl_8042E09C before the |Z| test.
#pragma opt_common_subs off
extern "C" f32 fn_800DAD94(Action800DAD94* action, Motion800DAD94* motion, Record800DAD94* record)
{
	f32 slope = lbl_8042E09C;

	if (record->unknown14 != 0) {
		return slope;
	}
	if (record->flags & 0x400) {
		return slope;
	}
	const RwV3d* down = &lbl_80242B38.direction;
	RwV3d gravity;
	gravity.x = down->x;
	gravity.y = down->y;
	gravity.z = down->z;
	RwV3d velocity;
	velocity.x = motion->velocity.x;
	velocity.y = motion->velocity.y;
	velocity.z = motion->velocity.z;
	if (velocity.z * velocity.z + (velocity.x * velocity.x + velocity.y * velocity.y)
	    > record->speed * record->speed) {
		fn_801990E0(&velocity, &velocity);
		// X is read through the global (retail rebuilds its address there).
		if (down->z * velocity.z + (lbl_80242B38.direction.x * velocity.x + down->y * velocity.y)
		    < lbl_8042E148) {
			return lbl_8042E09C;
		}
	}
	fn_8003EB18(action, &gravity);
	if (gravity.y < lbl_8042E09C && gravity.y > lbl_8042E150) {
		s32 angle = lbl_8042E098 * (f32)atan2(gravity.z, gravity.x);
		s32 yaw   = angle;
		slope     = fn_800D7AE4(angle);
		if (slope < lbl_8042E09C) {
			yaw += 0x8000;
		}
		yaw += action->angle;
		Abs(&gravity.z);
		motion->yaw = AdjustAngle(motion->yaw, yaw,
		    (action->flags & 0x100) ? (s32)(lbl_8042E154 * gravity.z)
		                            : (s32)(lbl_8042E158 * gravity.z));
	} else {
		motion->yaw = action->angle;
	}
	fn_800E1A48(action, motion, record, motion->yaw);
	return slope;
}
#pragma opt_common_subs reset
