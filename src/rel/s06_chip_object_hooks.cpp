#include "types.h"

// The casino chip's Unload and Load hooks (s06chipObjectUnload and s06chipObjectLoad here): its
// model is released; when the module's model archive is there, it is read
// and the model loaded from it.

extern "C" void* s06ChipModel;
extern "C" char s06ChipModelName[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_80150958(void* clump);
extern "C" void fn_801A4C84(void* resource);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s06chipObjectUnload(void)
{
	if (s06ChipModel != NULL) {
		fn_80150958(s06ChipModel);
		s06ChipModel = NULL;
	}
}

extern "C" void s06chipObjectLoad(void)
{
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);
	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	void* onefile = *(void**)(lbl_8042C298 + 0xA50);
	LoadOneFile__7ONEFILEFPc(onefile, lbl_802FF5A0);
	s06ChipModel = LoadClumpEx__7ONEFILEFUiPc(
	    onefile, CheckFileID__7ONEFILEFPc(onefile, s06ChipModelName), lbl_802FF5A0);
}
