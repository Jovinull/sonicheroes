// Applies fn_80196050 (HYPOTHESIS: RwMatrixScale) to the frame's modelling matrix, then marks the
// frame hierarchy dirty the way RenderWare's RwFrameUpdateObjects does: the root frame joins the
// engine's dirty-frame list (lbl_8042C9A4 + 0xBC) the first time it is flagged. Returns the frame.
#include "game/object.h"

struct RwGlobals8019EB94 {
	u8 pad0[0xBC];
	RwLinkList dirtyFrameList;
};

extern "C" {
extern RwGlobals8019EB94* lbl_8042C9A4;
RwMatrix* fn_80196050(RwMatrix* matrix, const RwV3d* scale, int combineOp);

RwFrame* fn_8019EB94(RwFrame* frame, const RwV3d* scale, int combineOp)
{
	u8 oldState;
	fn_80196050(&frame->modelling, scale, combineOp);
	oldState = frame->root->object.privateFlags;
	if (!(oldState & 3)) {
		frame->root->inDirtyListLink.next            = lbl_8042C9A4->dirtyFrameList.link.next;
		frame->root->inDirtyListLink.prev            = &lbl_8042C9A4->dirtyFrameList.link;
		lbl_8042C9A4->dirtyFrameList.link.next->prev = &frame->root->inDirtyListLink;
		lbl_8042C9A4->dirtyFrameList.link.next       = &frame->root->inDirtyListLink;
	}
	frame->root->object.privateFlags = oldState | 3;
	frame->object.privateFlags |= 0xC;
	return frame;
}
}
