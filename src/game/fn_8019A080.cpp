// Reads a camera from a stream (HYPOTHESIS: RwCameraStreamRead): finds the struct chunk, accepts
// library versions 0x31000 to 0x35000 (otherwise raises error 0x80000004 of plugin 1), reads the
// 0x20-byte camera record (zero-filled first, converted to native byte order), creates the camera,
// reads the camera plugin data and applies the view window, view offset, clip planes, fog
// distance and projection. Returns the camera, or null on failure.
#include "game/rw_camera.h"
#include "MSL_C/string.h"

// Camera record as stored in the stream (HYPOTHESIS: _rwCameraBinary).
struct RwCameraBinary8019A080 {
	RwCameraView viewWindow; // 0x0
	RwCameraView viewOffset; // 0x8
	f32 nearPlane;           // 0x10
	f32 farPlane;            // 0x14
	f32 fogPlane;            // 0x18
	s32 projection;          // 0x1C
};

#define RW_ID_STRUCT             1
#define RW_ERROR_BAD_VERSION     ((s32)0x80000004)
#define RW_STREAM_VERSION_OLDEST 0x31000
#define RW_STREAM_VERSION_NEWEST 0x35000

extern "C" {
// Camera plugin registry (HYPOTHESIS: cameraTKList).
extern RwPluginRegistry lbl_802904A0;
// HYPOTHESIS: RwStreamFindChunk, RwStreamRead, RwMemNative32, RwCameraCreate,
// _rwPluginRegistryReadDataChunks, RwCameraSetViewWindow, RwCameraSetViewOffset,
// RwCameraSetNearClipPlane, RwCameraSetFarClipPlane and RwCameraSetProjection.
s32 fn_80192F38(void* stream, u32 type, u32* length, u32* version);
u32 fn_801979AC(void* stream, void* buffer, u32 length);
void* fn_80193270(void* mem, u32 size);
RwCameraLayout* fn_8019D1D8(void);
const RwPluginRegistry* fn_8019836C(const RwPluginRegistry* registry, void* stream, void* object);
RwCameraLayout* fn_8019D0CC(RwCameraLayout* camera, const RwCameraView* viewWindow);
RwCameraLayout* fn_8019CC50(RwCameraLayout* camera, const RwCameraView* viewOffset);
RwCameraLayout* fn_8019CC9C(RwCameraLayout* camera, f32 nearPlane);
RwCameraLayout* fn_8019CD68(RwCameraLayout* camera, f32 farPlane);
RwCameraLayout* fn_8019CFB8(RwCameraLayout* camera, s32 projection);

RwCameraLayout* fn_8019A080(void* stream)
{
	u32 size;
	u32 version;
	RwCameraBinary8019A080 binary;
	RwCameraLayout* camera;

	if (!fn_80192F38(stream, RW_ID_STRUCT, &size, &version)) {
		return 0;
	}
	if (version >= RW_STREAM_VERSION_OLDEST && version <= RW_STREAM_VERSION_NEWEST) {
		memset(&binary, 0, sizeof(binary));
		if (size != fn_801979AC(stream, &binary, size)) {
			return 0;
		}
		fn_80193270(&binary, sizeof(binary));

		camera = fn_8019D1D8();
		if (camera == 0) {
			return 0;
		}
		if (fn_8019836C(&lbl_802904A0, stream, camera) == 0) {
			return 0;
		}
		fn_8019D0CC(camera, &binary.viewWindow);
		fn_8019CC50(camera, &binary.viewOffset);
		fn_8019CC9C(camera, binary.nearPlane);
		fn_8019CD68(camera, binary.farPlane);
		camera->fogPlane = binary.fogPlane;
		fn_8019CFB8(camera, binary.projection);
		return camera;
	} else {
		RwError error;
		error.pluginID  = 1;
		error.errorCode = fn_8019408C(RW_ERROR_BAD_VERSION);
		fn_80193FE8(&error);
		return 0;
	}
}
}
