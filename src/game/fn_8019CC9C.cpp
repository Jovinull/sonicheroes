// Sets the camera's near clip plane, recomputes its depth mapping and marks its frame hierarchy
// dirty (HYPOTHESIS: RwCameraSetNearClipPlane). Returns the camera.
#include "game/rw_camera.h"

extern "C" {
RwCameraLayout* fn_8019CC9C(RwCameraLayout* camera, f32 nearPlane)
{
	camera->nearPlane = nearPlane;
	RwCameraUpdateZShiftScale(camera);
	RwCameraSyncFrame(camera);
	return camera;
}
}
