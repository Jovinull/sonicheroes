// Releases one frame: runs the frame plugin destructors through fn_80198E04 on the frame registry
// lbl_802905F8, drops the frame from the dirty-frame list when it is a dirty root and returns it to
// the frame free list (HYPOTHESIS: the per-frame step of RwFrameDestroy).
#include "game/rw_frame.h"

extern "C" {
extern u8 lbl_802905F8[];
// HYPOTHESIS: _rwPluginRegistryDeInitObject.
void fn_80198E04(void* registry, void* object);

void fn_8019E588(RwFrame* frame)
{
	fn_80198E04(lbl_802905F8, frame);
	if (frame->object.privateFlags & RW_FRAME_HIERARCHY_SYNC) {
		RwLLLinkRemove(&frame->inDirtyListLink);
	}
	lbl_8042C9A4->freeListFree(RW_FRAME_FREE_LIST, frame);
}
}
