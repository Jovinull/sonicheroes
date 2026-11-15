#include "types.h"

// Points player `index`'s action (lbl_802AD090) along the direction (x, y, z): the yaw
// (+0x10, copied to the motion lbl_802AD0B0 +0x1C) is atan2(z, x); the pitch (+0xC) is acos of
// -z over the length times fn_800D7B00 of the yaw; the roll (+0x14) is asin(y / h) minus
// asin(|length| * fn_800D7B00(pitch) / h), h being the length in the XY plane (angles in 16-bit
// units, lbl_8042E210). HYPOTHESIS: fn_800D7B00 is a cosine; the axis roles are UNKNOWN.
// NonMatching (33 words, float registers only): retail keeps x in f0 across the first sqrtf and
// numbers its temporaries f1..f4 (MWCC: x in f4, temporaries f0..f3), and swaps the two volatile
// sqrt slots. The second sqrtf is written in place (the inline copied its argument); expanding
// the first one too, and every order of the float declarations, did not help.

struct Action800DFFA0 {
	u8 pad0[0xC];
	s32 pitch; // 0xC
	s32 yaw;   // 0x10
	s32 roll;  // 0x14
};

struct Motion800DFFA0 {
	u8 pad0[0x1C];
	s32 yaw; // 0x1C
};

extern "C" {
extern Action800DFFA0* lbl_802AD090[8];
extern Motion800DFFA0* lbl_802AD0B0[8];
extern const f32 lbl_8042E1F0; // 0.0f
extern const f64 lbl_8042E200; // 0.5
extern const f64 lbl_8042E208; // 3.0
extern const f32 lbl_8042E210; // radians to 16-bit angle units
double atan2(double y, double x);
double acos(double x);
double asin(double x);
f64 __frsqrte(f64 x);
f64 __fabs(f64 x);
f32 fn_800D7B00(s32 angle);
}

// The MSL sqrtf (three Newton steps on frsqrte; the volatile store is the retail round trip).
static inline f32 SqrtF(f32 value)
{
	if (value > lbl_8042E1F0) {
		f64 estimate = __frsqrte(value);
		estimate     = lbl_8042E200 * estimate * (lbl_8042E208 - estimate * estimate * value);
		estimate     = lbl_8042E200 * estimate * (lbl_8042E208 - estimate * estimate * value);
		estimate     = lbl_8042E200 * estimate * (lbl_8042E208 - estimate * estimate * value);
		volatile f32 result = value * estimate;
		value               = result;
	}
	return value;
}

static inline f32 AbsF(f32 value)
{
	return __fabs(value);
}

extern "C" void fn_800DFFA0(s32 index, f32 x, f32 y, f32 z)
{
	Action800DFFA0* action;
	Motion800DFFA0* motion;
	s32 pitch;
	s32 yaw;
	f32 plane;
	f32 length;
	f32 first;
	f32 second;
	f64 size;

	action = lbl_802AD090[index];
	motion = lbl_802AD0B0[index];
	length = SqrtF(z * z + (plane = x * x + y * y));
	yaw    = lbl_8042E210 * (f32)atan2(z, x);
	length *= fn_800D7B00(yaw);
	size  = __fabs(length);
	pitch = lbl_8042E210 * (f32)acos(-z / (f32)size);
	if (plane > lbl_8042E1F0) {
		f64 estimate = __frsqrte(plane);
		estimate     = lbl_8042E200 * estimate * (lbl_8042E208 - estimate * estimate * plane);
		estimate     = lbl_8042E200 * estimate * (lbl_8042E208 - estimate * estimate * plane);
		estimate     = lbl_8042E200 * estimate * (lbl_8042E208 - estimate * estimate * plane);
		volatile f32 result = plane * estimate;
		plane               = result;
	}
	size          = __fabs(length);
	first         = asin((f32)size * fn_800D7B00(pitch) / plane);
	second        = asin(y / plane);
	action->pitch = pitch;
	action->yaw   = yaw;
	motion->yaw   = action->yaw;
	action->roll  = (s32)(lbl_8042E210 * second) - (s32)(lbl_8042E210 * first);
}
