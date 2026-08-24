#include "types.h"

extern double __ieee754_pow(double x, double y);

#pragma dont_inline on
double pow(double x, double y)
{
	return __ieee754_pow(x, y);
}

float powf(float x, float y)
{
	return pow(x, y);
}
#pragma dont_inline reset
