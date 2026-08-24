#include "types.h"

extern double cos(double x);

__declspec(weak) float cosf(float x)
{
	return cos(x);
}
