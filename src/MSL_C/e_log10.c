#include "types.h"

extern s32 errno;
extern double __ieee754_log(double x);

static const double two54     = 1.80143985094819840000e+16;
static const double ivln10    = 4.34294481903251816668e-01;
static const double log10_2hi = 3.01029995663611771306e-01;
static const double log10_2lo = 3.69423907715893078616e-13;
static double zero            = 0.0;

double __ieee754_log10(double x)
{
	double y, z;
	s32 i, k, hx;
	u32 lx;

	hx = *(s32*)&x;
	lx = *((u32*)&x + 1);
	k  = 0;

	if (hx < 0x00100000) {
		if (((hx & 0x7FFFFFFF) | lx) == 0) {
			errno = 0x21;
			return -two54 / zero;
		}

		if (hx < 0) {
			errno = 0x21;
			return (x - x) / zero;
		}

		k -= 54;
		x *= two54;
		hx = *(s32*)&x;
	}

	if (hx >= 0x7FF00000)
		return x + x;

	k += (hx >> 20) - 1023;
	i         = ((u32)k & 0x80000000) >> 31;
	hx        = (hx & 0x000FFFFF) | ((0x3FF - i) << 20);
	y         = (double)(k + i);
	*(s32*)&x = hx;
	z         = y * log10_2lo + ivln10 * __ieee754_log(x);
	return z + y * log10_2hi;
}
