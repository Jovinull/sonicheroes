// Casts the object's position at 0x708 downward and reports the Y of the collision found by the
// octree, using half of field 0x89C as the lift.
#include "types.h"
#include "game/octree.h"

struct Vec80089404 {
	f32 x;
	f32 y;
	f32 z;
};

struct Obj80089404 {
	u8 pad0[0x708];
	Vec80089404 position; // 0x708
	u8 pad714[0x89C - 0x714];
	f32 unk89C; // 0x89C
};

extern "C" {
extern OCTREE* lbl_8042C150;
extern f32 lbl_8042D858;
s32 fn_80089490(POLYDATA*);

POLYDATA* fn_80089404(Obj80089404* o, f32* outY, f32 height)
{
	RwV3d start;
	RwV3d result;
	f32 offset;

	start.x = o->position.x;
	start.y = o->position.y;
	start.z = o->position.z;
	offset  = lbl_8042D858 * o->unk89C;
	start.y += offset;
	POLYDATA* poly = lbl_8042C150->DetectAxisYCollisionWithPolygons(
	    &start, -(height + offset), &result, fn_80089490);
	if (!poly)
		return 0;
	*outY = result.y;
	return poly;
}
}
