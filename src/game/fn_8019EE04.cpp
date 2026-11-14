// Resets the frame's modelling matrix to the identity and marks the hierarchy dirty
// (HYPOTHESIS: RwFrameSetIdentity). Returns the frame.
#include "game/rw_frame.h"

extern "C" {
RwFrame* fn_8019EE04(RwFrame* frame)
{
	RwMatrixSetIdentity(&frame->modelling);
	RwFrameMarkDirty(frame);
	return frame;
}
}
