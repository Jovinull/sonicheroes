// Creates a light of the given type (HYPOTHESIS: RpLightCreate): takes one from the light free list,
// initializes its object header (type 3) and frame sync callback fn_80153E9C, radius lbl_8042F320,
// cone and colour components lbl_8042F34C, an empty sector list, a light frame one behind the
// engine's, the "no chroma" private flag and the light-atomics/light-world flags, then runs the light
// plugin constructors. Returns the light, or null when allocation fails.
#include "game/rw_engine.h"

#define RP_LIGHT_TYPE                    3
#define RP_LIGHT_PRIVATE_NO_CHROMA       1
#define RP_LIGHT_LIGHT_ATOMICS_AND_WORLD 3

// Light fields used here (HYPOTHESIS: RpLight layout).
struct RpLight80154414 {
	RwObjectHasFrame object;   // 0x0
	f32 radius;                // 0x14
	RwRGBAReal color;          // 0x18
	f32 minusCosAngle;         // 0x28
	RwLinkList sectorsInLight; // 0x2C
	void* f34;                 // 0x34
	void* f38;                 // 0x38
	u16 lightFrame;            // 0x3C
};

extern "C" {
// Light module bookkeeping (HYPOTHESIS: lightModule) and plugin registry (lightTKList).
extern RwModuleInfo lbl_8042C8E8;
extern RwPluginRegistry lbl_8028D278;
// .sdata2 constants (non-const: see RW_MATRIX_SET_IDENTITY).
extern f32 lbl_8042F320;
extern f32 lbl_8042F34C;
// HYPOTHESIS: the light's frame sync callback.
void* fn_80153E9C(void* object);

RpLight80154414* fn_80154414(s32 type)
{
	RpLight80154414* light = (RpLight80154414*)lbl_8042C9A4->freeListAlloc(
	    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C8E8.globalsOffset));
	if (light == 0) {
		return 0;
	}
	light->object.object.type         = RP_LIGHT_TYPE;
	light->object.object.subType      = type;
	light->object.object.flags        = 0;
	light->object.object.privateFlags = 0;
	light->object.object.parent       = 0;
	light->object.sync                = (void*)fn_80153E9C;
	light->radius                     = lbl_8042F320;
	light->minusCosAngle              = lbl_8042F34C;
	light->color.red                  = lbl_8042F34C;
	light->color.green                = lbl_8042F34C;
	light->color.blue                 = lbl_8042F34C;
	light->color.alpha                = lbl_8042F34C;
	light->object.object.privateFlags = RP_LIGHT_PRIVATE_NO_CHROMA;
	light->sectorsInLight.link.next   = &light->sectorsInLight.link;
	light->sectorsInLight.link.prev   = &light->sectorsInLight.link;
	light->f38                        = 0;
	light->f34                        = 0;
	light->lightFrame                 = lbl_8042C9A4->lightFrame - 1;
	light->object.object.flags        = RP_LIGHT_LIGHT_ATOMICS_AND_WORLD;
	fn_80198D5C(&lbl_8028D278, light);
	return light;
}
}
