#ifndef GAME_MISCS_H
#define GAME_MISCS_H

#include "game/rw_types.h"

void njInitSinTable();
f32 DistanceP2SegL(RwV3d* point, RwV3d* first, RwV3d* second, RwV3d* closest);
void GetSclXZ(s32 angle, f32 scale, f32* sine, f32* cosine);
s32 CalcV2_TimeGP(
    RwV3d* now, RwV3d* trg, f32 max_y, f32 grav, RwV3d* v0, RwV3d* v0p, s32* yAng, s32* time);
s32 CalcV2_Time(RwV3d* now, RwV3d* trg, f32 max_y, f32 grav, RwV3d* v0, s32* time);
s32 CalcV2(RwV3d* now, RwV3d* trg, f32 max_y, f32 grav, RwV3d* v0);
void DrawSphere_(RwV3d* pos, f32 size);
void DrawLine_(RwV3d* line, RwRGBA* lineColor);
s32 SetPlayerYAngle(s32 yAng);
s32 CmpAngleRelative(s32 srcYAng, s32 dstYAng);
s32 GetYangle(f32 xp, f32 zp);

#endif
