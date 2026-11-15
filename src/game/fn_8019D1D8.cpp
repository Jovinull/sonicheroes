// Creates a camera (HYPOTHESIS: RwCameraCreate): takes one from the camera free list, initialises
// it as an unparented camera object with its sync and begin/end update callbacks, a unit view
// window, no view offset, the default clip and fog planes, no frame or Z buffer and a perspective
// projection, derives its Z shift and scale, clears the view matrix flags and runs the camera
// plugin constructors. Returns the camera, or null.
#include "game/rw_camera.h"

#define RW_CAMERA_OBJECT_TYPE 4

extern "C" {
// Camera module bookkeeping (HYPOTHESIS: cameraModule): the camera free list is the first field of
// its globals.
extern RwModuleInfo lbl_8042C998;
// Camera plugin registry (HYPOTHESIS: cameraTKList).
extern RwPluginRegistry lbl_802904A0;
extern f32 lbl_8042F6E4; // 0.0f
extern f32 lbl_8042F6E8; // default near clip plane
extern f32 lbl_8042F6EC; // default far clip plane
extern f32 lbl_8042F6F0; // default fog distance
// HYPOTHESIS: the camera sync, begin-update and end-update callbacks.
void* fn_8019C9DC(void* object);
RwCameraLayout* fn_8019CAA4(RwCameraLayout* camera);
RwCameraLayout* fn_8019CA40(RwCameraLayout* camera);

RwCameraLayout* fn_8019D1D8(void)
{
	RwCameraLayout* camera = (RwCameraLayout*)lbl_8042C9A4->freeListAlloc(
	    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C998.globalsOffset));
	if (camera == 0) {
		return 0;
	}
	camera->object.object.type         = RW_CAMERA_OBJECT_TYPE;
	camera->object.object.subType      = 0;
	camera->object.object.flags        = 0;
	camera->object.object.privateFlags = 0;
	camera->object.object.parent       = 0;
	camera->object.sync                = (void*)fn_8019C9DC;
	camera->beginUpdate                = fn_8019CAA4;
	camera->endUpdate                  = fn_8019CA40;

	camera->viewWindow.x = camera->viewWindow.y = lbl_8042F6D0;
	camera->recipViewWindow.x = camera->recipViewWindow.y = lbl_8042F6D0;
	camera->viewOffset.x = camera->viewOffset.y = lbl_8042F6E4;
	camera->nearPlane                           = lbl_8042F6E8;
	camera->farPlane                            = lbl_8042F6EC;
	camera->fogPlane                            = lbl_8042F6F0;
	camera->frameBuffer                         = 0;
	camera->zBuffer                             = 0;
	camera->projectionType                      = RW_PERSPECTIVE;
	RwCameraUpdateZShiftScale(camera);
	camera->viewMatrix.flags = 0;
	fn_80198D5C(&lbl_802904A0, camera);
	return camera;
}
}
