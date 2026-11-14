// Sets the camera's projection type (HYPOTHESIS: RwCameraSetProjection). A perspective or parallel
// projection is stored, the camera's frame hierarchy is marked dirty and the depth mapping is
// recomputed; any other value records a core "bad parameter" error (message lbl_802904B8) and
// fails. Returns the camera, or null on error.
#include "game/rw_camera.h"

extern "C" {
extern const char lbl_802904B8[];

RwCameraLayout* fn_8019CFB8(RwCameraLayout* camera, s32 projection)
{
	switch (projection) {
		case RW_PERSPECTIVE:
		case RW_PARALLEL:
			camera->projectionType = projection;
			RwCameraSyncFrame(camera);
			RwCameraUpdateZShiftScale(camera);
			return camera;
		default: {
			RwError error;
			error.pluginID  = RW_ID_CORE_PLUGIN;
			error.errorCode = fn_8019408C(0x80000003, lbl_802904B8);
			fn_80193FE8(&error);
			return 0;
		}
	}
}
}
