#include "game/matrix.h"

// The inverse of fn_8003E9B4: rotates a vector in place (fn_8019947C) by the inverse of an action
// state's angle (+0xC), by -Z about AxisZ, then -X about AxisX and Y about AxisY. The matrix
// lbl_802AD120[0] is rebuilt only when the angle differs from the one cached at lbl_802AD220 +0x0.
// Used to turn velocities into the action's frame (fn_800E09F0, fn_800EE9FC). HYPOTHESIS:
// RwV3dTransformVectors; the cache layout beyond the two angles is UNKNOWN.

struct Angle8003EB18 {
	s32 x;
	s32 y;
	s32 z;
};

struct Action8003EB18 {
	u8 pad0[0xC];
	Angle8003EB18 angle; // 0xC
};

struct Cache8003EB18 {
	Angle8003EB18 inverse; // 0x0 (this function)
	Angle8003EB18 forward; // 0xC (fn_8003E9B4)
};

extern "C" {
extern RwMatrixTag lbl_802AD120[4];
extern Cache8003EB18 lbl_802AD220;
extern const f32 lbl_8042D0E8; // 1.0f
f32 fn_800D7AE4(s32 angle);
f32 fn_800D7B00(s32 angle);
RwMatrixTag* fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
RwV3d* fn_8019947C(RwV3d* out, const RwV3d* in, s32 count, const RwMatrixTag* matrix);
}

extern "C" void fn_8003EB18(Action8003EB18* action, RwV3d* vector)
{
	RwMatrixTag* matrix = &lbl_802AD120[0];

	if (action->angle.x != lbl_802AD220.inverse.x || action->angle.y != lbl_802AD220.inverse.y
	    || action->angle.z != lbl_802AD220.inverse.z) {
		lbl_802AD220.inverse = action->angle;
		fn_80195790(matrix, &AxisZ, lbl_8042D0E8 - fn_800D7AE4(-action->angle.z),
		    fn_800D7B00(-action->angle.z), 0);
		fn_80195790(matrix, &AxisX, lbl_8042D0E8 - fn_800D7AE4(-action->angle.x),
		    fn_800D7B00(-action->angle.x), 2);
		fn_80195790(matrix, &AxisY, lbl_8042D0E8 - fn_800D7AE4(action->angle.y),
		    fn_800D7B00(action->angle.y), 2);
	}
	fn_8019947C(vector, vector, 1, matrix);
}
