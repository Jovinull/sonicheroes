// Sets the camera's far clip plane, recomputes its depth mapping and marks its frame hierarchy
// dirty (HYPOTHESIS: RwCameraSetFarClipPlane). Returns the camera.
#include "game/rw_camera.h"

extern "C" {
RwCameraLayout* fn_8019CD68(RwCameraLayout* camera, f32 farPlane)
{
	camera->farPlane = farPlane;
	RwCameraUpdateZShiftScale(camera);
	RwCameraSyncFrame(camera);
	return camera;
}
}
