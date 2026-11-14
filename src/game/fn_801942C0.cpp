// Renders a 2D immediate-mode primitive through the device entry point of the engine globals
// (HYPOTHESIS: RwIm2DRenderPrimitive).
#include "game/rw_engine.h"

extern "C" {
s32 fn_801942C0(s32 primType, void* vertices, s32 numVertices)
{
	return lbl_8042C9A4->im2DRenderPrimitive(primType, vertices, numVertices);
}
}
