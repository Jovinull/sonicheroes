// Applies fn_80195A74 (HYPOTHESIS: RwMatrixRotate) to the frame's modelling matrix and marks the
// hierarchy dirty (HYPOTHESIS: RwFrameRotate). Returns the frame.
#include "game/rw_frame.h"

extern "C" {
RwMatrix* fn_80195A74(RwMatrix* matrix, const RwV3d* axis, f32 angle, int combineOp);

RwFrame* fn_8019ED68(RwFrame* frame, const RwV3d* axis, f32 angle, int combineOp)
{
	fn_80195A74(&frame->modelling, axis, angle, combineOp);
	RwFrameMarkDirty(frame);
	return frame;
}
}
