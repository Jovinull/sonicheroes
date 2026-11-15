// Rebuilds the matrices and syncs the objects of a frame subtree (HYPOTHESIS: the RenderWare
// child-frame update walk used by the dirty-frame sync): for each frame of a sibling chain, ORs
// its subtree flags into the inherited ones, rebuilds its LTM from the modelling matrix and the
// parent's LTM (fn_80195674) when a matrix update is pending (0x4), calls the sync callback of
// every attached object, clears both subtree sync bits (0xC) and recurses into the children with
// the accumulated flags. The compiler inlines the recursion several levels deep.
// NonMatching: as in fn_801A2B90, retail keeps the list terminator of every inlined level in r24,
// while this source gives the second and third levels other registers (6 register-only words).
// Tried permuted and block-scoped declarations and an inline object-sync helper.
#include "game/rw_frame.h"

#define RW_FRAME_SUBTREE_SYNC_LTM 0x4

typedef RwObjectHasFrame* (*RwObjectHasFrameSync801A2980)(RwObjectHasFrame* object);

extern "C" {
// HYPOTHESIS: RwMatrixMultiply.
RwMatrix* fn_80195674(RwMatrix* dst, const RwMatrix* a, const RwMatrix* b);

void fn_801A2980(RwFrame* frame, u32 flags)
{
	RwObjectHasFrame* object;
	u32 accumulated;
	RwLLLink* cur;
	RwLLLink* end;

	while (frame != 0) {
		accumulated = flags | frame->object.privateFlags;
		if (accumulated & RW_FRAME_SUBTREE_SYNC_LTM) {
			fn_80195674(&frame->ltm, &frame->modelling, &((RwFrame*)frame->object.parent)->ltm);
		}
		end = &frame->objectList.link;
		if (frame->objectList.link.next != end) {
			for (cur = frame->objectList.link.next; cur != end; cur = cur->next) {
				object = (RwObjectHasFrame*)((u8*)cur - 8);
				((RwObjectHasFrameSync801A2980)object->sync)(object);
			}
		}
		frame->object.privateFlags &= ~RW_FRAME_SUBTREE_SYNC;
		fn_801A2980(frame->child, accumulated);
		frame = frame->next;
	}
}
}
