#ifndef GAME_RW_CAMERA_H
#define GAME_RW_CAMERA_H

#include "game/rw_frame.h"

// RenderWare camera fields used by the reconstructed camera units (HYPOTHESIS: RwCamera layout).
// The camera's frame is its object's parent.

#define RW_PERSPECTIVE 1
#define RW_PARALLEL    2

struct RwCameraView {
	f32 x;
	f32 y;
};

struct RwCameraLayout {
	RwObjectHasFrame object;
	s32 projectionType; // 0x14
	u8 pad18[0x68 - 0x18];
	RwCameraView viewWindow;      // 0x68
	RwCameraView recipViewWindow; // 0x70
	u8 pad78[0x80 - 0x78];
	f32 nearPlane; // 0x80
	f32 farPlane;  // 0x84
	f32 fogPlane;  // 0x88
	f32 zScale;    // 0x8C
	f32 zShift;    // 0x90
};

extern "C" {
// .sdata2 constants of the camera code (non-const: see RW_MATRIX_SET_IDENTITY).
extern f32 lbl_8042F6D0; // 1.0f
extern f32 lbl_8042F6D4; // half-unit inset factor
extern f32 lbl_8042F6D8; // 0.5f
// HYPOTHESIS: RwIm2DGetNearScreenZ / RwIm2DGetFarScreenZ (device zBufferNear/zBufferFar).
f32 fn_8019421C(void);
f32 fn_80194228(void);
}

// Maps the clip range (reciprocal for perspective cameras, linear for parallel ones) onto the
// device screen-Z range inset by half a unit at each end (HYPOTHESIS: CameraUpdateZShiftScale).
static inline void RwCameraUpdateZShiftScale(RwCameraLayout* camera)
{
	f32 nearScreenZ;
	f32 farScreenZ;
	f32 zNear;
	f32 zFar;
	f32 inset;
	f32 zScale;

	nearScreenZ = fn_8019421C();
	farScreenZ  = fn_80194228();
	switch (camera->projectionType) {
		case RW_PARALLEL:
			zFar  = camera->farPlane;
			zNear = camera->nearPlane;
			break;
		case RW_PERSPECTIVE:
		default:
			zFar  = lbl_8042F6D0 / camera->farPlane;
			zNear = lbl_8042F6D0 / camera->nearPlane;
			break;
	}
	inset          = lbl_8042F6D4 * (farScreenZ - nearScreenZ);
	farScreenZ     = farScreenZ - inset;
	nearScreenZ    = nearScreenZ + inset;
	zScale         = (farScreenZ - nearScreenZ) / (zFar - zNear);
	camera->zScale = zScale;
	camera->zShift = lbl_8042F6D8 * ((farScreenZ + nearScreenZ) - zScale * (zFar + zNear));
}

// Marks the hierarchy of the camera's frame dirty when the camera has a frame.
static inline void RwCameraSyncFrame(RwCameraLayout* camera)
{
	RwFrame* frame = (RwFrame*)camera->object.object.parent;
	if (frame != 0) {
		fn_8019E880(frame);
	}
}

#endif
