// Allocates a frame from the frame free list and initializes it (HYPOTHESIS: RwFrameCreate): an
// empty object header and object list, identity modelling and LTM matrices, no children or
// siblings, itself as root, then the frame plugin constructors. Returns null when allocation fails.
#include "game/rw_frame.h"

#define RW_MATRIX_TYPE_ORTHONORMAL  0x3
#define RW_MATRIX_INTERNAL_IDENTITY 0x20000

extern "C" {
extern u8 lbl_802905F8[];
// .sdata2 constants 1.0f and 0.0f. Declared non-const: the retail code reloads them after the
// matrix stores, treating them as ordinary memory rather than folded constants.
extern f32 lbl_8042F6F8;
extern f32 lbl_8042F6FC;
// HYPOTHESIS: _rwPluginRegistryInitObject.
void fn_80198D5C(void* registry, void* object);
}

// HYPOTHESIS: rwMatrixInitialize followed by RwMatrixSetIdentityMacro.
static inline void RwMatrixInitIdentity(RwMatrix* m)
{
	m->flags   = RW_MATRIX_TYPE_ORTHONORMAL;
	m->right.x = m->up.y = m->at.z = lbl_8042F6F8;
	m->right.y = m->right.z = m->up.x = lbl_8042F6FC;
	m->up.z = m->at.x = m->at.y = lbl_8042F6FC;
	m->pos.x = m->pos.y = m->pos.z = lbl_8042F6FC;
	m->flags |= RW_MATRIX_INTERNAL_IDENTITY | RW_MATRIX_TYPE_ORTHONORMAL;
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
