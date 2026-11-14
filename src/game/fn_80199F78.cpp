// Grows the bounding box to include the point (HYPOTHESIS: RwBBoxAddPoint). Returns the box.
#include "game/rw_engine.h"

extern "C" {
RwBBox* fn_80199F78(RwBBox* bbox, const RwV3d* point)
{
	RwBBoxAddPointInline(bbox, point);
	return bbox;
}
}
