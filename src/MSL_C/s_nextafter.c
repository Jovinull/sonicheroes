#include "types.h"

double nextafter(double x, double y)
{
	s32 hx, hy, ix, iy;
	u32 lx, ly;

	hx = *(s32*)&x;
	lx = *(1 + (s32*)&x);
	hy = *(s32*)&y;
	ly = *(1 + (s32*)&y);
	ix = hx & 0x7FFFFFFF;
	iy = hy & 0x7FFFFFFF;

	if (((ix >= 0x7FF00000) && ((ix - 0x7FF00000) | lx) != 0)
	    || ((iy >= 0x7FF00000) && ((iy - 0x7FF00000) | ly) != 0)) {
		return x + y;
	}

	if (x == y) {
		return x;
	}

	if ((ix | lx) == 0) {
		*(s32*)&x       = hy & 0x80000000;
		*(1 + (s32*)&x) = 1;
		y               = x * x;
		if (y == x) {
			return y;
		} else {
			return x;
		}
	}

	if (hx >= 0) {
		if (hx > hy || ((hx == hy) && (lx > ly))) {
			if (lx == 0) {
				hx -= 1;
			}
			lx -= 1;
		} else {
			lx += 1;
			if (lx == 0) {
				hx += 1;
			}
		}
	} else {
		if (hy >= 0 || hx > hy || ((hx == hy) && (lx > ly))) {
			if (lx == 0) {
				hx -= 1;
			}
			lx -= 1;
		} else {
			lx += 1;
			if (lx == 0) {
				hx += 1;
			}
		}
	}

	hy = hx & 0x7FF00000;
	if (hy >= 0x7FF00000) {
		return x + x;
	}

	if (hy < 0x00100000) {
		y = x * x;
		if (y != x) {
			*(s32*)&y       = hx;
			*(1 + (s32*)&y) = lx;
			return y;
		}
	}

	*(s32*)&x       = hx;
	*(1 + (s32*)&x) = lx;
	return x;
}
