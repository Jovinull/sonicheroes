#include "types.h"

extern double __ieee754_fmod(double x, double y);

double fmod(double x, double y)
{
	return __ieee754_fmod(x, y);
}
