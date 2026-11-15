// Renders a menu's 3D scene in two camera passes (HYPOTHESIS; names inferred): sets the far
// distance (through the game context lbl_8042C1F8 when there is one, otherwise lbl_8042EE68),
// clears the camera with the colour lbl_8042AEB0, adds the camera and the two lights of
// lbl_8042C784 to the scene world lbl_8042C780, then renders the scene object (0xC) from the
// camera placed at lbl_8028AEA8 (fn_80018064) and again from lbl_8028AEB4 (fn_80017AEC), each pass
// inside a camera update and the context's begin/end hooks; finally removes the camera and lights,
// flushes (fn_80177C50) and shows the raster.
#include "game/matrix.h"

struct RwCamera;

struct Camera801302B0 {
	u8 pad0[0x4];
	void* frame; // 0x4
};

struct Scene801302B0 {
	u8 pad0[0xC];
	void* object; // 0xC
};

RwCamera* GetCurrentCameraPointer();

extern "C" {
extern void* lbl_8042C1F8;
extern void* lbl_8042C780;
extern void* lbl_8042C784[2]; // the two scene lights
extern u8 lbl_8042AEB0[4];
extern RwV3d lbl_8028AEA8;
extern RwV3d lbl_8028AEB4;
extern f32 lbl_8042EE68;
void fn_8004DC80(void* context, s32 value);
void fn_8019CD68(RwCamera* camera, f32 farPlane);
void fn_8019CF28(RwCamera* camera, void* colour, s32 mode);
void fn_8015B8E8(void* world, RwCamera* camera);
void fn_8015B93C(void* world, RwCamera* camera);
void fn_8015BD84(void* world, void* light);
void fn_8015BE24(void* world, void* light);
void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);
RwCamera* fn_8019CC28(RwCamera* camera);
RwCamera* fn_8019CC00(RwCamera* camera);
void fn_8004D650(void* context);
void fn_8004D678(void* context);
void fn_80018064(void* object);
void fn_80017AEC(void* object);
void fn_80177C50(void);
void RsCameraShowRaster(RwCamera* camera);

void fn_801302B0(Scene801302B0* scene)
{
	void* frame;

	if (lbl_8042C1F8 != 0) {
		fn_8004DC80(lbl_8042C1F8, 0);
	} else {
		fn_8019CD68(GetCurrentCameraPointer(), lbl_8042EE68);
	}
	fn_8019CF28(GetCurrentCameraPointer(), lbl_8042AEB0, 3);
	fn_8015B8E8(lbl_8042C780, GetCurrentCameraPointer());
	if (lbl_8042C784[0] != 0) {
		fn_8015BD84(lbl_8042C780, lbl_8042C784[0]);
	}
	if (lbl_8042C784[1] != 0) {
		fn_8015BD84(lbl_8042C780, lbl_8042C784[1]);
	}

	frame = ((Camera801302B0*)GetCurrentCameraPointer())->frame;
	if (frame != 0) {
		fn_8019EB94(frame, &lbl_8028AEA8, 0);
	}
	if (fn_8019CC28(GetCurrentCameraPointer()) != 0) {
		if (lbl_8042C1F8 != 0) {
			fn_8004D650(lbl_8042C1F8);
		}
		if (scene->object != 0) {
			fn_80018064(scene->object);
		}
		if (lbl_8042C1F8 != 0) {
			fn_8004D678(lbl_8042C1F8);
		}
		fn_8019CC00(GetCurrentCameraPointer());
	}

	frame = ((Camera801302B0*)GetCurrentCameraPointer())->frame;
	if (frame != 0) {
		fn_8019EB94(frame, &lbl_8028AEB4, 0);
	}
	if (fn_8019CC28(GetCurrentCameraPointer()) != 0) {
		if (lbl_8042C1F8 != 0) {
			fn_8004D650(lbl_8042C1F8);
		}
		if (scene->object != 0) {
			fn_80017AEC(scene->object);
		}
		if (lbl_8042C1F8 != 0) {
			fn_8004D678(lbl_8042C1F8);
		}
		fn_8019CC00(GetCurrentCameraPointer());
	}

	fn_8015B93C(lbl_8042C780, GetCurrentCameraPointer());
	if (lbl_8042C784[0] != 0) {
		fn_8015BE24(lbl_8042C780, lbl_8042C784[0]);
	}
	if (lbl_8042C784[1] != 0) {
		fn_8015BE24(lbl_8042C780, lbl_8042C784[1]);
	}
	fn_80177C50();
	RsCameraShowRaster(GetCurrentCameraPointer());
}
}
