// Computes the bounding box of numVertices points (HYPOTHESIS: RwBBoxCalculate): both corners start
// at the first point and every further point grows the box. Returns the box.
// Built with GC/2.0 (configure.py): GC/1.3.2 lays the copy and loop out differently (3 more
// instructions). HYPOTHESIS: RenderWare was built with GC/2.x (see fn_8019D0CC).
#include "game/rw_engine.h"

// The retail code copies the first point as three plain words (integer registers).
struct RwV3dWords80199E98 {
	u32 w[3];
};

extern "C" {
RwBBox* fn_80199E98(RwBBox* bbox, const RwV3d* vertices, s32 numVertices)
{
	*(RwV3dWords80199E98*)&bbox->inf = *(const RwV3dWords80199E98*)vertices;
	*(RwV3dWords80199E98*)&bbox->sup = *(const RwV3dWords80199E98*)vertices;
	vertices++;
	numVertices--;
	while (numVertices--) {
		RwBBoxAddPointInline(bbox, vertices);
		vertices++;
	}
	return bbox;
}
}
