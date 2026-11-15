// Whether the line from `pos` along lbl_80239F28 hits a polygon of the stage octree
// (lbl_8042C158) accepted by the filter fn_800A2E1C; 0 when there is no octree. The first argument
// is unused (HYPOTHESIS: the enemy). HYPOTHESIS: a ground probe below an enemy (CheckDamage2 does
// the same test with its position).
#include "game/octree.h"

extern "C" {
extern OCTREE* lbl_8042C158;
extern const RwV3d lbl_80239F28;
s32 fn_800A2E1C(POLYDATA* poly);

s32 fn_800A2D90(void* unused, const RwV3d* pos)
{
	if (lbl_8042C158 == NULL) {
		return 0;
	}
	RwV3d start = *pos;
	RwV3d line  = lbl_80239F28;
	RwV3d hit;

	return lbl_8042C158->DetectLineCollisionWithPolygons(&start, &line, &hit, fn_800A2E1C) != NULL;
}
}
