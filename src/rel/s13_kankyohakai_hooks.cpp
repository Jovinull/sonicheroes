#include "types.h"

// The s13Kankyohakai family's Unload and Load hooks (s13KankyohakaiUnload and
// s13KankyohakaiLoad here): its nine model infos are released and its two
// cameras freed; when the module's model archive is there, it is read, each
// model info loaded and each camera loaded by its name.

// one of the stage's model infos (s13ModelInfoRelease and s13ModelInfoLoad
// handle them)
typedef struct S13ModelInfo {
	u8 unk00[0x18];
} S13ModelInfo; // 0x18

// one of the family's cameras: the camera once loaded and its name
typedef struct KankyohakaiCamera {
	void* camera;     // 0x00
	const char* name; // 0x04
} KankyohakaiCamera;  // 0x08

extern "C" S13ModelInfo s13KankyohakaiModels[9];
extern "C" KankyohakaiCamera s13KankyohakaiCameras[2];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8* lbl_8042C9A4;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadCameraTmbEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void s13ModelInfoRelease(S13ModelInfo* info);
extern "C" void s13ModelInfoLoad(S13ModelInfo* info, const char* name);

extern "C" void s13KankyohakaiUnload(void)
{
	S13ModelInfo* info = (S13ModelInfo*)s13KankyohakaiModels;

	for (u8 i = 0; i < 9; i++) {
		s13ModelInfoRelease(info);
		info++;
	}
	KankyohakaiCamera* camera = (KankyohakaiCamera*)s13KankyohakaiCameras;
	for (u8 i = 0; i < 2; i++) {
		(*(void (**)(void*))(lbl_8042C9A4 + 0x138))(camera->camera);
		camera->camera = NULL;
		camera++;
	}
}

extern "C" void s13KankyohakaiLoad(void)
{
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);
	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S13ModelInfo* info = (S13ModelInfo*)s13KankyohakaiModels;
	for (u8 i = 0; i < 9; i++) {
		s13ModelInfoLoad(info, NULL);
		info++;
	}
	KankyohakaiCamera* camera = (KankyohakaiCamera*)s13KankyohakaiCameras;
	for (u8 i = 0; i < 2; i++) {
		camera->camera = LoadCameraTmbEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), camera->name), lbl_802FF5A0);
		camera++;
	}
}
