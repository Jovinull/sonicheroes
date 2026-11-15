#include "types.h"

// Turns a direction (x, z horizontal, y vertical) into a pitch and a yaw in 16-bit angle units
// (lbl_8042D154 per radian): straight up (y above lbl_8042D148, or no horizontal part within
// lbl_8042D14C and y above lbl_8042D120) gives pitch 0x4000 and yaw 0, straight down (y below
// lbl_8042D150, or no horizontal part and y below lbl_8042D120) gives pitch 0xC000 and yaw 0;
// otherwise pitch = asin(y) and yaw = -atan2(x, z). HYPOTHESIS: lbl_8042D148/D150 are 1 and -1 and
// lbl_8042D120 is 0 (values not checked); the vector is presumably normalized.

extern "C" {
extern const f32 lbl_8042D120;
extern const f32 lbl_8042D148;
extern const f32 lbl_8042D14C;
extern const f32 lbl_8042D150;
extern const f32 lbl_8042D154;
double __fabs(double x);
double asin(double x);
double atan2(double y, double x);
}

extern "C" void fn_8003FE68(f32 x, f32 z, f32 y, s32* pitch, s32* yaw)
{
	if (y > lbl_8042D148
	    || ((f32)__fabs(z) < lbl_8042D14C && (f32)__fabs(x) < lbl_8042D14C && y > lbl_8042D120)) {
		*pitch = 0x4000;
		*yaw   = 0;
	} else if (y < lbl_8042D150
	    || ((f32)__fabs(z) < lbl_8042D14C && (f32)__fabs(x) < lbl_8042D14C && y < lbl_8042D120)) {
		*pitch = 0xC000;
		*yaw   = 0;
	} else {
		*pitch = lbl_8042D154 * (f32)asin(y);
		*yaw   = -(s32)(lbl_8042D154 * (f32)atan2(x, z));
	}
}
