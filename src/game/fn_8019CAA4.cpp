// Makes the camera current, runs fn_801A2EF4 on it, starts rendering through the driver standard
// function and then runs fn_801B3364 on it (HYPOTHESIS: RwCameraBeginUpdate). Returns the camera,
// or null when the driver fails.
#include "game/rw_engine.h"

extern "C" {
void fn_801A2EF4(RwCamera* camera);
void fn_801B3364(RwCamera* camera);

RwCamera* fn_8019CAA4(RwCamera* camera)
{
	lbl_8042C9A4->curCamera = camera;
	fn_801A2EF4(camera);
	if (lbl_8042C9A4->stdFunc[rwSTANDARDCAMERABEGINUPDATE](0, camera, 0)) {
		fn_801B3364(camera);
		return camera;
	}
	return 0;
}
}
