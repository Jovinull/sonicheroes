#include "game/mobject.h"
#include "dolphin/gx/GXFrameBuffer.h"
#include "dolphin/os.h"
#include "dolphin/dvd.h"

// PS2 DWARF supplies the mobject.cpp filename, C++ language, MObject API and
// static member names. GameCube-only helper names below remain address labels.
struct RwFrame;
struct RwRaster;
struct MObjectV2 {
	f32 x, y;
};
struct MObjectV3 {
	f32 x, y, z;
};
struct MObjectBox {
	MObjectV3 sup, inf;
};
struct MObjectColor {
	f32 red, green, blue, alpha;
};
struct RwCamera {
	u32 unk_0x00;
	RwFrame* frame;
	u8 unk_0x08[0x58];
	RwRaster* raster;
	RwRaster* zRaster;
	MObjectV2 viewWindow;
};
struct RpLight {
	u32 unk_0x00;
	RwFrame* frame;
};
struct MObjectCameraTask {
	u8 unk_0x00[0x28];
	RwCamera* camera;
};
struct MObjectMainTask {
	u8 unk_0x00[0x38];
	s32 mode;
};
struct MObjectGlobals {
	const char* title;
	s32 width, height;
};
struct MObjectRwGlobals {
	RwCamera* currentCamera;
};
struct MObjectRenderMode {
	u8 unk_0x00[0x19];
	GXBool aa;
	u8 samples[12][2];
	u8 filter[7];
};
extern "C" {
extern MObjectGlobals RsGlobal;
extern MObjectRwGlobals* lbl_8042C9A4;
extern MObjectCameraTask* lbl_8042C1F8;
extern MObjectMainTask* lbl_8042C180;
extern MObjectRenderMode* lbl_8042CA3C;
extern GXBool lbl_8042C0C0;
extern u8 lbl_8029C310[0x298], lbl_80303EC8[0x70], lbl_8042C458[8], MoviePlaySub[0x10];
void fn_80012C10();
RwCamera* fn_800A8BBC(MObject*);
RwCamera* fn_8019CC00(RwCamera*);
RwCamera* fn_8019CC28(RwCamera*);
RwCamera* fn_8016EE88(RwCamera*);
RwCamera* fn_8019D1D8();
RwFrame* fn_8019E344();
void* fn_801A5370(void*, RwFrame*);
s32 fn_8019E480(RwFrame*);
RwRaster* fn_801A19D4(s32, s32, s32, s32);
s32 fn_801A173C(RwRaster*);
s32 fn_8019D178(RwCamera*);
RpWorld* fn_80159920(const MObjectBox*);
s32 fn_80159798(RpWorld*);
RpWorld* fn_8015B93C(RpWorld*, RwCamera*);
RpWorld* fn_8015B8E8(RpWorld*, RwCamera*);
RpWorld* fn_8015BE24(RpWorld*, RpLight*);
RpWorld* fn_8015BD84(RpWorld*, RpLight*);
RpLight* fn_80154414(s32);
s32 fn_801543B4(RpLight*);
RpLight* fn_80153EE0(RpLight*, const MObjectColor*);
RwCamera* fn_8019D0CC(RwCamera*, const MObjectV2*);
RwCamera* fn_8019CD68(RwCamera*, f32);
RwCamera* fn_8019CC9C(RwCamera*, f32);
}

RpWorld* MObject::pDefaultWorld;
RwCamera* MObject::pDefaultCamera;
RpLight* MObject::pDefaultAmbientLight;
RpLight* MObject::pDefaultDiffuseLight;
MObject* MObject::pCurrent_MObject;
// Descriptive private names inferred from the GameCube accesses.
s32 discHistoryPosition;
s32 MObject::module_number         = 1;
u8 softCopyFilter[7]               = { 2, 6, 16, 16, 16, 6, 2 };
MObject* MObject::mobject_table[4] = { (MObject*)lbl_8029C310, (MObject*)lbl_80303EC8,
	(MObject*)lbl_8042C458, (MObject*)MoviePlaySub };
s32 discHistory[40] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

void fn_800A74BC(s32 mode)
{
	switch (mode) {
		case 0: {
			s32 position = discHistoryPosition - 35;
			if (position < 0)
				position += 40;
			if (!discHistory[position])
				OSResetSystem(1, 0, 0);
			else
				fn_80012C10();
			break;
		}
		case 1:
			OSResetSystem(1, 0, 0);
			break;
	}
}
void fn_800A7548()
{
	discHistory[discHistoryPosition] = DVDCheckDisk();
	if (++discHistoryPosition >= 40)
		discHistoryPosition = 0;
}
void fn_800A7594()
{
	RwCamera* camera = lbl_8042C9A4->currentCamera;
	if (camera) {
		fn_8019CC00(camera);
		fn_8019CC28(camera);
		fn_8016EE88(camera);
	}
}
void fn_800A75E0()
{
	GXSetCopyFilter(lbl_8042CA3C->aa, lbl_8042CA3C->samples, lbl_8042C0C0, lbl_8042CA3C->filter);
}
void fn_800A7614()
{
	GXSetCopyFilter(lbl_8042CA3C->aa, lbl_8042CA3C->samples, lbl_8042C0C0, softCopyFilter);
}
RwCamera* GetMObjectCameraPointer()
{
	return MObject::pDefaultCamera;
}
RpWorld* GetCurrentWorldPointer()
{
	return MObject::pDefaultWorld;
}
RwCamera* GetCurrentCameraPointer()
{
	if (lbl_8042C1F8)
		return lbl_8042C1F8->camera;
	if (MObject::pDefaultCamera)
		return MObject::pDefaultCamera;
	if (lbl_8042C180) {
		switch (lbl_8042C180->mode) {
			case 0:
			case 1:
			case 4: {
				RwCamera* camera = fn_800A8BBC((MObject*)lbl_80303EC8);
				if (camera)
					return camera;
				break;
			}
		}
	}
	return 0;
}

