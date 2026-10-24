#include "types.h"

// The s14Koware family's Unload and Load hooks (s14KowareUnload and
// s14KowareLoad here): its model infos are released; when the module's
// model archive is there, it is read and each model info loaded.

// one of the stage's model infos (s13ModelInfoRelease and s13ModelInfoLoad
// handle them)
typedef struct S13ModelInfo {
	u8 unk00[0x18];
} S13ModelInfo; // 0x18

extern "C" S13ModelInfo s14KowareModels[2];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void s13ModelInfoRelease(S13ModelInfo* info);
extern "C" void s13ModelInfoLoad(S13ModelInfo* info, const char* name);

extern "C" void s14KowareUnload(void)
{
	S13ModelInfo* info = (S13ModelInfo*)s14KowareModels;

	for (u8 i = 0; i < 2; i++) {
		s13ModelInfoRelease(info);
		info++;
	}
}

extern "C" void s14KowareLoad(void)
{
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);
	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S13ModelInfo* info = (S13ModelInfo*)s14KowareModels;
	for (u8 i = 0; i < 2; i++) {
		s13ModelInfoLoad(info, NULL);
		info++;
	}
}
