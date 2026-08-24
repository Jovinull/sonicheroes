#include "types.h"

extern double __ieee754_acos(double x);

double acos(double x)
{
	return __ieee754_acos(x);
}
