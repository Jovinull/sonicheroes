// Sets root as the hierarchy root of the frame and, recursively, of all its descendants
// (HYPOTHESIS: _rwSetHierarchyRoot). The compiler inlines the recursion eight levels deep.
#include "game/rw_frame.h"

extern "C" {
void fn_8019DFDC(RwFrame* frame, RwFrame* root)
{
	frame->root = root;
	frame       = frame->child;
	while (frame != 0) {
		fn_8019DFDC(frame, root);
		frame = frame->next;
	}
}
}
