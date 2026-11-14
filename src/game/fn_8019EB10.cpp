// Calls callback(child, data) for each direct child of the frame, stopping early when it returns
// null (HYPOTHESIS: RwFrameForAllChildren). The next sibling is read before the call so the
// callback may unlink the child. Returns the frame.
#include "game/rw_frame.h"

typedef RwFrame* (*RwFrameCallBack8019EB10)(RwFrame* frame, void* data);

extern "C" {
RwFrame* fn_8019EB10(RwFrame* frame, RwFrameCallBack8019EB10 callback, void* data)
{
	RwFrame* child = frame->child;
	while (child != 0) {
		RwFrame* next = child->next;
		if (callback(child, data) == 0) {
			return frame;
		}
		child = next;
	}
	return frame;
}
}
