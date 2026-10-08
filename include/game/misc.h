#ifndef GAME_MISC_H
#define GAME_MISC_H
#include "game/rw_types.h"
struct RpSpline;
struct NJS_LINE {
	RwV3d p, v;
};
struct sAngle {
	s32 x, y, z;
};
// GameCube retains 16-bit angle results while accepting integer angle inputs.
void ClosePositionToCamera(RwV3d* arg0, f32 farg0);
void DisplayRpSpline(RpSpline* arg0);
void RelativeCalcPoint(RwV3d* arg0, RwV3d* arg1, RwV3d* arg2, sAngle* arg3);
s32 AdjustPoint(RwV3d* arg0, const RwV3d* arg1, f32 farg0);
void njPrintColor(u32 arg0);
void njPrint2(s32 position, const char* format, ...);
void njPrint(s32 position, const char* format, ...);
f32 DistanceL2PL(const NJS_LINE* arg0, const NJS_LINE* arg1, RwV3d* arg2);
f32 DistanceL2L(const NJS_LINE* arg0, const NJS_LINE* arg1, RwV3d* arg2, RwV3d* arg3);
f32 RoundOff(f32 farg0);
f32 CrossProduct(RwV3d* arg0, RwV3d* arg1, RwV3d* arg2);
f32 DistancePL2PL(const RwV3d* arg0, const RwV3d* arg1, NJS_LINE* arg2);
f32 DistancePL2PL(const NJS_LINE* arg0, const NJS_LINE* arg1, NJS_LINE* arg2);
f32 DistanceP2PL(const RwV3d* arg0, const RwV3d* arg1, RwV3d* arg2);
f32 DistanceP2PL(const RwV3d* arg0, const NJS_LINE* arg1, RwV3d* arg2);
f32 DistanceP2L(const RwV3d* arg0, const NJS_LINE* arg1, RwV3d* arg2);
f32 Distance2P2P(const RwV3d* arg0, const RwV3d* arg1);
f32 DistanceP2P(const RwV3d* arg0, const RwV3d* arg1);
void SubVectorReturnToVector(const RwV3d* arg0, const RwV3d* arg1, RwV3d* arg2);
void AddVectorReturnToVector(const RwV3d* arg0, const RwV3d* arg1, RwV3d* arg2);
f32 AdjustFloat(f32 farg0, f32 farg1, f32 farg2);
void GetZYAngleForTheTargetPoint(const RwV3d* arg0, const RwV3d* arg1, s32* arg2);
f32 GetFloatMod(f32 farg0, f32 farg1);
s32 VectorAngleOnPlane(RwV3d* first, RwV3d* second, RwV3d* planeNormal);
s32 VectorAngle(RwV3d* first, RwV3d* second, RwV3d* orientation);
u16 DiffAngle(s32 first, s32 second);
s16 SubAngle(s32 first, s32 second);
u16 AdjustAngle(s32 first, s32 second, s32 limit);
// Provisional names for the two GameCube table lookups.
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" f32 fn_800D7B00(u16 angle);
#endif
