// Frame destruction (HYPOTHESIS: the RenderWare frame destroy helpers). The three functions
// share this unit because fn_8019E600 inlines the other two at its outer recursion levels.
#include "game/rw_frame.h"

extern "C" {
// Runs the frame plugin destructors through fn_80198E04 on the frame registry lbl_802905F8 and
// drops the frame from the dirty-frame list when it is a dirty root (HYPOTHESIS: the per-frame
// deinit step of RwFrameDestroy).
void fn_8019E52C(RwFrame* frame)
{
	fn_80198E04(&lbl_802905F8, frame);
	if (frame->object.privateFlags & RW_FRAME_HIERARCHY_SYNC) {
		RW_LL_LINK_REMOVE(&frame->inDirtyListLink);
	}
}

// Deinitialises one frame (fn_8019E52C) and returns it to the frame free list (HYPOTHESIS: the
// per-frame step of RwFrameDestroy).
void fn_8019E588(RwFrame* frame)
{
	fn_8019E52C(frame);
	lbl_8042C9A4->freeListFree(RW_FRAME_FREE_LIST, frame);
}

// Destroys a frame and its whole subtree, children first (HYPOTHESIS: _rwFrameDestroyRecurse).
// The compiler inlines the recursion and the two helpers several levels deep.
void fn_8019E600(RwFrame* frame)
{
	if (frame != 0) {
		RwFrame* child = frame->child;
		while (child != 0) {
			RwFrame* next = child->next;
			fn_8019E600(child);
			child = next;
		}
		fn_8019E588(frame);
	}
}
}
