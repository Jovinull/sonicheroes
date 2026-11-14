// Sets the camera's view window, caches its reciprocals and marks the camera's frame hierarchy
// dirty when it has a frame (HYPOTHESIS: RwCameraSetViewWindow). Returns the camera.
// Built with GC/2.0 (configure.py): GC/1.3.2 keeps the view-window loads after the register saves,
// while the retail code schedules them into the prologue as GC/2.0 and later do. HYPOTHESIS: the
// RenderWare library was built with a GC/2.x compiler; every other reconstructed RenderWare unit
// also matches under GC/2.0.
#include "game/rw_camera.h"

// The retail code copies the view window as two plain words (integer registers); a struct copy
// of the float pair goes through floating-point registers instead.
struct RwCameraViewWords {
	u32 w[2];
};

extern "C" {
RwCameraLayout* fn_8019D0CC(RwCameraLayout* camera, const RwCameraView* viewWindow)
{
	*(RwCameraViewWords*)&camera->viewWindow = *(const RwCameraViewWords*)viewWindow;
	camera->recipViewWindow.x                = lbl_8042F6D0 / camera->viewWindow.x;
	camera->recipViewWindow.y                = lbl_8042F6D0 / camera->viewWindow.y;
	RwCameraSyncFrame(camera);
	return camera;
}
}
