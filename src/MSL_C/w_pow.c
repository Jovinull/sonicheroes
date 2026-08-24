#include "types.h"

extern double __ieee754_pow(double x, double y);

double pow(double x, double y)
{
	return __ieee754_pow(x, y);
}
