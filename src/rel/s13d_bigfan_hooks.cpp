#include "types.h"

// The s13dBigfan family's Unload and Load hooks (s13dBigfanUnload and
// s13dBigfanLoad here): its model infos are released; when the module's model
// archive is there, it is read and each model info loaded.

// one of the stage's larger model infos (fn_9_76448 and fn_9_765CC handle
// them)
typedef struct S13ModelInfoEx {
	u8 unk00[0x2C];
} S13ModelInfoEx; // 0x2C

extern "C" S13ModelInfoEx s13dBigfanModels[2];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void fn_9_76448(S13ModelInfoEx* info);
extern "C" void fn_9_765CC(S13ModelInfoEx* info, const char* name);

extern "C" void s13dBigfanUnload(void)
{
	S13ModelInfoEx* info = (S13ModelInfoEx*)s13dBigfanModels;

	for (u8 i = 0; i < 2; i++) {
		fn_9_76448(info);
		info++;
	}
}

extern "C" void s13dBigfanLoad(void)
{
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);
	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S13ModelInfoEx* info = (S13ModelInfoEx*)s13dBigfanModels;
	for (u8 i = 0; i < 2; i++) {
		fn_9_765CC(info, NULL);
		info++;
	}
}
