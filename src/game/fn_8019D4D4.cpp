// Returns the index of the current video mode from the device system entry point
// (HYPOTHESIS: RwEngineGetCurrentVideoMode), or -1 when the request fails.
#include "game/rw_engine.h"

extern "C" {
s32 fn_8019D4D4(void)
{
	s32 mode;
	if (RwDeviceSystemRequest(RW_DEVICE_SYSTEM_GET_MODE, &mode, 0, 0)) {
		return mode;
	}
	return -1;
}
}
