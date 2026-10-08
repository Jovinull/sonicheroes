#ifndef GAME_CALC_H
#define GAME_CALC_H

#include "types.h"

struct RwMatrixTag;

f32 InterDivPosF(f32 p1, f32 p2, f32 d1, f32 d2);
s32 InterDivAngF(s32 a1, s32 a2, f32 d1, f32 d2);
void GetAngleYZ(f32 dx, f32 dy, f32 dz, s32* ay, s32* az);
void GetAngleXZ(f32 dx, f32 dy, f32 dz, s32* ax, s32* az);
void GetAngleXY(f32 dx, f32 dy, f32 dz, s32* ax, s32* ay);
void GetRotZXY(RwMatrixTag* mat, s32* ax, s32* ay, s32* az);
void GetRotYXZ(RwMatrixTag* mat, s32* ax, s32* ay, s32* az);
void GetRotXYZ(RwMatrixTag* mat, s32* ax, s32* ay, s32* az);

#endif
