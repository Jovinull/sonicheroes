#include "types.h"

struct TFn80051F68Angles {
	s32 mX;
	s32 mY;
};

struct TFn80051F68Vector {
	f32 mX;
	f32 mY;
	f32 mZ;
};

extern "C" {
extern f32 lbl_8042D374;
extern f32 lbl_8042D388;

void CalcVector__FPC11RwMatrixTagPC5RwV3dP5RwV3d(
    void*, const TFn80051F68Vector*, TFn80051F68Vector*);
void PopMatrix__FUi(u32);
void PushMatrix__FP11RwMatrixTag(void*);
void RotateX__FP11RwMatrixTagi(void*, s32);
void RotateY__FP11RwMatrixTagi(void*, s32);
void UnitMatrix__FP11RwMatrixTag(void*);
}

extern "C" void fn_80051F68(void* arg0, TFn80051F68Angles* arg1, TFn80051F68Vector* arg2)
{
	register TFn80051F68Angles* temp_r30 = arg1;
	register TFn80051F68Vector* temp_r31 = arg2;
	f32 temp_f0                          = lbl_8042D374;

	(void)arg0;
	temp_r31->mX = temp_f0;
	temp_r31->mY = temp_f0;
	temp_r31->mZ = lbl_8042D388;
	PushMatrix__FP11RwMatrixTag(0);
	UnitMatrix__FP11RwMatrixTag(0);
	RotateY__FP11RwMatrixTagi(0, temp_r30->mY);
	RotateX__FP11RwMatrixTagi(0, temp_r30->mX);
	CalcVector__FPC11RwMatrixTagPC5RwV3dP5RwV3d(0, temp_r31, temp_r31);
	PopMatrix__FUi(1);
}
