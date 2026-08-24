#include "types.h"

extern double __kernel_cos(double x, double y);
extern double __kernel_sin(double x, double y, s32 iy);
extern s32 __ieee754_rem_pio2(double x, double* y);

double cos(double x)
{
	double y[2], z = 0.0;
	s32 n, ix;

	ix = *(s32*)&x;
	ix &= 0x7FFFFFFF;

	if (ix <= 0x3FE921FB) {
		return __kernel_cos(x, z);
	} else if (ix >= 0x7FF00000) {
		return x - x;
	} else {
		n = __ieee754_rem_pio2(x, y);

		switch (n & 3) {
			case 0:
				return __kernel_cos(y[0], y[1]);
			case 1:
				return -__kernel_sin(y[0], y[1], 1);
			case 2:
				return -__kernel_cos(y[0], y[1]);
			default:
				return __kernel_sin(y[0], y[1], 1);
		}
	}
}
