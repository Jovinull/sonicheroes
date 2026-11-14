// Attaches an object to a frame (HYPOTHESIS: _rwObjectHasFrameSetFrame): unlinks it from its
// previous frame's object list, records the new frame as its parent and, when there is one, links
// it at the head of that frame's object list and marks the frame's hierarchy dirty.
#include "game/rw_frame.h"

extern "C" {
void fn_801A5370(RwObjectHasFrame* object, RwFrame* frame)
{
	if (object->object.parent != 0) {
		RwLLLinkRemove(&object->lFrame);
	}
	object->object.parent = frame;
	if (frame != 0) {
		RwLinkListAddLLLink(&frame->objectList, &object->lFrame);
		fn_8019E880(frame);
	}
}
}
