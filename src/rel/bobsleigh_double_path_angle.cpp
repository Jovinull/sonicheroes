#include "types.h"

// TObjBobsleigh::CalcDoublePathAngle (the PS2 build's name): the attitude of
// a double path at point p0 from the two neighbouring points. The normal is
// the cross product of the two edges (flipped for kind 0) and gives the X and
// Z angles; the first edge's reverse gives the optional extra angle. The Y
// angle comes from p1 seen in the frame turned back by those angles and moved
// to p0.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

extern "C" const f32 bobsleighOne[1];
extern "C" const f32 bobsleighRadToAngle[1];
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisZ;

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, RwV3d* translation, s32 combine);
void CalcPoint(const RwMatrixTag* matrix, const RwV3d* point, RwV3d* out);
void CrossProduct(RwV3d* a, RwV3d* b, RwV3d* out);
void GetAngleXZ(f32 x, f32 y, f32 z, int* ax, int* az);
void GetAngleXY(f32 x, f32 y, f32 z, int* ax, int* ay);
extern "C" double atan2(double y, double x);

extern "C" void
CalcDoublePathAngle__13TObjBobsleighFPC5RwV3dPC5RwV3dPC5RwV3dQ213TObjBobsleigh27ENUM_CALC_DOUBLE_PATH_ANGLEP6sAngleP5RwV3dPi(
    void* object, const RwV3d* p0, const RwV3d* p1, const RwV3d* p2, int kind, sAngle* angle,
    RwV3d* normal, int* extra)
{
	RwMatrixTag matrix;
	RwV3d b;
	RwV3d a;
	int unused;

	b.x = p2->x - p0->x;
	b.y = p2->y - p0->y;
	b.z = p2->z - p0->z;
	a.x = p1->x - p0->x;
	a.y = p1->y - p0->y;
	a.z = p1->z - p0->z;
	CrossProduct(&a, &b, normal);
	if (kind == 0) {
		normal->x = -normal->x;
		normal->y = -normal->y;
		normal->z = -normal->z;
	}
	GetAngleXZ(normal->x, normal->y, normal->z, &angle->x, &angle->z);
	if (extra != NULL) {
		GetAngleXY(-a.x, -a.y, -a.z, extra, &unused);
	}
	b.x = -p0->x;
	b.y = -p0->y;
	b.z = -p0->z;
	fn_80195790(
	    &matrix, &AxisX, bobsleighOne[0] - fn_800D7AE4(-angle->x), fn_800D7B00(-angle->x), 0);
	fn_80195790(
	    &matrix, &AxisZ, bobsleighOne[0] - fn_800D7AE4(-angle->z), fn_800D7B00(-angle->z), 1);
	fn_80196050(&matrix, &b, 1);
	CalcPoint(&matrix, p1, &b);
	angle->y = bobsleighRadToAngle[0] * (f32)atan2(-b.x, -b.z);
}
