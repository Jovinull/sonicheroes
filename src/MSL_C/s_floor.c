#include "types.h"

static const double big = 1.0e300;

double floor(double x)
{
	s32 dbl_hi, dbl_lo, j0;
	u32 i, j;

	dbl_hi = *((s32*)&x);
	dbl_lo = *(1 + (s32*)&x);
	j0     = ((dbl_hi >> 20) & 0x7FF) - 0x3FF;

	if (j0 < 20) {
		if (j0 < 0) {
			if (big + x > 0.0) {
				if (dbl_hi >= 0) {
					dbl_hi = dbl_lo = 0;
				} else if (((dbl_hi & 0x7FFFFFFF) | dbl_lo) != 0) {
					dbl_hi = 0xBFF00000;
					dbl_lo = 0;
				}
			}
		} else {
			i = 0xFFFFF >> j0;

			if (((dbl_hi & i) | dbl_lo) == 0) {
				return x;
			}

			if (big + x > 0.0) {
				if (dbl_hi < 0) {
					dbl_hi += 0x100000 >> j0;
				}

				dbl_hi &= ~i;
				dbl_lo = 0;
			}
		}
	} else if (j0 > 51) {
		if (j0 == 0x400) {
			return x + x;
		} else {
			return x;
		}
	} else {
		i = ((u32)(0xFFFFFFFF)) >> j0 - 20;

		if ((dbl_lo & i) == 0) {
			return x;
		}

		if (big + x > 0.0) {
			if (dbl_hi < 0) {
				if (j0 == 20) {
					dbl_hi += 1;
				} else {
					j = dbl_lo + (1 << (52 - j0));

					if (j < dbl_lo) {
						dbl_hi += 1;
					}

					dbl_lo = j;
				}
			}

			dbl_lo &= ~i;
		}
	}

	*(s32*)&x       = dbl_hi;
	*(1 + (s32*)&x) = dbl_lo;
	return x;
}
