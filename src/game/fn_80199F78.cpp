// Grows the bounding box to include the point (HYPOTHESIS: RwBBoxAddPoint). Returns the box.
#include "game/rw_engine.h"

extern "C" {
RwBBox* fn_80199F78(RwBBox* bbox, const RwV3d* point)
{
	if (bbox->inf.x > point->x) {
		bbox->inf.x = point->x;
	}
	if (bbox->inf.y > point->y) {
		bbox->inf.y = point->y;
	}
	if (bbox->inf.z > point->z) {
		bbox->inf.z = point->z;
	}
	if (bbox->sup.x < point->x) {
		bbox->sup.x = point->x;
	}
	if (bbox->sup.y < point->y) {
		bbox->sup.y = point->y;
	}
	if (bbox->sup.z < point->z) {
		bbox->sup.z = point->z;
	}
	return bbox;
}
}
