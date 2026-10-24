#include "types.h"

// The rain mushroom's Load hook (rainmushLoad here): its two delta morph
// animations are loaded from the module's model archive and the first one's
// key list taken.

struct DANIM_KEY;
struct RpDMorphAnimation;

class DAnimClass
{
public:
	f32 GetDAnimKeyList(DANIM_KEY* keys, int count, int start, RpDMorphAnimation* animation);
};

extern "C" RpDMorphAnimation* rainmushTable[4];
extern "C" char rainmushAnimName0[];
extern "C" char rainmushAnimName1[];
extern "C" DANIM_KEY rainmushAnimKeys[];
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];
extern "C" DAnimClass lbl_8042C340;

extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" RpDMorphAnimation* LoadDeltaMorphEx__7ONEFILEFUiPc(
    void* onefile, void* id, void* archive);

extern "C" void rainmushLoad(void)
{
	rainmushTable[0] = LoadDeltaMorphEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), rainmushAnimName0), lbl_802FF5A0);
	rainmushTable[1] = LoadDeltaMorphEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), rainmushAnimName1), lbl_802FF5A0);
	lbl_8042C340.GetDAnimKeyList(rainmushAnimKeys, 2, 0, rainmushTable[0]);
}
