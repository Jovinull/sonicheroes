// Clamps a velocity: when x or z leaves [-max, max] (max at +0xD0 of the path record) the whole
// vector is scaled so that its horizontal length is max; then, when y leaves [-maxY, maxY] (+0xD4),
// it is scaled so that |y| is maxY. The first argument is unused. sqrtf is MSL's, with the TU's
// pooled constants named. HYPOTHESIS: player speed limits.
#include "types.h"

struct Vec800E13DC {
	f32 x;
	f32 y;
	f32 z;
};

struct Ctrl800E13DC {
	u8 pad0[0xD0];
	f32 maxSpeed;  // 0xD0
	f32 maxSpeedY; // 0xD4
};

extern "C" {
extern const f32 lbl_8042E1F0[1]; // 0.0f
extern const f64 lbl_8042E200[1]; // 0.5
extern const f64 lbl_8042E208[1]; // 3.0
extern double __fabs(double x);
}

double __frsqrte(double x);

// MSL's sqrtf (see src/rel/cage_class.inc).
static inline f32 Sqrtf(f32 x)
{
	volatile f32 y;

	if (x > lbl_8042E1F0[0]) {
		double guess = __frsqrte((double)x);
		double half  = lbl_8042E200[0];
		double three;
		guess = half * guess * ((three = lbl_8042E208[0]) - guess * guess * x);
		guess = half * guess * (three - guess * guess * x);
		guess = half * guess * (three - guess * guess * x);
		y     = (f32)(x * guess);
		return y;
	}
	return x;
}

extern "C" void fn_800E13DC(void* unused, Vec800E13DC* v, Ctrl800E13DC* ctrl)
{
	f32 scale;

	if (ctrl->maxSpeed < v->x || -ctrl->maxSpeed > v->x || ctrl->maxSpeed < v->z
	    || -ctrl->maxSpeed > v->z) {
		scale = ctrl->maxSpeed / Sqrtf(v->x * v->x + v->z * v->z);
		v->x *= scale;
		v->y *= scale;
		v->z *= scale;
	}
	if (ctrl->maxSpeedY < v->y || -ctrl->maxSpeedY > v->y) {
		f64 y = __fabs(v->y);

		scale = ctrl->maxSpeedY / (f32)y;
		v->x *= scale;
		v->y *= scale;
		v->z *= scale;
	}
}
