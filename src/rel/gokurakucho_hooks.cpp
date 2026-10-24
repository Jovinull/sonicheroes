#include "types.h"

// The bird of paradise's Unload and Load hooks (gokurakuchoUnload and
// gokurakuchoLoad here): the wings' morph animation, the body model and the
// wing model are released, the wing atomic the callback found being cleared
// with them; when the module's texture dictionary is there, it is kept and
// made current, the module's model archive is read, the body and wing models
// are loaded (the wing's atomics going through the family's callback, which
// keeps the one it is after) and then the wings' morph animation, whose frame
// count is kept.

extern "C" void* gokurakuchoDictionary;
extern "C" void* gokurakuchoModelFile;
extern "C" void* gokurakuchoWingModel;
extern "C" void* gokurakuchoReference;
extern "C" void* gokurakuchoWingMorph;
extern "C" f32 gokurakuchoWingFrames;
extern "C" char gokurakuchoBodyName[];
extern "C" char gokurakuchoWingName[];
extern "C" char gokurakuchoWingMorphName[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_8042C340[];
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8013BD74(void* animation);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_3_7DBA4(void* atomic);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadDeltaMorphEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" f32 GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(void* anim, void* morph);

extern "C" void gokurakuchoUnload(void)
{
	if (gokurakuchoWingMorph != NULL) {
		fn_8013BD74(gokurakuchoWingMorph);
		gokurakuchoWingMorph = NULL;
	}
	if (gokurakuchoModelFile != NULL) {
		fn_80150958(gokurakuchoModelFile);
		gokurakuchoModelFile = NULL;
	}
	if (gokurakuchoWingModel != NULL) {
		fn_80150958(gokurakuchoWingModel);
		gokurakuchoWingModel = NULL;
		gokurakuchoReference = NULL;
	}
}

extern "C" void gokurakuchoLoad(void)
{
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		gokurakuchoDictionary = resource;
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	gokurakuchoModelFile = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), gokurakuchoBodyName),
	    lbl_802FF5A0);
	gokurakuchoWingModel = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), gokurakuchoWingName),
	    lbl_802FF5A0);
	fn_8014FFBC(gokurakuchoWingModel, fn_3_7DBA4, &gokurakuchoReference);
	void* morph = gokurakuchoWingMorph
	    = LoadDeltaMorphEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	        CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), gokurakuchoWingMorphName),
	        lbl_802FF5A0);
	if (morph != NULL) {
		gokurakuchoWingFrames
		    = GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(lbl_8042C340, morph);
	}
}
