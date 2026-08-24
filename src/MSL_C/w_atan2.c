#include "types.h"

extern double __ieee754_atan2(double y, double x);

double atan2(double y, double x)
{
	return __ieee754_atan2(y, x);
}
