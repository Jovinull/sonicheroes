// Creates an empty geometry that only occupies space (HYPOTHESIS: RpGeometryCreateSpace): creates
// a geometry without vertices or triangles (fn_80152B04, HYPOTHESIS: RpGeometryCreate), centres
// its first morph target's bounding sphere on the origin (the .sdata2 constant lbl_8042F310,
// HYPOTHESIS 0.0f) with the given radius, then unlocks it (fn_80152880, HYPOTHESIS:
// RpGeometryUnlock), destroying it and returning null when that fails. The create result is not
// checked before the unlock.
#include "types.h"

// Morph target (HYPOTHESIS: RpMorphTarget); only the bounding sphere is used here.
struct MorphTarget80152288 {
	void* parentGeometry; // 0x0
	f32 centerX;          // 0x4
	f32 centerY;          // 0x8
	f32 centerZ;          // 0xC
	f32 radius;           // 0x10
};

struct Geometry80152288 {
	u8 pad0[0x5C];
	MorphTarget80152288* morphTargets; // 0x5C
};

extern "C" {
extern f32 lbl_8042F310;

Geometry80152288* fn_80152B04(s32 numVertices, s32 numTriangles, u32 format);
Geometry80152288* fn_80152880(Geometry80152288* geometry);
s32 fn_80152EEC(Geometry80152288* geometry);

Geometry80152288* fn_80152288(f32 radius)
{
	Geometry80152288* geometry = fn_80152B04(0, 0, 0);

	if (geometry) {
		MorphTarget80152288* morphTarget = geometry->morphTargets;
		morphTarget->centerX             = lbl_8042F310;
		morphTarget->centerY             = lbl_8042F310;
		morphTarget->centerZ             = lbl_8042F310;
		morphTarget->radius              = radius;
	}
	if (!fn_80152880(geometry)) {
		fn_80152EEC(geometry);
		return 0;
	}
	return geometry;
}
}
