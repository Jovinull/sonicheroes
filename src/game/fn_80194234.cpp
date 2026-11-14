// Sets a device render state (HYPOTHESIS: RwRenderStateSet). Without a current camera it records
// error 0x10 (HYPOTHESIS: no camera bound) for plugin 1 and fails; otherwise it forwards to the
// device entry point.
#include "game/rw_engine.h"

extern "C" {
s32 fn_80194234(s32 state, void* value)
{
	if (lbl_8042C9A4->curCamera == 0) {
		RwError error;
		error.pluginID  = RW_ID_CORE_PLUGIN;
		error.errorCode = fn_8019408C(0x10);
		fn_80193FE8(&error);
		return 0;
	}
	return lbl_8042C9A4->renderStateSet(state, value);
}
}
