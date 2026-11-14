// Allocates a frame from the frame free list and initializes it (HYPOTHESIS: RwFrameCreate): an
// empty object header and object list, identity modelling and LTM matrices, no children or
// siblings, itself as root, then the frame plugin constructors. Returns null when allocation fails.
#include "game/rw_frame.h"

// HYPOTHESIS: rwMatrixInitialize followed by RwMatrixSetIdentityMacro.
static inline void RwMatrixInitIdentity(RwMatrix* m)
{
	m->flags = RW_MATRIX_TYPE_ORTHONORMAL;
	RwMatrixSetIdentity(m);
}

extern "C" {
RwFrame* fn_8019E344(void)
{
	RwFrame* frame = (RwFrame*)lbl_8042C9A4->freeListAlloc(RW_FRAME_FREE_LIST);
	if (frame == 0) {
		return 0;
	}
	frame->object.type          = 0;
	frame->object.subType       = 0;
	frame->object.flags         = 0;
	frame->object.privateFlags  = 0;
	frame->object.parent        = 0;
	frame->objectList.link.next = &frame->objectList.link;
	frame->objectList.link.prev = &frame->objectList.link;
	RwMatrixInitIdentity(&frame->modelling);
	RwMatrixInitIdentity(&frame->ltm);
	frame->child = 0;
	frame->next  = 0;
	frame->root  = frame;
	fn_80198D5C(lbl_802905F8, frame);
	return frame;
}
}
