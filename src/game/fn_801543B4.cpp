// Destroys a light (HYPOTHESIS: RpLightDestroy): runs the light plugin destructors on the registry
// lbl_8028D278, detaches it from its frame and returns it to the light free list. Always
// returns 1.
#include "game/rw_engine.h"

extern "C" {
// Light module bookkeeping (HYPOTHESIS: lightModule) and plugin registry (lightTKList).
extern RwModuleInfo lbl_8042C8E8;
extern RwPluginRegistry lbl_8028D278;
// HYPOTHESIS: _rwObjectHasFrameReleaseFrame.
void fn_801A53E4(void* object);

s32 fn_801543B4(void* light)
{
	fn_80198E04(&lbl_8028D278, light);
	fn_801A53E4(light);
	lbl_8042C9A4->freeListFree(
	    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C8E8.globalsOffset), light);
	return 1;
}
}
