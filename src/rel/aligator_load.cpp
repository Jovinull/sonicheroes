#include "types.h"

// The alligator's Load hook (aligatorLoad here): the module's texture
// dictionary is made current and its model archive read; its animated model
// file's model is loaded and, when it has one, its animation and the
// animation's key list, the file getting the family's frame step; then its
// path is loaded by name.

struct DANIM_KEY;
struct RtAnimAnimation;

// the alligator's animated model file: the archive it is read from, the
// model's and the animation's names, the model and animation once loaded, the
// animation's key list and count, and its frame step
struct AnimModelFile {
	void* archive;              // 0x00
	const char* name;           // 0x04
	const char* anim;           // 0x08
	void* model;                // 0x0C
	RtAnimAnimation* animation; // 0x10
	DANIM_KEY* keys;            // 0x14
	s32 keyCount;               // 0x18
	f32 step;                   // 0x1C
	u8 unk20[0x4];              // 0x20
}; // 0x24

class HAnimClass
{
public:
	void GetHAnimKeyList(DANIM_KEY* keys, int count, RtAnimAnimation* animation);
};

extern "C" AnimModelFile aligatorModelFile[1];
extern "C" void* aligatorPath;
extern "C" char aligatorPathName[];
extern "C" const f32 aligatorFrameStep;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];
extern HAnimClass HAnim;

extern "C" void fn_801A4C84(void* resource);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadSplineEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void aligatorLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	AnimModelFile* files = aligatorModelFile;
	for (int i = 0; i < 1; i++) {
		files[i].model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].name),
		    files[i].archive);
		if (files[i].anim != NULL) {
			files[i].animation
			    = (RtAnimAnimation*)LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			        CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].anim),
			        files[i].archive);
			HAnim.GetHAnimKeyList(files[i].keys, files[i].keyCount, files[i].animation);
		}
		files[i].step = aligatorFrameStep;
	}
	aligatorPath = LoadSplineEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), aligatorPathName), lbl_802FF5A0);
}
