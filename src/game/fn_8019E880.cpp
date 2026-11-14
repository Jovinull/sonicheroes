// Marks the frame's hierarchy dirty (HYPOTHESIS: RwFrameUpdateObjects). Returns the frame.
#include "game/rw_frame.h"

extern "C" {
RwFrame* fn_8019E880(RwFrame* frame)
{
	RwFrameMarkDirty(frame);
	return frame;
}
}
