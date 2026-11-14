// Creates a material (HYPOTHESIS: RpMaterialCreate): takes one from the material free list with one
// reference, opaque white colour, no texture or pipeline and the default surface properties
// lbl_8028D2A8, then runs the material plugin constructors. Returns the material, or null when
// allocation fails.
#include "game/rw_engine.h"

// The retail code copies the colour and surface properties as plain words.
struct RwRGBAWord80154860 {
	u32 w;
};
struct RwSurfaceWords80154860 {
	u32 w[3];
};

// Material fields used here (HYPOTHESIS: RpMaterial layout).
struct RpMaterial80154860 {
	void* texture;                       // 0x0
	RwRGBA color;                        // 0x4
	void* pipeline;                      // 0x8
	RwSurfaceWords80154860 surfaceProps; // 0xC
	s16 refCount;                        // 0x18
};

extern "C" {
// Material module bookkeeping (HYPOTHESIS: materialModule), plugin registry (materialTKList) and
// default surface properties.
extern RwModuleInfo lbl_8042C8F8;
extern RwPluginRegistry lbl_8028D290;
extern RwSurfaceWords80154860 lbl_8028D2A8;

RpMaterial80154860* fn_80154860(void)
{
	RwRGBA white;
	RpMaterial80154860* material = (RpMaterial80154860*)lbl_8042C9A4->freeListAlloc(
	    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C8F8.globalsOffset));
	if (material == 0) {
		return 0;
	}
	material->refCount                     = 1;
	white.red                              = 0xFF;
	white.green                            = 0xFF;
	white.blue                             = 0xFF;
	white.alpha                            = 0xFF;
	*(RwRGBAWord80154860*)&material->color = *(RwRGBAWord80154860*)&white;
	material->texture                      = 0;
	material->pipeline                     = 0;
	material->surfaceProps                 = lbl_8028D2A8;
	fn_80198D5C(&lbl_8028D290, material);
	return material;
}
}
