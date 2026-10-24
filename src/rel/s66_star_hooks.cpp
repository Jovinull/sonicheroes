#include "types.h"

// The shooting star's Unload and Load hooks (s66StarUnload and s66StarLoad
// here): its morph animation and its model are released, the data its callback
// gets being cleared with the model; when the module's texture dictionary is
// there, it is kept and made current, the model is loaded (its atomics going
// through the family's callback) and then its morph animation, whose frame
// count is kept.

extern "C" void* s66StarDictionary;
extern "C" void* s66StarModel;
extern "C" u32 s66StarCallbackData;
extern "C" void* s66StarMorph;
extern "C" f32 s66StarMorphFrames;
extern "C" char s66StarModelName[];
extern "C" char s66StarMorphName[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_8042C340[];
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8013BD74(void* animation);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_3_C9F78(void* atomic);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadDeltaMorphEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" f32 GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(void* anim, void* morph);

extern "C" void s66StarUnload(void)
{
	if (s66StarMorph != NULL) {
		fn_8013BD74(s66StarMorph);
		s66StarMorph = NULL;
	}
	if (s66StarModel != NULL) {
		fn_80150958(s66StarModel);
		s66StarModel        = NULL;
		s66StarCallbackData = 0;
	}
}

extern "C" void s66StarLoad(void)
{
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		s66StarDictionary = resource;
		fn_801A4C84(resource);
	} else {
		return;
	}
	s66StarModel = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), s66StarModelName), lbl_802FF5A0);
	fn_8014FFBC(s66StarModel, fn_3_C9F78, &s66StarCallbackData);
	void* morph = s66StarMorph = LoadDeltaMorphEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), s66StarMorphName), lbl_802FF5A0);
	if (morph != NULL) {
		s66StarMorphFrames = GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(lbl_8042C340, morph);
	}
}
