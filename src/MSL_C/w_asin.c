#include "types.h"

extern double __ieee754_asin(double x);

double asin(double x)
{
	return __ieee754_asin(x);
}