inline void MObject::DestroyDefaultCamera()
{
	if (pDefaultCamera) {
		RwFrame* frame = pDefaultCamera->frame;
		if (frame) {
			fn_801A5370(pDefaultCamera, 0);
			fn_8019E480(frame);
		}
		if (pDefaultCamera->raster) {
			fn_801A173C(pDefaultCamera->raster);
			pDefaultCamera->raster = 0;
		}
		if (pDefaultCamera->zRaster) {
			fn_801A173C(pDefaultCamera->zRaster);
			pDefaultCamera->zRaster = 0;
		}
		fn_8019D178(pDefaultCamera);
		pDefaultCamera = 0;
	}
}
void MObject::DefaultCloseDown()
{
	if (pDefaultWorld) {
		if (pDefaultCamera)
			fn_8015B93C(pDefaultWorld, pDefaultCamera);
		if (pDefaultDiffuseLight)
			fn_8015BE24(pDefaultWorld, pDefaultDiffuseLight);
		if (pDefaultAmbientLight)
			fn_8015BE24(pDefaultWorld, pDefaultAmbientLight);
		fn_80159798(pDefaultWorld);
		pDefaultWorld = 0;
	}
	if (pDefaultCamera)
		DestroyDefaultCamera();
	if (pDefaultDiffuseLight) {
		RwFrame* frame = pDefaultDiffuseLight->frame;
		fn_801A5370(pDefaultDiffuseLight, 0);
		fn_8019E480(frame);
		fn_801543B4(pDefaultDiffuseLight);
		pDefaultDiffuseLight = 0;
	}
	if (pDefaultAmbientLight) {
		fn_801543B4(pDefaultAmbientLight);
		pDefaultAmbientLight = 0;
	}
}
inline RpWorld* MObject::CreateDefaultWorld()
{
	MObjectBox bb;
	bb.inf.x = bb.inf.y = bb.inf.z = -150.0f;
	bb.sup.x = bb.sup.y = bb.sup.z = 150.0f;
	pDefaultWorld                  = fn_80159920(&bb);
	return pDefaultWorld;
}
inline RwCamera* MObject::CreateDefaultCamera()
{
	s32 width = RsGlobal.width, height = RsGlobal.height;
	RwCamera* result = 0;
	pDefaultCamera   = fn_8019D1D8();
	if (pDefaultCamera) {
		fn_801A5370(pDefaultCamera, fn_8019E344());
		pDefaultCamera->raster  = fn_801A19D4(width, height, 0, 2);
		pDefaultCamera->zRaster = fn_801A19D4(width, height, 0, 1);
		if (pDefaultCamera->frame)
			result = pDefaultCamera;
	} else {
		DestroyDefaultCamera();
		return 0;
	}
	MObjectV2 window;
	if (lbl_8042C1F8)
		window = lbl_8042C1F8->camera->viewWindow;
	else {
		window.x = 0.615574061870575f;
		window.y = 0.5f;
	}
	fn_8019D0CC(pDefaultCamera, &window);
	fn_8019CD68(pDefaultCamera, 30.0f);
	fn_8019CC9C(pDefaultCamera, 0.1f);
	return result;
}
inline RpLight* MObject::CreateDefaultAmbientLight()
{
	pDefaultAmbientLight = fn_80154414(2);
	if (pDefaultAmbientLight) {
		MObjectColor color = { 0.0f, 0.0f, 0.0f, 1.0f };
		fn_80153EE0(pDefaultAmbientLight, &color);
	}
	return pDefaultAmbientLight;
}
void MObject::DefaultSetUp()
{
	CreateDefaultWorld();
	CreateDefaultCamera();
	CreateDefaultAmbientLight();
	if (pDefaultWorld) {
		if (pDefaultCamera)
			fn_8015B8E8(pDefaultWorld, pDefaultCamera);
		if (pDefaultDiffuseLight)
			fn_8015BD84(pDefaultWorld, pDefaultDiffuseLight);
		if (pDefaultAmbientLight)
			fn_8015BD84(pDefaultWorld, pDefaultAmbientLight);
	}
}
void getRidOfRwCameraMemoryLeakBugAndDefaultFontSet()
{
	RwCamera* camera = fn_8019D1D8();
	fn_801A5370(camera, fn_8019E344());
	camera->raster = fn_801A19D4(8, 8, 0, 2);
	fn_8019CC28(camera);
	fn_8019CC00(camera);
	RwFrame* frame = camera->frame;
	fn_801A5370(camera, 0);
	fn_8019E480(frame);
	fn_801A173C(camera->raster);
	camera->raster = 0;
	fn_8019D178(camera);
}
