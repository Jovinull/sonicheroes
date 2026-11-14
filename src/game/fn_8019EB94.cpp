// Applies fn_80196050 (HYPOTHESIS: RwMatrixScale) to the frame's modelling matrix and marks the
// hierarchy dirty (HYPOTHESIS: RwFrameScale). Returns the frame.
#include "game/rw_frame.h"

extern "C" {
RwMatrix* fn_80196050(RwMatrix* matrix, const RwV3d* scale, int combineOp);

RwFrame* fn_8019EB94(RwFrame* frame, const RwV3d* scale, int combineOp)
{
	fn_80196050(&frame->modelling, scale, combineOp);
	RwFrameMarkDirty(frame);
	return frame;
}
}
