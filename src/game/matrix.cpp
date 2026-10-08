#include "game/matrix.h"

// PS2 DWARF identifies matrix.cpp as C++ and records all sixteen API functions,
// the 64-element MatrixStack, pCurrentMatrix and the three axis vectors.
// GameCube calls, shared storage and contiguous function order independently
// correlate this unit with .text 0x8001EED8-0x8001F4E8.

// Only the camera fields accessed by this unit are reconstructed here.
struct MatrixCamera {
	u8 unk_0x00[0x20];
	RwMatrixTag viewMatrix;
};
struct MatrixCameraTask {
	u8 unk_0x00[0x28];
	MatrixCamera* camera;
};

extern "C" {
extern MatrixCameraTask* lbl_8042C1F8;
RwV3d* fn_8019941C(RwV3d*, const RwV3d*, s32, const RwMatrixTag*);
RwV3d* fn_8019947C(RwV3d*, const RwV3d*, s32, const RwMatrixTag*);
RwMatrixTag* fn_80195B5C(RwMatrixTag*, const RwMatrixTag*);
RwMatrixTag* fn_80195790(RwMatrixTag*, const RwV3d*, f32, f32, s32);
f32 fn_800D7B00(s32);
f32 fn_800D7AE4(s32);
}

RwMatrixTag* pCurrentMatrix;
RwMatrixTag MatrixStack[64];
const RwV3d AxisX = { 1.0f, 0.0f, 0.0f };
const RwV3d AxisY = { 0.0f, 1.0f, 0.0f };
const RwV3d AxisZ = { 0.0f, 0.0f, 1.0f };

void ProjectScreen(RwMatrixTag* m, RwV3d* p3, RwV2d* p2)
{
	RwMatrixTag* mat = m;
	RwV3d getPos;
	if (!m)
		mat = &lbl_8042C1F8->camera->viewMatrix;
	fn_8019941C(&getPos, p3, 1, mat);
	p2->x = 640.0f * (getPos.x / getPos.z);
	p2->y = 480.0f * (getPos.y / getPos.z);
}

void njInvertMatrix(RwMatrixTag* mat)
{
	RwMatrixTag dest;
	if (!mat)
		mat = pCurrentMatrix;
	fn_80195B5C(&dest, mat);
	*mat = dest;
}

void CalcVector(const RwMatrixTag* mat, const RwV3d* src, RwV3d* dest)
{
	if (!mat)
		mat = pCurrentMatrix;
	fn_8019947C(dest, src, 1, mat);
}

void CalcPoints(const RwMatrixTag* mat, const RwV3d* src, RwV3d* dest, u32 count)
{
	if (!mat)
		mat = pCurrentMatrix;
	fn_8019941C(dest, src, count, mat);
}

void CalcPoint(const RwMatrixTag* mat, const RwV3d* src, RwV3d* dest)
{
	if (!mat)
		mat = pCurrentMatrix;
	fn_8019941C(dest, src, 1, mat);
}

void RotateZ(RwMatrixTag* mat, s32 angle)
{
	if (!mat)
		mat = pCurrentMatrix;
	f32 sine           = fn_800D7B00(angle);
	f32 oneMinusCosine = 1.0f - fn_800D7AE4(angle);
	fn_80195790(mat, &AxisZ, oneMinusCosine, sine, 1);
}

void RotateY(RwMatrixTag* mat, s32 angle)
{
	if (!mat)
		mat = pCurrentMatrix;
	f32 sine           = fn_800D7B00(angle);
	f32 oneMinusCosine = 1.0f - fn_800D7AE4(angle);
	fn_80195790(mat, &AxisY, oneMinusCosine, sine, 1);
}

void RotateX(RwMatrixTag* mat, s32 angle)
{
	if (!mat)
		mat = pCurrentMatrix;
	f32 sine           = fn_800D7B00(angle);
	f32 oneMinusCosine = 1.0f - fn_800D7AE4(angle);
	fn_80195790(mat, &AxisX, oneMinusCosine, sine, 1);
}

void PushUnitMatrix()
{
	++pCurrentMatrix;
	pCurrentMatrix->right.x = pCurrentMatrix->up.y = pCurrentMatrix->at.z = 1.0f;
	pCurrentMatrix->pos.x = pCurrentMatrix->pos.y = pCurrentMatrix->pos.z = pCurrentMatrix->up.z
	    = pCurrentMatrix->at.x = pCurrentMatrix->at.y = pCurrentMatrix->right.y
	    = pCurrentMatrix->right.z = pCurrentMatrix->up.x = 0.0f;
	pCurrentMatrix->flags |= 0x20003;
}

void PopMatrixEx()
{
	--pCurrentMatrix;
}
s32 PopMatrix(u32)
{
	return 0;
}

void PushMatrixEx()
{
	RwMatrixTag* src = pCurrentMatrix++;
	*pCurrentMatrix  = *src;
}

s32 PushMatrix(RwMatrixTag*)
{
	return 0;
}

void UnitMatrixEx()
{
	pCurrentMatrix->right.x = pCurrentMatrix->up.y = pCurrentMatrix->at.z = 1.0f;
	pCurrentMatrix->pos.x = pCurrentMatrix->pos.y = pCurrentMatrix->pos.z = pCurrentMatrix->up.z
	    = pCurrentMatrix->at.x = pCurrentMatrix->at.y = pCurrentMatrix->right.y
	    = pCurrentMatrix->right.z = pCurrentMatrix->up.x = 0.0f;
	pCurrentMatrix->flags |= 0x20003;
}

void UnitMatrix(RwMatrixTag* mat)
{
	if (!mat) {
		UnitMatrixEx();
		return;
	}
	mat->right.x = mat->up.y = mat->at.z = 1.0f;
	mat->pos.x = mat->pos.y = mat->pos.z = mat->up.z = mat->at.x = mat->at.y = mat->right.y
	    = mat->right.z = mat->up.x = 0.0f;
	mat->flags |= 0x20003;
}

void InitMatrix()
{
	pCurrentMatrix = MatrixStack;
}
