// Fills modeInfo with the description of video mode modeIndex through the device system entry
// point (HYPOTHESIS: RwEngineGetVideoModeInfo). Returns modeInfo, or null when the request fails.
#include "game/rw_engine.h"

extern "C" {
void* fn_8019D448(void* modeInfo, s32 modeIndex)
{
	if (!RwDeviceSystemRequest(RW_DEVICE_SYSTEM_GET_MODE_INFO, modeInfo, 0, modeIndex)) {
		modeInfo = 0;
	}
	return modeInfo;
}
}
