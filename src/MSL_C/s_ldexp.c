#include "types.h"

extern double copysign(double x, double y);

extern inline s32 __fpclassifyd(double x)
{
	switch ((*(s32*)&x) & 0x7FF00000) {
		case 0x7FF00000:
			if (((*(s32*)&x) & 0xFFFFF) || (*(1 + (s32*)&x)) & 0xFFFFFFFF) {
				return 1;
			} else {
				return 2;
			}
		case 0:
			if (((*(s32*)&x) & 0xFFFFF) || (*(1 + (s32*)&x)) & 0xFFFFFFFF) {
				return 5;
			} else {
				return 3;
			}
	}

	return 4;
}

double ldexp(double x, s32 n)
{
	s32 exp, hx, lx;

	if (!(__fpclassifyd(x) > 2) || x == 0.0) {
		return x;
	}

	hx  = *(s32*)&x;
	lx  = *(1 + (s32*)&x);
	exp = (hx & 0x7FF00000) >> 20;

	if (exp == 0) {
		if ((lx | (hx & 0x7FFFFFFF)) == 0) {
			return x;
		}

		x *= 1.80143985094819840000e+16;
		hx  = *(s32*)&x;
		exp = ((hx & 0x7FF00000) >> 20) - 54;

		if (n < -50000) {
			return 1.0e-300 * x;
		}
	}

	if (exp == 0x7FF) {
		return x + x;
	}

	exp = exp + n;

	if (exp > 0x7FE) {
		return 1.0e+300 * copysign(1.0e+300, x);
	}

	if (exp > 0) {
		*(s32*)&x = (hx & 0x800FFFFF) | (exp << 20);
		return x;
	}

	if (exp <= -54) {
		if (n > 50000) {
			return 1.0e+300 * copysign(1.0e+300, x);
		} else {
			return 1.0e-300 * copysign(1.0e-300, x);
		}
	}

	exp += 54;
	*(s32*)&x = (hx & 0x800FFFFF) | (exp << 20);
	return x * 5.55111512312578270212e-17;
}
