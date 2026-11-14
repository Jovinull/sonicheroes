// Reports whether the point lies inside the bounding box, bounds included
// (HYPOTHESIS: RwBBoxContainsPoint).
#include "game/rw_engine.h"

extern "C" {
s32 fn_80199FF4(const RwBBox* bbox, const RwV3d* point)
{
	if (bbox->inf.x > point->x) {
		return 0;
	}
	if (bbox->inf.y > point->y) {
		return 0;
	}
	if (bbox->inf.z > point->z) {
		return 0;
	}
	if (bbox->sup.x < point->x) {
		return 0;
	}
	if (bbox->sup.y < point->y) {
		return 0;
	}
	return !(bbox->sup.z < point->z) ? 1 : 0;
}
}
