// Drops one reference to a material (HYPOTHESIS: RpMaterialDestroy). The last reference runs the
// material plugin destructors (registry lbl_8028D290), releases its texture through fn_8015498C
// (HYPOTHESIS: RpMaterialSetTexture with null) and returns it to the material free list. Always
// returns 1.
#include "game/rw_engine.h"

// Material fields used here (HYPOTHESIS: RpMaterial layout).
struct RpMaterial80154910 {
	u8 pad0[0x18];
	s16 refCount; // 0x18
};

extern "C" {
extern RwModuleInfo lbl_8042C8F8;
extern RwPluginRegistry lbl_8028D290;
RpMaterial80154910* fn_8015498C(RpMaterial80154910* material, void* texture);

s32 fn_80154910(RpMaterial80154910* material)
{
	if (material->refCount == 1) {
		fn_80198E04(&lbl_8028D290, material);
		fn_8015498C(material, 0);
		lbl_8042C9A4->freeListFree(
		    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C8F8.globalsOffset), material);
	} else {
		material->refCount--;
	}
	return 1;
}
}
