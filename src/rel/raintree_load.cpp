#include "types.h"

// The rain tree's Load hook (raintreeLoad here): its delta morph animation is
// loaded from the module's model archive and its key list taken; the frame
// step is the key count per hundredth.

struct DANIM_KEY;
struct RpDMorphAnimation;

class DAnimClass
{
public:
	f32 GetDAnimKeyList(DANIM_KEY* keys, int count, int start, RpDMorphAnimation* animation);
};

extern "C" RpDMorphAnimation* raintreeResource;
extern "C" char raintreeAnimName[];
extern "C" DANIM_KEY raintreeAnimKeys[];
extern "C" f32 raintreeFrameStep;
extern "C" const f32 raintreeFrameScale[1];
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];
extern "C" DAnimClass lbl_8042C340;

extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" RpDMorphAnimation* LoadDeltaMorphEx__7ONEFILEFUiPc(
    void* onefile, void* id, void* archive);

extern "C" void raintreeLoad(void)
{
	raintreeResource  = LoadDeltaMorphEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), raintreeAnimName), lbl_802FF5A0);
	raintreeFrameStep = lbl_8042C340.GetDAnimKeyList(raintreeAnimKeys, 1, 0, raintreeResource)
	    / raintreeFrameScale[0];
}
