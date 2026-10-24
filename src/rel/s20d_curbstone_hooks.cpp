#include "types.h"

// The curbstone's Unload and Load hooks (s20dCurbstoneUnload and
// s20dCurbstoneLoad here): both of its models are released; the module's
// texture dictionary is made current and each model is loaded by its name,
// the ones whose name is empty being left out (their slot cleared).

extern "C" char* s20dCurbstoneModelNames[2];
extern "C" void* s20dCurbstoneModels[2];
extern "C" char s20dCurbstoneEmptyName[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int strcmp(const char* a, const char* b);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s20dCurbstoneUnload(void)
{
	for (u8 i = 0; i < 2; i++) {
		if (s20dCurbstoneModels[i] != NULL) {
			fn_80150958(s20dCurbstoneModels[i]);
			s20dCurbstoneModels[i] = NULL;
		}
	}
}

extern "C" void s20dCurbstoneLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	for (u8 i = 0; i < 2; i++) {
		if (strcmp(s20dCurbstoneModelNames[i], s20dCurbstoneEmptyName) != 0) {
			s20dCurbstoneModels[i] = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			    CheckFileID__7ONEFILEFPc(
			        *(void**)(lbl_8042C298 + 0xA50), s20dCurbstoneModelNames[i]),
			    lbl_802FF5A0);
		} else {
			s20dCurbstoneModels[i] = NULL;
		}
	}
}
