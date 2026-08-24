#include "types.h"

const double lbl_8042FD88 = 0.0;

double modf(double x, double* iptr)
{
	s32 i0, i1, j0;
	u32 i;

	i0 = *(s32*)&x;
	i1 = *(1 + (s32*)&x);
	j0 = ((i0 >> 20) & 0x7FF) - 0x3FF;

	if (j0 < 20) {
		if (j0 < 0) {
			*(s32*)iptr       = i0 & 0x80000000;
			*(1 + (s32*)iptr) = 0;
			return x;
		} else {
			i = 0xFFFFF >> j0;
			if (((i0 & i) | i1) == 0) {
				*iptr = x;
				*(s32*)&x &= 0x80000000;
				*(1 + (s32*)&x) = 0;
				return x;
			} else {
				*(s32*)iptr       = i0 & ~i;
				*(1 + (s32*)iptr) = 0;
				return x - *iptr;
			}
		}
	} else if (j0 > 51) {
		*iptr = x;
		*(s32*)&x &= 0x80000000;
		*(1 + (s32*)&x) = 0;
		return x;
	} else {
		i = 0xFFFFFFFF >> (j0 - 20);
		if ((i1 & i) == 0) {
			*iptr = x;
			*(s32*)&x &= 0x80000000;
			*(1 + (s32*)&x) = 0;
			return x;
		} else {
			*(s32*)iptr       = i0;
			*(1 + (s32*)iptr) = i1 & ~i;
			return x - *iptr;
		}
	}
}
