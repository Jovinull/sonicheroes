#include "types.h"

// Turns the module's base direction (x = y = lbl_8042D374, z = lbl_8042D388)
// by the given Y and then X angles into out, through the current matrix stack
// (push, identity, RotateY, RotateX, CalcVector, pop). The first argument is
// unused.

struct AngleXY {
	s32 x;
	s32 y;
};

struct Vector3 {
	f32 x;
	f32 y;
	f32 z;
};

extern "C" {
extern f32 lbl_8042D374;
extern f32 lbl_8042D388;
void CalcVector__FPC11RwMatrixTagPC5RwV3dP5RwV3d(void*, const Vector3*, Vector3*);
void PopMatrix__FUi(u32);
void PushMatrix__FP11RwMatrixTag(void*);
void RotateX__FP11RwMatrixTagi(void*, s32);
void RotateY__FP11RwMatrixTagi(void*, s32);
void UnitMatrix__FP11RwMatrixTag(void*);
}

extern "C" void fn_80051F68(void* self, AngleXY* angle, Vector3* out)
{
	register AngleXY* turn = angle;
	register Vector3* dir  = out;
	f32 base               = lbl_8042D374;
	(void)self;

	dir->x = base;
	dir->y = base;
	dir->z = lbl_8042D388;
	PushMatrix__FP11RwMatrixTag(0);
	UnitMatrix__FP11RwMatrixTag(0);
	RotateY__FP11RwMatrixTagi(0, turn->y);
	RotateX__FP11RwMatrixTagi(0, turn->x);
	CalcVector__FPC11RwMatrixTagPC5RwV3dP5RwV3d(0, dir, dir);
	PopMatrix__FUi(1);
}
