#include "types.h"

// Keeping the bounds as vector aggregates preserves the retail floating-point
// live ranges and register allocation across the recursive traversal.

struct Fn80055470Vec {
	f32 x;
	f32 y;
	f32 z;
};
struct Fn80055470Result {
	u16 value;
	u16 padding;
	Fn80055470Result* previous;
	Fn80055470Result* next;
};
struct Fn80055470Node {
	u16 value;
	u8 padding[2];
	u16 firstChild;
	u8 padding2[8];
	u16 count;
	u8 padding3[8];
	u8 level;
	u8 padding4[7];
};
struct Fn80055470Grid {
	Fn80055470Node* root;
	u8 padding[80];
	f32 cellExtents[1];
};

extern "C" u32 lbl_80242B28[4];
extern "C" void fn_8005430C(Fn80055470Grid*, const Fn80055470Node*, Fn80055470Vec*);
extern "C" Fn80055470Result* fn_8005428C(Fn80055470Result*, u16);

extern "C" Fn80055470Result* fn_80055470(Fn80055470Grid* grid, Fn80055470Result* result,
    Fn80055470Node* node, const Fn80055470Vec* upper, const Fn80055470Vec* lower)
{
	Fn80055470Vec center;
	Fn80055470Vec maximum;
	Fn80055470Vec minimum;
	f32 extent = grid->cellExtents[node->level];
	fn_8005430C(grid, node, &center);
	maximum.x = center.x + extent;
	maximum.z = center.z + extent;
	minimum.x = center.x - extent;
	minimum.z = center.z - extent;

	if (lower->x <= minimum.x && maximum.x <= upper->x && lower->z <= minimum.z
	    && maximum.z <= upper->z) {
		if (node->count != 0)
			result = fn_8005428C(result, node->value);
		return result;
	}
	if (node->firstChild != 0) {
		u8 selection = 0;
		if (upper->x < center.x)
			selection = 0xA;
		else if (center.x < lower->x)
			selection = 5;
		if (upper->z < center.z)
			selection |= 0xC;
		else if (center.z < lower->z)
			selection |= 3;
		for (s32 index = 0; index < 4; index++) {
			if ((s32)(selection & lbl_80242B28[index]) == 0)
				result = fn_80055470(
				    grid, result, &grid->root[node->firstChild + index], upper, lower);
		}
	} else if (node->count != 0) {
		if (((lower->x <= minimum.x && minimum.x <= upper->x)
		        || (minimum.x <= lower->x && lower->x <= maximum.x))
		    && ((lower->z <= minimum.z && minimum.z <= upper->z)
		        || (minimum.z <= lower->z && lower->z <= maximum.z)))
			result = fn_8005428C(result, node->value);
	}
	return result;
}
