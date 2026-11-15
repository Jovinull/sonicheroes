#include "game/matrix.h"

// Rebuilds an object's rotation matrix (+0xCC) and its inverse (+0x10C, fn_80195B5C) from an
// angle when it differs from the object's angle (+0x74; not updated here). With flag 0x400 the
// angle's X and Z are first replaced by the pitch and yaw of a direction (fn_8003FE68). The matrix
// is the rotation by -Y about AxisY, then by X about AxisX and Z about AxisZ (fn_80195790 with
// 1 - cos and sin; fn_800D7AE4/fn_800D7B00 are cosine and sine). HYPOTHESIS: the roles are UNKNOWN.

struct Angle800EB9A0 {
	s32 x;
	s32 y;
	s32 z;
};

struct Object800EB9A0 {
	u8 pad0[0x74];
	Angle800EB9A0 angle; // 0x74
	u8 pad80[0xCC - 0x80];
	RwMatrixTag rotation; // 0xCC
	RwMatrixTag inverse;  // 0x10C
};

extern "C" {
extern const f32 lbl_8042E250; // 1.0f
f32 fn_800D7AE4(s32 angle);
f32 fn_800D7B00(s32 angle);
RwMatrixTag* fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
void fn_80195B5C(RwMatrixTag* dst, const RwMatrixTag* src);
void fn_8003FE68(f32 x, f32 z, f32 y, s32* pitch, s32* yaw);
}

extern "C" void fn_800EB9A0(
    Object800EB9A0* object, const Angle800EB9A0* angle, u32 flags, const RwV3d* direction)
{
	if (object->angle.x == angle->x && object->angle.y == angle->y && object->angle.z == angle->z) {
		return;
	}
	Angle800EB9A0 a = *angle;
	if (flags & 0x400) {
		fn_8003FE68(direction->x, direction->y, direction->z, &a.x, &a.z);
	}
	fn_80195790(&object->rotation, &AxisY, lbl_8042E250 - fn_800D7AE4(-a.y), fn_800D7B00(-a.y), 0);
	fn_80195790(&object->rotation, &AxisX, lbl_8042E250 - fn_800D7AE4(a.x), fn_800D7B00(a.x), 2);
	fn_80195790(&object->rotation, &AxisZ, lbl_8042E250 - fn_800D7AE4(a.z), fn_800D7B00(a.z), 2);
	fn_80195B5C(&object->inverse, &object->rotation);
}
