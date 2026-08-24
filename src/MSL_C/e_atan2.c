#include "MSL_C/math.h"
#include "types.h"

double __ieee754_atan2(double y, double x)
{
	double z;
	s32 k, m, hx, hy, ix, iy;
	u32 lx, ly;

	hx = *(s32*)&x;
	ix = hx & 0x7FFFFFFF;
	lx = *((u32*)&x + 1);
	hy = *(s32*)&y;
	iy = hy & 0x7FFFFFFF;
	ly = *((u32*)&y + 1);

	if (((ix | ((lx | -lx) >> 31)) > 0x7FF00000) || ((iy | ((ly | -ly) >> 31)) > 0x7FF00000))
		return x + y;

	if (((hx - 0x3FF00000) | lx) == 0)
		return atan(y);

	m = ((hy >> 31) & 1) | ((hx >> 30) & 2);

	if ((iy | ly) == 0) {
		switch (m) {
			case 0:
			case 1:
				return y;
			case 2:
				return 3.1415926535897931160E+00 + 1.0e-300;
			case 3:
				return -3.1415926535897931160E+00 - 1.0e-300;
		}
	}

	if ((ix | lx) == 0) {
		if (hy < 0)
			return -1.5707963267948965580E+00 - 1.0e-300;
		return 1.5707963267948965580E+00 + 1.0e-300;
	}

	if (ix == 0x7FF00000) {
		if (iy == 0x7FF00000) {
			switch (m) {
				case 0:
					return 7.8539816339744827900E-01 + 1.0e-300;
				case 1:
					return -7.8539816339744827900E-01 - 1.0e-300;
				case 2:
					return 3.0 * 7.8539816339744827900E-01 + 1.0e-300;
				case 3:
					return -3.0 * 7.8539816339744827900E-01 - 1.0e-300;
			}
		} else {
			switch (m) {
				case 0:
					return 0.0;
				case 1:
					return -0.0;
				case 2:
					return 3.1415926535897931160E+00 + 1.0e-300;
				case 3:
					return -3.1415926535897931160E+00 - 1.0e-300;
			}
		}
	}

	if (iy == 0x7FF00000) {
		if (hy < 0)
			return -1.5707963267948965580E+00 - 1.0e-300;
		return 1.5707963267948965580E+00 + 1.0e-300;
	}

	k = (iy - ix) >> 20;
	if (k > 60)
		z = 1.5707963267948965580E+00 + 0.5 * 1.2246467991473531772E-16;
	else if (hx < 0 && k < -60)
		z = 0.0;
	else
		z = atan(__fabs(y / x));

	switch (m) {
		case 0:
			return z;
		case 1:
			*(s32*)&z ^= 0x80000000;
			return z;
		case 2:
			return 3.1415926535897931160E+00 - (z - 1.2246467991473531772E-16);
		default:
			return (z - 1.2246467991473531772E-16) - 3.1415926535897931160E+00;
	}
}
