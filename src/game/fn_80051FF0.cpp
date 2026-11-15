// Converts a direction vector to 16-bit angles: *yaw from the negated x/z components and *pitch
// from the height over the horizontal length (each output optional). The first argument is unused.
// HYPOTHESIS: a camera look-at helper; sqrtf is MSL's, with the TU's pooled constants named.
#include "types.h"

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

extern "C" {
extern f32 lbl_8042D370;          // 65536 / (2 pi)
extern const f32 lbl_8042D374[1]; // 0.0f
extern const f64 lbl_8042D378[1]; // 0.5
extern const f64 lbl_8042D380[1]; // 3.0
double atan2(double y, double x);
}

double __frsqrte(double x);

// MSL's sqrtf (see src/rel/cage_class.inc).
static inline f32 Sqrtf(f32 x)
{
	volatile f32 y;

	if (x > lbl_8042D374[0]) {
		double guess = __frsqrte((double)x);
		double half  = lbl_8042D378[0];
		double three;
		guess = half * guess * ((three = lbl_8042D380[0]) - guess * guess * x);
		guess = half * guess * (three - guess * guess * x);
		guess = half * guess * (three - guess * guess * x);
		y     = (f32)(x * guess);
		return y;
	}
	return x;
}

extern "C" void fn_80051FF0(void* unused, RwV3d* v, s32* pitch, s32* yaw)
{
	if (yaw != NULL) {
		*yaw = lbl_8042D370 * (f32)atan2(-v->x, -v->z);
	}
	if (pitch != NULL) {
		*pitch = lbl_8042D370 * (f32)atan2(v->y, Sqrtf(v->x * v->x + v->z * v->z));
	}
}
