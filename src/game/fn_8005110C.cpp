#include "game/matrix.h"

// Whether a point lies inside an oriented box (the first argument is unused): the box (centre,
// half-extent and angle pointers, then the point) is rejected at once when the point is farther
// from the centre than the extent's length; otherwise the point is brought into the box frame
// (the inverse, fn_80195B5C, of the box matrix: translation to the centre, then rotations by Z, X
// and Y with fn_80195790 and lbl_8042D360 - cos) and compared with the extent on each axis.
// HYPOTHESIS: RwV3dTransformPoints (fn_8019941C); the roles are UNKNOWN. Built with -bool off: the
// last comparison is returned without a byte clip.

struct Angle8005110C {
	s32 x;
	s32 y;
	s32 z;
};

struct Box8005110C {
	RwV3d* center;        // 0x0
	RwV3d* extent;        // 0x4
	Angle8005110C* angle; // 0x8
	RwV3d* point;         // 0xC
};

extern "C" {
extern const f32 lbl_8042D360; // 1.0f
f32 fn_800D7AE4(s32 angle);
f32 fn_800D7B00(s32 angle);
RwMatrixTag* fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
RwMatrixTag* fn_80196050(RwMatrixTag* matrix, const RwV3d* translation, s32 combine);
void fn_80195B5C(RwMatrixTag* dst, const RwMatrixTag* src);
RwV3d* fn_8019941C(RwV3d* out, const RwV3d* in, s32 count, const RwMatrixTag* matrix);
}

extern "C" s32 fn_8005110C(void* unused, Box8005110C* box)
{
	RwV3d* center = box->center;
	f32 dx        = center->x - box->point->x;
	f32 dy        = center->y - box->point->y;
	f32 dz        = center->z - box->point->z;
	if (dz * dz + (dx * dx + dy * dy) > box->extent->z * box->extent->z
	        + (box->extent->x * box->extent->x + box->extent->y * box->extent->y)) {
		return 0;
	}
	RwMatrixTag matrix;
	RwMatrixTag inverse;
	RwV3d local;
	fn_80196050(&matrix, center, 0);
	fn_80195790(
	    &matrix, &AxisZ, lbl_8042D360 - fn_800D7AE4(box->angle->z), fn_800D7B00(box->angle->z), 1);
	fn_80195790(
	    &matrix, &AxisX, lbl_8042D360 - fn_800D7AE4(box->angle->x), fn_800D7B00(box->angle->x), 1);
	fn_80195790(
	    &matrix, &AxisY, lbl_8042D360 - fn_800D7AE4(box->angle->y), fn_800D7B00(box->angle->y), 1);
	fn_80195B5C(&inverse, &matrix);
	fn_8019941C(&local, box->point, 1, &inverse);
	if (local.x > box->extent->x) {
		return 0;
	}
	if (local.x < -box->extent->x) {
		return 0;
	}
	if (local.y > box->extent->y) {
		return 0;
	}
	if (local.y < -box->extent->y) {
		return 0;
	}
	if (local.z > box->extent->z) {
		return 0;
	}
	return !(local.z < -box->extent->z);
}
