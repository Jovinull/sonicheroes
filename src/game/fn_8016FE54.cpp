// Appends a point to the 2D path of an object: the new 0x18-byte point (type 1) stores its
// position, the unit normal of the segment from the previous point, and the running path length;
// once the path has more than one point, the previous point's normal becomes the miter of the two
// segment normals (their sum scaled by 1 / dot(previous, sum)). Names are HYPOTHESIS; returns the
// object.
// NonMatching: retail copies the normal in the single-point case with two integer word moves
// (lwz/stw), while this struct assignment compiles to lfs/stfs (4 words differ). Field copies, an
// inline assignment helper, memcpy and compilers 2.0/2.6 give the same or worse result.
#include "game/rw_engine.h"

struct V2d8016FE54 {
	f32 x;
	f32 y;
};

// Path point (layout from this function only).
struct Point8016FE54 {
	s32 type;           // 0x0
	V2d8016FE54 pos;    // 0x4
	V2d8016FE54 normal; // 0xC
	f32 length;         // 0x14: path length up to this point
};

struct Path8016FE54 {
	RwSList* points; // 0x0
};

struct Obj8016FE54 {
	u8 pad0[0x18];
	Path8016FE54* path; // 0x18
};

extern "C" {
extern f32 lbl_8042F47C; // 1.0f
// HYPOTHESIS: _rwSListGetNumEntries, _rwSListGetNewEntry, RwSqrt and RwInvSqrt.
s32 fn_8019469C(RwSList* sList);
void* fn_80194430(RwSList* sList);
f32 fn_801991F4(f32 value);
f32 fn_80199248(f32 value);

Obj8016FE54* fn_8016FE54(Obj8016FE54* object, f32 x, f32 y)
{
	s32 count            = fn_8019469C(object->path->points);
	Point8016FE54* point = (Point8016FE54*)fn_80194430(object->path->points);
	Point8016FE54* prev  = point - 1;
	f32 dy;
	f32 dx;
	f32 lengthSq;
	f32 length;
	f32 invLength;

	point->type  = 1;
	point->pos.x = x;
	point->pos.y = y;

	dy              = y - prev->pos.y;
	dx              = prev->pos.x - x;
	lengthSq        = dy * dy + dx * dx;
	length          = fn_801991F4(lengthSq);
	invLength       = fn_80199248(lengthSq);
	point->normal.x = dy * invLength;
	point->normal.y = dx * invLength;
	point->length   = prev->length + length;

	if (count > 1) {
		f32 sx         = prev->normal.x + point->normal.x;
		f32 sy         = prev->normal.y + point->normal.y;
		f32 scale      = lbl_8042F47C / (prev->normal.x * sx + prev->normal.y * sy);
		prev->normal.x = sx * scale;
		prev->normal.y = sy * scale;
	} else {
		prev->normal = point->normal;
	}
	return object;
}
}
