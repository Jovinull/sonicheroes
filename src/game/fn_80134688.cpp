// Tests for ground below a point while the current player is in state 3 (HYPOTHESIS; names
// inferred): casts a line from the point, lowered by lbl_8042EFC0, along the vector
// (lbl_8042EFC4, lbl_8042EFC8, lbl_8042EFC4) through the collision octree lbl_8042C150. Returns
// whether it hit a polygon; 0 in any other state.
#include "game/octree.h"

struct Player80134688 {
	u8 pad0[0x140];
	s32 state; // 0x140
};

extern OCTREE* lbl_8042C150;

extern "C" {
// Player objects indexed by the current player number (HYPOTHESIS).
extern Player80134688* lbl_80303DC8[];
extern s32 lbl_8042C1FC;
extern f32 lbl_8042EFC0;
extern f32 lbl_8042EFC4;
extern f32 lbl_8042EFC8;

s32 fn_80134688(RwV3d* point)
{
	RwV3d start;
	RwV3d line;
	RwV3d hit;

	if (lbl_80303DC8[lbl_8042C1FC]->state != 3) {
		return 0;
	}
	start = *point;
	start.y -= lbl_8042EFC0;
	line.x = lbl_8042EFC4;
	line.y = lbl_8042EFC8;
	line.z = lbl_8042EFC4;
	return lbl_8042C150->DetectLineCollisionWithPolygons(&start, &line, &hit, 0) != 0;
}
}
