// Unlinks the frame from its parent's child list, makes it the root of its own hierarchy and marks
// that hierarchy dirty (HYPOTHESIS: RwFrameRemoveChild). Returns the frame.
#include "game/rw_frame.h"

extern "C" {
RwFrame* fn_8019EA2C(RwFrame* child)
{
	RwFrame* parent = (RwFrame*)child->object.parent;
	RwFrame* cur    = parent->child;
	if (cur == child) {
		parent->child = child->next;
	} else {
		while (cur->next != child) {
			cur = cur->next;
		}
		cur->next = child->next;
	}
	child->object.parent = 0;
	child->next          = 0;
	fn_8019DFDC(child, child);
	RwFrameMarkDirty(child);
	return child;
}
}
