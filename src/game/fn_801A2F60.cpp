// Rebuilds the matrices of a frame subtree without syncing objects (HYPOTHESIS: the matrix-only
// RenderWare child-frame update walk): for each frame of a sibling chain, ORs its subtree flags
// into the inherited ones and, when a matrix update is pending (0x4), rebuilds its LTM from the
// modelling matrix and the parent's LTM (fn_80195674) and clears its own matrix bit, then recurses
// into the children with the accumulated flags. The compiler inlines the recursion several
// levels deep; the parent local matters, as the inline depth follows the size of the body.
#include "game/rw_frame.h"

#define RW_FRAME_SUBTREE_SYNC_LTM 0x4

extern "C" {
// HYPOTHESIS: RwMatrixMultiply.
RwMatrix* fn_80195674(RwMatrix* dst, const RwMatrix* a, const RwMatrix* b);

void fn_801A2F60(RwFrame* frame, u32 flags)
{
	u32 accumulated;

	while (frame != 0) {
		accumulated = flags | frame->object.privateFlags;
		if (accumulated & RW_FRAME_SUBTREE_SYNC_LTM) {
			RwFrame* parent = (RwFrame*)frame->object.parent;
			fn_80195674(&frame->ltm, &frame->modelling, &parent->ltm);
			frame->object.privateFlags &= ~RW_FRAME_SUBTREE_SYNC_LTM;
		}
		fn_801A2F60(frame->child, accumulated);
		frame = frame->next;
	}
}
}
