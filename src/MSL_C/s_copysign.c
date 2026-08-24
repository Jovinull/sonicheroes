#include "types.h"

double copysign(double x, double y)
{
	*(s32*)&x = (*(s32*)&x) & 0x7FFFFFFF | (*(s32*)&y) & 0x80000000;
	return x;
}
