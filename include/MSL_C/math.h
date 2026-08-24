#ifndef MSL_C_MATH_H
#define MSL_C_MATH_H

#include "types.h"

extern s32 lbl_8042BEE8[];
extern s32 lbl_8042BEEC[];

#define NAN       (*(float*)lbl_8042BEE8)
#define HUGE_VALF (*(float*)lbl_8042BEEC)

double __frsqrte(double x);

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
