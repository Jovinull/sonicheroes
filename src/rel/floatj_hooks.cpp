#include "types.h"

// The floating jump's editor-record hooks (floatjReset, floatjUnload and
// floatjLoad here): nothing to reset; its model is released; its model is
// loaded from the module's model archive.

extern "C" void* floatJModel;
extern "C" char floatjModelName[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_80150958(void* clump);
extern "C" void fn_801A4C84(void* resource);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void floatjReset(void) { }

extern "C" void floatjUnload(void)
{
	if (floatJModel != NULL) {
		fn_80150958(floatJModel);
		floatJModel = NULL;
	}
}

extern "C" void floatjLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	floatJModel = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), floatjModelName), lbl_802FF5A0);
}
