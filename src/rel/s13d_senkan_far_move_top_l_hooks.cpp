#include "types.h"

// The s13dSenkanFarMoveTopL family's Unload and Load hooks (s13dSenkanFarMoveTopLUnload and s13dSenkanFarMoveTopLLoad
// here): its model infos are released; when the module's texture dictionary is there, it is made
// current, the module's model archive is read and each model info loaded. Both run only once
// in a row, through the family's loaded and unloaded flags.

// one of the stage's model infos (s13ModelInfoRelease and s13ModelInfoLoad
// handle them)
typedef struct S13ModelInfo {
	u8 unk00[0x18];
} S13ModelInfo; // 0x18

extern "C" S13ModelInfo s13ShipFarModels[9];
extern "C" s32 s13dSenkanFarMoveTopLLoaded;
extern "C" s32 s13dSenkanFarMoveTopLUnloaded;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" char lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* dictionary);
extern "C" void LoadOneFile__7ONEFILEFPc(void* file, char* name);
extern "C" void s13ModelInfoRelease(S13ModelInfo* info);
extern "C" void s13ModelInfoLoad(S13ModelInfo* info, const char* name);

extern "C" void s13dSenkanFarMoveTopLUnload(void)
{
	if (s13dSenkanFarMoveTopLUnloaded == 1) {
		return;
	}
	S13ModelInfo* file = s13ShipFarModels;

	for (u8 i = 0; i < 9; i++) {
		s13ModelInfoRelease(file);
		file++;
	}
	s13dSenkanFarMoveTopLLoaded   = 0;
	s13dSenkanFarMoveTopLUnloaded = 1;
}

extern "C" void s13dSenkanFarMoveTopLLoad(void)
{
	if (s13dSenkanFarMoveTopLLoaded == 1) {
		return;
	}
	void* dictionary = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (dictionary != NULL) {
		fn_801A4C84(dictionary);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S13ModelInfo* file = s13ShipFarModels;

	for (u8 i = 0; i < 9; i++) {
		s13ModelInfoLoad(file, NULL);
		file++;
	}
	s13dSenkanFarMoveTopLLoaded   = 1;
	s13dSenkanFarMoveTopLUnloaded = 0;
}
