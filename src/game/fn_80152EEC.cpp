// Drops one reference to a geometry (HYPOTHESIS: RpGeometryDestroy). The last reference releases its
// resource entry (+0x58) through fn_80197384, marks everything locked (low 12 bits of the halfword at
// +0xC), frees its triangle data (+0x54) through fn_801559E4, runs the geometry plugin destructors
// (registry lbl_8028D260), frees the morph target block (+0x5C), empties its material list (+0x20)
// through fn_80154E54 and frees the geometry with the engine memory function. Always returns 1.
#include "game/rw_engine.h"

#define RP_GEOMETRY_LOCK_ALL 0xFFF

// Geometry fields used here (HYPOTHESIS: RpGeometry layout).
struct RpGeometry80152EEC {
	u8 pad0[0xC];
	u16 lockedSinceLastInst; // 0xC
	s16 refCount;            // 0xE
	u8 pad10[0x20 - 0x10];
	RpMaterialList matList; // 0x20
	u8 pad2C[0x54 - 0x2C];
	void* triangles;    // 0x54
	void* repEntry;     // 0x58
	void* morphTargets; // 0x5C
};

extern "C" {
extern RwPluginRegistry lbl_8028D260;
void fn_80197384(void* entry);
s32 fn_801559E4(void* triangles);
RpMaterialList* fn_80154E54(RpMaterialList* list);
}

// Releases everything owned by a geometry whose last reference is being dropped.
static inline s32 GeometryRelease(RpGeometry80152EEC* geometry)
{
	if (geometry->repEntry != 0) {
		fn_80197384(geometry->repEntry);
	}
	geometry->refCount--;
	geometry->refCount++;
	geometry->lockedSinceLastInst |= RP_GEOMETRY_LOCK_ALL;
	if (geometry->triangles != 0) {
		fn_801559E4(geometry->triangles);
		geometry->triangles = 0;
	}
	fn_80198E04(&lbl_8028D260, geometry);
	if (geometry->morphTargets != 0) {
		lbl_8042C9A4->rwfree(geometry->morphTargets);
		geometry->morphTargets = 0;
	}
	fn_80154E54(&geometry->matList);
	geometry->refCount--;
	lbl_8042C9A4->rwfree(geometry);
	return 1;
}

extern "C" {
s32 fn_80152EEC(RpGeometry80152EEC* geometry)
{
	s32 result = 1;
	if (geometry->refCount - 1 <= 0) {
		result = GeometryRelease(geometry);
	} else {
		geometry->refCount--;
	}
	return result;
}
}
