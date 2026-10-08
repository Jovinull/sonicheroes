#ifndef GAME_MATRIX_H
#define GAME_MATRIX_H

#include "types.h"

struct RwV2d {
	f32 x, y;
};
struct RwV3d {
	f32 x, y, z;
};
struct RwMatrixTag {
	RwV3d right;
	u32 flags;
	RwV3d up;
	u32 pad1;
	RwV3d at;
	u32 pad2;
	RwV3d pos;
	u32 pad3;
};

extern RwMatrixTag* pCurrentMatrix;
extern RwMatrixTag MatrixStack[64];
extern const RwV3d AxisX, AxisY, AxisZ;

void ProjectScreen(RwMatrixTag*, RwV3d*, RwV2d*);
void njInvertMatrix(RwMatrixTag*);
void CalcVector(const RwMatrixTag*, const RwV3d*, RwV3d*);
void CalcPoints(const RwMatrixTag*, const RwV3d*, RwV3d*, u32);
void CalcPoint(const RwMatrixTag*, const RwV3d*, RwV3d*);
void RotateZ(RwMatrixTag*, s32);
void RotateY(RwMatrixTag*, s32);
void RotateX(RwMatrixTag*, s32);
void PushUnitMatrix();
void PopMatrixEx();
s32 PopMatrix(u32);
void PushMatrixEx();
s32 PushMatrix(RwMatrixTag*);
void UnitMatrixEx();
void UnitMatrix(RwMatrixTag*);
void InitMatrix();

#endif
