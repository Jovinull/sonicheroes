// Destroys a single frame (HYPOTHESIS: RwFrameDestroy): runs the frame plugin destructors, detaches
// it from its parent, drops it from the dirty-frame list when it is a dirty root, orphans its
// children and returns it to the frame free list. Always returns 1.
#include "game/rw_frame.h"

extern "C" {
s32 fn_8019E480(RwFrame* frame)
{
	RwFrame* child;
	fn_80198E04(lbl_802905F8, frame);
	if (frame->object.parent != 0) {
		fn_8019EA2C(frame);
	}
	if (frame->object.privateFlags & RW_FRAME_HIERARCHY_SYNC) {
		RwLLLinkRemove(&frame->inDirtyListLink);
	}
	for (child = frame->child; child != 0; child = child->next) {
		child->object.parent = 0;
	}
	lbl_8042C9A4->freeListFree(RW_FRAME_FREE_LIST, frame);
	return 1;
}
}
