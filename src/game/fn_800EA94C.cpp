#include "types.h"

// atan2 rounded to a float.

extern "C" f64 atan2(f64 y, f64 x);

extern "C" f32 fn_800EA94C(f64 y, f64 x)
{
	return (f32)atan2(y, x);
}
