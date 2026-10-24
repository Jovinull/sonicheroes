#include "types.h"

// The thunder's Unload and Load hooks (s14ThunderUnload and s14ThunderLoad
// here): its model info is released while it holds a model; when the module's
// texture dictionary is there, it is made current, the module's model archive
// is read and the model info loaded unless it already holds one.

// one of the stage's model infos (s13ModelInfoRelease and s13ModelInfoLoad
// handle them)
typedef struct S13ModelInfo {
	u8 unk00[0x10];
	void* model; // 0x10
	u8 unk14[0x4];
} S13ModelInfo; // 0x18

extern "C" S13ModelInfo s14ThunderModels[1];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" char lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* dictionary);
extern "C" void LoadOneFile__7ONEFILEFPc(void* file, char* name);
extern "C" void s13ModelInfoRelease(S13ModelInfo* info);
extern "C" void s13ModelInfoLoad(S13ModelInfo* info, const char* name);

extern "C" void s14ThunderUnload(void)
{
	S13ModelInfo* file = s14ThunderModels;

	for (u8 i = 0; i < 1; i++) {
		if (file->model == NULL) {
			return;
		}
		s13ModelInfoRelease(file);
		file++;
	}
}

extern "C" void s14ThunderLoad(void)
{
	void* dictionary = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (dictionary != NULL) {
		fn_801A4C84(dictionary);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S13ModelInfo* file = s14ThunderModels;

	for (u8 i = 0; i < 1; i++) {
		if (file->model != NULL) {
			return;
		}
		s13ModelInfoLoad(file, NULL);
		file++;
	}
}
