// Stores minus the cosine of angle at +0x28 of the object when angle lies within
// [lbl_8042F320, lbl_8042F328]. Returns the object, or null when the angle is out of range.
#include "game/rw_engine.h"

struct Object80154160 {
	u8 pad0[0x28];
	f32 f28; // 0x28
};

extern "C" {
double cos(double x);
// .sdata2 range limits (non-const: see RW_MATRIX_SET_IDENTITY).
extern f32 lbl_8042F320;
extern f32 lbl_8042F328;

Object80154160* fn_80154160(Object80154160* object, f32 angle)
{
	if (angle < lbl_8042F320 || angle > lbl_8042F328) {
		return 0;
	}
	object->f28 = -(f32)cos(angle);
	return object;
}
}
