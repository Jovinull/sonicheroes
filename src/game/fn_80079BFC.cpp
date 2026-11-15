#include "types.h"

extern "C" {
f64 __frsqrte(f64);
extern const f32 lbl_8042D624; /* 0.0f */
extern const f64 lbl_8042D6D8; /* 0.5 */
extern const f64 lbl_8042D6E0; /* 3.0 */

f32 fn_80079BFC(f32 value)
{
	if (value > lbl_8042D624) {
		f64 estimate = __frsqrte(value);
		estimate = lbl_8042D6D8 * estimate * (lbl_8042D6E0 - (f64)(estimate * estimate * value));
		estimate = lbl_8042D6D8 * estimate * (lbl_8042D6E0 - (f64)(estimate * estimate * value));
		estimate = lbl_8042D6D8 * estimate * (lbl_8042D6E0 - (f64)(estimate * estimate * value));
		volatile f32 result = (f32)(value * estimate);
		return result;
	}
	return value;
}
}
