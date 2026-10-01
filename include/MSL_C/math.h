#ifndef MSL_C_MATH_H
#define MSL_C_MATH_H

#include "types.h"

extern s32 __float_nan[];
extern s32 __float_huge[];

#define NAN       (*(float*)__float_nan)
#define HUGE_VALF (*(float*)__float_huge)

double __frsqrte(double x);
double __fabs(double x);
double atan(double x);

extern inline double sqrt(double x)
{
	if (x > 0.0) {
		double guess = __frsqrte(x);
		guess        = 0.5 * guess * (3.0 - guess * guess * x);
		guess        = 0.5 * guess * (3.0 - guess * guess * x);
		guess        = 0.5 * guess * (3.0 - guess * guess * x);
		guess        = 0.5 * guess * (3.0 - guess * guess * x);
		return x * guess;
	}
	if (x == 0.0)
		return 0.0;
	if (x)
		return NAN;
	return HUGE_VALF;
}

#endif
