#include "types.h"

extern double __kernel_tan(double x, double y, s32 iy);
extern s32 __ieee754_rem_pio2(double x, double* y);

const double lbl_8042FD90 = 0.0;

double tan(double x)
{
	double y[2];
	s32 n, ix;

	ix = *(s32*)&x;
	ix &= 0x7FFFFFFF;

	if (ix <= 0x3FE921FB) {
		return __kernel_tan(x, lbl_8042FD90, 1);
	} else if (ix >= 0x7FF00000) {
		return x - x;
	} else {
		n = __ieee754_rem_pio2(x, y);
		return __kernel_tan(y[0], y[1], 1 - ((n & 1) << 1));
	}
}
