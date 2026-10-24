#include "types.h"

// The s13dRailArrow1 family's Unload and Load hooks (s13dRailArrow1Unload and s13dRailArrow1Load
// here): its model infos are released; when the module's texture dictionary is there, it is made
// current, the module's model archive is read and each model info loaded. Both run only once
// in a row, through the family's loaded and unloaded flags.

// one of the stage's model infos (s13ModelInfoRelease and s13ModelInfoLoad
// handle them)
typedef struct S13ModelInfo {
	u8 unk00[0x18];
} S13ModelInfo; // 0x18

extern "C" S13ModelInfo s13dRailArrow1Models[4];
extern "C" s32 s13dRailArrow1Loaded;
extern "C" s32 s13dRailArrow1Unloaded;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" char lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* dictionary);
extern "C" void LoadOneFile__7ONEFILEFPc(void* file, char* name);
extern "C" void s13ModelInfoRelease(S13ModelInfo* info);
extern "C" void s13ModelInfoLoad(S13ModelInfo* info, const char* name);

extern "C" void s13dRailArrow1Unload(void)
{
	if (s13dRailArrow1Unloaded == 1) {
		return;
	}
	S13ModelInfo* file = s13dRailArrow1Models;

	for (u8 i = 0; i < 4; i++) {
		s13ModelInfoRelease(file);
		file++;
	}
	s13dRailArrow1Loaded   = 0;
	s13dRailArrow1Unloaded = 1;
}

extern "C" void s13dRailArrow1Load(void)
{
	if (s13dRailArrow1Loaded == 1) {
		return;
	}
	void* dictionary = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (dictionary != NULL) {
		fn_801A4C84(dictionary);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S13ModelInfo* file = s13dRailArrow1Models;

	for (u8 i = 0; i < 4; i++) {
		s13ModelInfoLoad(file, NULL);
		file++;
	}
	s13dRailArrow1Loaded   = 1;
	s13dRailArrow1Unloaded = 0;
}
