// Queries a device render state through the device entry point (HYPOTHESIS: RwRenderStateGet).
#include "game/rw_engine.h"

extern "C" {
s32 fn_80194294(s32 state, void* value)
{
	return lbl_8042C9A4->renderStateGet(state, value);
}
}
