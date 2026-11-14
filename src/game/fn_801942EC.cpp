// Renders an indexed 2D immediate-mode primitive through the device entry point of the engine
// globals (HYPOTHESIS: RwIm2DRenderIndexedPrimitive).
#include "game/rw_engine.h"

extern "C" {
s32 fn_801942EC(s32 primType, void* vertices, s32 numVertices, u16* indices, s32 numIndices)
{
	return lbl_8042C9A4->im2DRenderIndexedPrimitive(
	    primType, vertices, numVertices, indices, numIndices);
}
}
