// Destroys a camera (HYPOTHESIS: RwCameraDestroy): runs the camera plugin destructors on the
// camera registry lbl_802904A0, detaches it from its frame and returns it to the camera free list.
// Always returns 1.
#include "game/rw_engine.h"

extern "C" {
// Camera module bookkeeping (HYPOTHESIS: cameraModule) and plugin registry (cameraTKList).
extern RwModuleInfo lbl_8042C998;
extern RwPluginRegistry lbl_802904A0;
// HYPOTHESIS: _rwObjectHasFrameReleaseFrame.
void fn_801A53E4(void* object);

s32 fn_8019D178(RwCamera* camera)
{
	fn_80198E04(&lbl_802904A0, camera);
	fn_801A53E4(camera);
	lbl_8042C9A4->freeListFree(
	    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C998.globalsOffset), camera);
	return 1;
}
}
