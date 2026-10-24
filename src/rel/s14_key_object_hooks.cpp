#include "types.h"

// The stage key's Unload and Load hooks (s14keyObjectUnload and s14keyObjectLoad here): its
// model is released; when the module's model archive is there, it is read
// and the model loaded from it.

extern "C" void* s14KeyModel;
extern "C" char s14KeyModelName[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_80150958(void* clump);
extern "C" void fn_801A4C84(void* resource);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s14keyObjectUnload(void)
{
	if (s14KeyModel != NULL) {
		fn_80150958(s14KeyModel);
		s14KeyModel = NULL;
	}
}

extern "C" void s14keyObjectLoad(void)
{
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);
	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	void* onefile = *(void**)(lbl_8042C298 + 0xA50);
	LoadOneFile__7ONEFILEFPc(onefile, lbl_802FF5A0);
	s14KeyModel = LoadClumpEx__7ONEFILEFUiPc(
	    onefile, CheckFileID__7ONEFILEFPc(onefile, s14KeyModelName), lbl_802FF5A0);
}
