// Tests whether a point lies inside a closed 2D path (HYPOTHESIS: Rt2dPathInside-style crossing
// count): counts the path segments a ray towards -x from the point crosses, using the same point
// layout as fn_8016FE54 (a raw array, or a growable array when the count is -1). Returns 1 for an
// odd number of crossings.
#include "game/rw_engine.h"

struct V2d80171EB8 {
	f32 x;
	f32 y;
};

struct Point80171EB8 {
	s32 type;        // 0x0
	V2d80171EB8 pos; // 0x4
	u8 padC[0x18 - 0xC];
};

struct PathSource80171EB8 {
	void* points; // 0x0
	s32 count;    // 0x4: -1 when points is an RwSList
};

#define MIN_80171EB8(a, b) (((a) <= (b)) ? (a) : (b))
#define MAX_80171EB8(a, b) (((a) >= (b)) ? (a) : (b))

extern "C" {
// HYPOTHESIS: _rwSListGetArray and _rwSListGetNumEntries.
void* fn_8019460C(RwSList* sList);
s32 fn_8019469C(RwSList* sList);

s32 fn_80171EB8(const V2d80171EB8* point, PathSource80171EB8* path)
{
	Point80171EB8* points;
	s32 crossings;
	s32 i;
	Point80171EB8* next;
	Point80171EB8* cur;

	crossings = 0;
	if (path->count == -1) {
		points = (Point80171EB8*)fn_8019460C((RwSList*)path->points);
	} else {
		points = (Point80171EB8*)path->points;
	}
	cur  = points;
	next = points;
	for (i = 0; i < ((path->count == -1) ? fn_8019469C((RwSList*)path->points) : path->count) - 1;
	    i++) {
		next++;
		if (point->y > MIN_80171EB8(cur->pos.y, next->pos.y)
		    && point->y <= MAX_80171EB8(cur->pos.y, next->pos.y)
		    && point->x <= MAX_80171EB8(cur->pos.x, next->pos.x) && cur->pos.y != next->pos.y) {
			f32 crossX
			    = (point->y - cur->pos.y) * (next->pos.x - cur->pos.x) / (next->pos.y - cur->pos.y)
			    + cur->pos.x;
			if (cur->pos.x == next->pos.x || point->x <= crossX) {
				crossings++;
			}
		}
		cur++;
	}
	return (crossings % 2) ? 1 : 0;
}
}
