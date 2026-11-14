// Ends rendering to the camera through the driver standard function and clears the current camera
// (HYPOTHESIS: RwCameraEndUpdate). Returns the camera, or null when the driver fails.
#include "game/rw_engine.h"

extern "C" {
RwCamera* fn_8019CA40(RwCamera* camera)
{
	if (lbl_8042C9A4->stdFunc[rwSTANDARDCAMERAENDUPDATE](0, camera, 0)) {
		lbl_8042C9A4->curCamera = 0;
		return camera;
	}
	return 0;
}
}
