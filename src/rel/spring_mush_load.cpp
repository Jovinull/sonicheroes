#include "types.h"

// The spring mushroom's Load hook (springMushLoad here): the module's model
// archive is read and the mushroom's delta morph animation loaded from it.

struct RpDMorphAnimation;

extern "C" RpDMorphAnimation* springMushResource;
extern "C" char springMushAnimName[];
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" RpDMorphAnimation* LoadDeltaMorphEx__7ONEFILEFUiPc(
    void* onefile, void* id, void* archive);

extern "C" void springMushLoad(void)
{
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	springMushResource = LoadDeltaMorphEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), springMushAnimName),
	    lbl_802FF5A0);
}
