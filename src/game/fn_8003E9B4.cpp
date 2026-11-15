#include "game/matrix.h"

// Rotates a vector in place (fn_8019947C) by an action state's angle (+0xC), as fn_800EB9A0 builds
// its matrix: the rotation matrix lbl_802AD120[1] is rebuilt (by -Y about AxisY, then X about AxisX
// and Z about AxisZ) only when the angle differs from the one cached at lbl_802AD220 +0xC. Used by
// fn_800E104C and fn_800E03B4 on the player slot tables. HYPOTHESIS: RwV3dTransformVectors; the
// cache layout beyond the angle is UNKNOWN.

struct Angle8003E9B4 {
	s32 x;
	s32 y;
	s32 z;
};

struct Action8003E9B4 {
	u8 pad0[0xC];
	Angle8003E9B4 angle; // 0xC
};

extern "C" {
extern RwMatrixTag lbl_802AD120[4];
extern Action8003E9B4 lbl_802AD220;
extern const f32 lbl_8042D0E8; // 1.0f
f32 fn_800D7AE4(s32 angle);
f32 fn_800D7B00(s32 angle);
RwMatrixTag* fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
RwV3d* fn_8019947C(RwV3d* out, const RwV3d* in, s32 count, const RwMatrixTag* matrix);
}

extern "C" void fn_8003E9B4(Action8003E9B4* action, RwV3d* vector)
{
	RwMatrixTag* matrix = &lbl_802AD120[1];

	if (action->angle.x != lbl_802AD220.angle.x || action->angle.y != lbl_802AD220.angle.y
	    || action->angle.z != lbl_802AD220.angle.z) {
		lbl_802AD220.angle = action->angle;
		fn_80195790(matrix, &AxisY, lbl_8042D0E8 - fn_800D7AE4(-action->angle.y),
		    fn_800D7B00(-action->angle.y), 0);
		fn_80195790(matrix, &AxisX, lbl_8042D0E8 - fn_800D7AE4(action->angle.x),
		    fn_800D7B00(action->angle.x), 2);
		fn_80195790(matrix, &AxisZ, lbl_8042D0E8 - fn_800D7AE4(action->angle.z),
		    fn_800D7B00(action->angle.z), 2);
	}
	fn_8019947C(vector, vector, 1, matrix);
}
