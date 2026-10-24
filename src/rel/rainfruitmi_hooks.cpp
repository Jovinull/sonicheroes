#include "types.h"

// The rain fruit (small)'s editor-record hooks (rainfruitmiReset, rainfruitmiUnload and
// rainfruitmiLoad here): nothing to reset; its model is released; its model is
// loaded from the module's model archive.

extern "C" void* rainfruitmiModel;
extern "C" char rainfruitmiModelName[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_80150958(void* clump);
extern "C" void fn_801A4C84(void* resource);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void rainfruitmiReset(void) { }

extern "C" void rainfruitmiUnload(void)
{
	if (rainfruitmiModel != NULL) {
		fn_80150958(rainfruitmiModel);
		rainfruitmiModel = NULL;
	}
}

extern "C" void rainfruitmiLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	rainfruitmiModel = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), rainfruitmiModelName),
	    lbl_802FF5A0);
}
