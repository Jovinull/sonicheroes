// Complete vertical_colli.cpp unit, identified by C++ symbolic metadata.
#include "game/vertical_colli.h"

struct POLYDATA {
	u16 vertexIndexNo[3];
	u16 neighbor[3];
	RwV3d norm;
	u32 attribute;
	u16 groupIndexNo;
	u8 dummy[2];
};
// Only the external collision interface is needed here; this TU owns no OCTREE.
class OCTREE
{
public:
	POLYDATA* DetectAxisYCollisionWithPolygons(const RwV3d*, f32, RwV3d*, s32 (*)(POLYDATA*));
};
extern "C" {
extern OCTREE* lbl_8042C150;
f64 atan2(f64, f64);
f64 asin(f64);
}
static s32 callbackDetectPolygon(POLYDATA*);
static s32 callbackDetectPolygonWithoutWater(POLYDATA*);

f32 GetShadowPos(RwV3d* pPos, sAngle* pAng, s32 IgnoreWater)
{
	RwV3d startPos;
	RwV3d coliPos;
	POLYDATA* coliPoly;
	f32 tmpy;
	if (!lbl_8042C150)
		return -1000000.0f;
	startPos.x = pPos->x;
	startPos.y = pPos->y;
	startPos.z = pPos->z;
	startPos.y += 1.0f;
	if (IgnoreWater == 1
	    && (coliPoly = lbl_8042C150->DetectAxisYCollisionWithPolygons(
	            &startPos, -250.0f, &coliPos, callbackDetectPolygonWithoutWater))) {
		tmpy = coliPos.y;
	} else if (IgnoreWater == 0
	    && (coliPoly = lbl_8042C150->DetectAxisYCollisionWithPolygons(
	            &startPos, -250.0f, &coliPos, callbackDetectPolygon))) {
		tmpy = coliPos.y;
	} else {
		return -1000000.0f;
	}
	if (pAng) {
		pAng->z = -(s32)(10430.381f * (f32)atan2(coliPoly->norm.x, coliPoly->norm.y));
		pAng->x = (s32)(10430.381f * (f32)asin(coliPoly->norm.z));
	}
	return tmpy;
}
static s32 callbackDetectPolygon(POLYDATA*)
{
	return 1;
}
static s32 callbackDetectPolygonWithoutWater(POLYDATA*)
{
	return 1;
}
