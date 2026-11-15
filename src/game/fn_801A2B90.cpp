// Syncs the objects of a frame subtree without rebuilding matrices (HYPOTHESIS: the object-only
// child walk used by fn_801A2DA8): for each frame of a sibling chain, calls the sync callback of
// every attached object, clears the subtree object-sync bit (0x8) and recurses into the children.
// The compiler inlines the recursion several levels deep.
// NonMatching: same instruction stream, but retail keeps every inlined level's list terminator in
// r27 and the outer frame in r28, while this source spreads them over r24-r29 (32 register-only
// words). Tried for/while forms, named or expression terminators, an object local, permuted
// declarations and compilers GC/1.3 to 2.7.
#include "game/rw_frame.h"

#define RW_FRAME_SUBTREE_SYNC_OBJ 0x8

typedef RwObjectHasFrame* (*RwObjectHasFrameSync801A2B90)(RwObjectHasFrame* object);

extern "C" {
void fn_801A2B90(RwFrame* frame)
{
	RwLLLink* cur;
	RwLLLink* end;
	RwObjectHasFrame* object;

	while (frame != 0) {
		end = &frame->objectList.link;
		if (frame->objectList.link.next != end) {
			for (cur = frame->objectList.link.next; cur != end; cur = cur->next) {
				object = (RwObjectHasFrame*)((u8*)cur - 8);
				((RwObjectHasFrameSync801A2B90)object->sync)(object);
			}
		}
		frame->object.privateFlags &= ~RW_FRAME_SUBTREE_SYNC_OBJ;
		fn_801A2B90(frame->child);
		frame = frame->next;
	}
}
}
