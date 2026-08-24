#include "types.h"

extern double __ieee754_log10(double x);

double log10(double x)
{
	return __ieee754_log10(x);
}
