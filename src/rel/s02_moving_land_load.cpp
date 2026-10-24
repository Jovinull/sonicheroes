#include "types.h"

// The moving platform's Load hook (s02MovingLandLoad here): when the stage's
// resources are there they are set up, the module's model archive is read and
// the three pieces' models are loaded from it.

extern "C" void* s02MovingLandModels[3];
extern "C" const char* s02MovingLandModelNames[3];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s02MovingLandLoad(void)
{
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	for (s8 i = 0; i < 3; i++) {
		s02MovingLandModels[i] = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), s02MovingLandModelNames[i]),
		    lbl_802FF5A0);
	}
}
