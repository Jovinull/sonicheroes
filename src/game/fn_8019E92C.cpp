// Detaches child from any previous parent, links it at the head of parent's child list, moves it
// into parent's hierarchy (dropping it from the dirty-frame list if it was a dirty root) and marks
// the new hierarchy dirty (HYPOTHESIS: RwFrameAddChild). Returns parent.
#include "game/rw_frame.h"

extern "C" {
RwFrame* fn_8019E92C(RwFrame* parent, RwFrame* child)
{
	if (child->object.parent != 0) {
		fn_8019EA2C(child);
	}
	child->next          = parent->child;
	parent->child        = child;
	child->object.parent = parent;
	fn_8019DFDC(child, parent->root);
	if (child->object.privateFlags & RW_FRAME_HIERARCHY_SYNC) {
		RwLLLinkRemove(&child->inDirtyListLink);
		child->object.privateFlags &= ~RW_FRAME_HIERARCHY_SYNC;
	}
	RwFrameMarkDirty(child);
	return parent;
}
}
