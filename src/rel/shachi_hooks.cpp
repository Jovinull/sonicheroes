#include "types.h"

// The killer whale's Unload and Load hooks (shachiUnload and shachiLoad here):
// both of its models are released; when the module's texture dictionary is
// there, it is kept and made current, then both models are loaded by their
// names.

extern "C" char* shachiModelNames[2];
extern "C" void* shachiModels[2];
extern "C" void* shachiDictionary;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void shachiUnload(void)
{
	for (u8 i = 0; i < 2; i++) {
		if (shachiModels[i] != NULL) {
			fn_80150958(shachiModels[i]);
			shachiModels[i] = NULL;
		}
	}
}

extern "C" void shachiLoad(void)
{
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		shachiDictionary = resource;
		fn_801A4C84(resource);
	} else {
		return;
	}
	for (u8 i = 0; i < 2; i++) {
		shachiModels[i] = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), shachiModelNames[i]),
		    lbl_802FF5A0);
	}
}
