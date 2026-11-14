// Clears the camera's buffers through the driver standard function
// (HYPOTHESIS: RwCameraClear). Returns the camera, or null when the driver fails.
#include "game/rw_engine.h"

extern "C" {
RwCamera* fn_8019CF28(RwCamera* camera, RwRGBA* color, s32 clearMode)
{
	if (lbl_8042C9A4->stdFunc[rwSTANDARDCAMERACLEAR](camera, color, clearMode)) {
		return camera;
	}
	return 0;
}
}
