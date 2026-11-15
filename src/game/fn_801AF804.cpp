// Turns the GX fog of the RenderWare GameCube driver on or off (HYPOTHESIS: the driver's fog render
// state): when switched on, takes the fog start and the near/far planes (and the end, unless one
// was set explicitly) from the current camera, then sets the fog of the stored type (mapped through
// lbl_80290F60) and colour; when switched off, sets fog type 0 with the .sdata2 defaults. Only
// acts on a change of state. Always returns 1. Field names are inferred from this function only.
// NonMatching: when switching off, the retail code copies the colour argument before loading the
// float constants; ours loads the first constant first (5 words differ).
#include "dolphin/gx/GXPixel.h"
#include "game/rw_camera.h"

// Driver render state block (fields used here only).
struct RenderState801AF804 {
	u8 pad0[0x10];
	s32 fogEnabled; // 0x10
	s32 fogType;    // 0x14
	u8 pad18[0x4];
	GXColor fogColor; // 0x1C
	s32 fogEndSet;    // 0x20
	f32 fogStart;     // 0x24
	f32 fogEnd;       // 0x28
	f32 fogNear;      // 0x2C
	f32 fogFar;       // 0x30
};

extern "C" {
extern RenderState801AF804 lbl_803EDBD0;
extern GXFogType lbl_80290F60[4];
extern f32 lbl_8042F7BC;
extern f32 lbl_8042F7C0;
extern f32 lbl_8042F7C4;

s32 fn_801AF804(s32 enable)
{
	if (enable) {
		if (!lbl_803EDBD0.fogEnabled) {
			RwCameraLayout* camera = (RwCameraLayout*)lbl_8042C9A4->curCamera;
			if (camera) {
				if (!lbl_803EDBD0.fogEndSet) {
					lbl_803EDBD0.fogEnd = camera->farPlane;
				}
				lbl_803EDBD0.fogStart = camera->fogPlane;
				lbl_803EDBD0.fogNear  = camera->nearPlane;
				lbl_803EDBD0.fogFar   = camera->farPlane;
			}
			GXSetFog(lbl_80290F60[lbl_803EDBD0.fogType], lbl_803EDBD0.fogStart, lbl_803EDBD0.fogEnd,
			    lbl_803EDBD0.fogNear, lbl_803EDBD0.fogFar, lbl_803EDBD0.fogColor);
			lbl_803EDBD0.fogEnabled = 1;
		}
	} else if (lbl_803EDBD0.fogEnabled) {
		GXSetFog(GX_FOG_NONE, lbl_8042F7BC, lbl_8042F7C0, lbl_8042F7C4, lbl_8042F7C0,
		    lbl_803EDBD0.fogColor);
		lbl_803EDBD0.fogEnabled = 0;
	}
	return 1;
}
}
