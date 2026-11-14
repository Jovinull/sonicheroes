// Sets a device render state (HYPOTHESIS: RwRenderStateSet). Without a current camera it records
// error 0x10 (HYPOTHESIS: no camera bound) for plugin 1 and fails; otherwise it forwards to the
// device entry point.
#include "game/rw_engine.h"

// Error record (HYPOTHESIS: RwError).
struct RwError80194234 {
	s32 pluginID;
	s32 errorCode;
};

extern "C" {
// HYPOTHESIS: _rwerror (variadic) and RwErrorSet.
s32 fn_8019408C(s32 code, ...);
RwError80194234* fn_80193FE8(RwError80194234* error);

s32 fn_80194234(s32 state, void* value)
{
	if (lbl_8042C9A4->curCamera == 0) {
		RwError80194234 error;
		error.pluginID  = 1;
		error.errorCode = fn_8019408C(0x10);
		fn_80193FE8(&error);
		return 0;
	}
	return lbl_8042C9A4->renderStateSet(state, value);
}
}
