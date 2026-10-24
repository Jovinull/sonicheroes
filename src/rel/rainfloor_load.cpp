#include "types.h"

// The rain floor's Load hook (rainfloorLoad here): its delta morph animation
// is loaded from the module's model archive.

struct RpDMorphAnimation;

extern "C" RpDMorphAnimation* rainfloorResource;
extern "C" char rainfloorAnimName[];
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" RpDMorphAnimation* LoadDeltaMorphEx__7ONEFILEFUiPc(
    void* onefile, void* id, void* archive);

extern "C" void rainfloorLoad(void)
{
	rainfloorResource = LoadDeltaMorphEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), rainfloorAnimName), lbl_802FF5A0);
}
