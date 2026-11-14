// Sets the camera's view window, caches its reciprocals and marks the camera's frame hierarchy
// dirty when it has a frame (HYPOTHESIS: RwCameraSetViewWindow). Returns the camera.
// Built with GC/2.0 (configure.py): GC/1.3.2 keeps the view-window loads after the register saves,
// while the retail code schedules them into the prologue as GC/2.0 and later do. HYPOTHESIS: the
// RenderWare library was built with a GC/2.x compiler; every other reconstructed RenderWare unit
// also matches under GC/2.0.
#include "game/rw_frame.h"

// View-window size (HYPOTHESIS: RwV2d).
struct RwV2d8019D0CC {
	f32 x;
	f32 y;
};

// The retail code copies the view window as two plain words (integer registers); a struct copy
// of the float pair goes through floating-point registers instead.
struct RwV2dWords8019D0CC {
	u32 w[2];
};

// Camera fields used here (HYPOTHESIS: RwCamera layout); the frame is the object's parent.
struct RwCamera8019D0CC {
	RwObjectHasFrame object;
	u8 pad14[0x68 - 0x14];
	RwV2d8019D0CC viewWindow;      // 0x68
	RwV2d8019D0CC recipViewWindow; // 0x70
};

extern "C" {
// .sdata2 constant 1.0f of the camera code (non-const: reloaded after each store).
extern f32 lbl_8042F6D0;

RwCamera8019D0CC* fn_8019D0CC(RwCamera8019D0CC* camera, const RwV2d8019D0CC* viewWindow)
{
	RwFrame* frame;
	*(RwV2dWords8019D0CC*)&camera->viewWindow = *(const RwV2dWords8019D0CC*)viewWindow;
	camera->recipViewWindow.x                 = lbl_8042F6D0 / camera->viewWindow.x;
	camera->recipViewWindow.y                 = lbl_8042F6D0 / camera->viewWindow.y;
	frame                                     = (RwFrame*)camera->object.object.parent;
	if (frame != 0) {
		fn_8019E880(frame);
	}
	return camera;
}
}
