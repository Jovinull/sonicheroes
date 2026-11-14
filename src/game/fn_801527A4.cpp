// Calls callback(material, data) for each material of the geometry's material list (+0x20),
// stopping early when it returns null (HYPOTHESIS: RpGeometryForAllMaterials). Returns the geometry.
#include "game/rw_engine.h"

struct RpGeometry801527A4 {
	u8 pad0[0x20];
	RpMaterialList matList; // 0x20
};

typedef RpMaterial* (*Callback801527A4)(RpMaterial* material, void* data);

extern "C" {
RpGeometry801527A4* fn_801527A4(RpGeometry801527A4* geometry, Callback801527A4 callback, void* data)
{
	s32 count = geometry->matList.numMaterials;
	s32 i;
	for (i = 0; i < count; i++) {
		if (callback(geometry->matList.materials[i], data) == 0) {
			return geometry;
		}
	}
	return geometry;
}
}
