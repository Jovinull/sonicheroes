#include "types.h"

// The barrel's Load hook (barrelLoad here): the module's model archive is read
// and, for each animated model file, its model and, when it has one, its
// animation and the animation's key list; each file's frame step is a sixtieth.

// One of the module's animated model files: the archive it is read from, the
// model's and the animation's names, the model and animation once loaded, the
// animation's key list and count, and its frame step.
struct DANIM_KEY;
struct RtAnimAnimation;

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

extern "C" AnimModelFile barrelModelFiles[2];
extern "C" const f32 barrelFrameStep[1];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];
extern HAnimClass HAnim;

extern "C" void fn_801A4C84(void* resource);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void barrelLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	AnimModelFile* files = barrelModelFiles;
	for (int i = 0; i < 2; i++) {
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
		files[i].step = barrelFrameStep[0];
	}
}
