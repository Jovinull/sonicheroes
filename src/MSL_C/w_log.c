#include "types.h"

extern double __ieee754_log(double x);

double log(double x)
{
	return __ieee754_log(x);
}
