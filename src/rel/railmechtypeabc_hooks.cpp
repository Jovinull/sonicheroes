#include "types.h"

// The railmechtypeabc family's Reset, Unload and Load hooks
// (railmechtypeabcReset, railmechtypeabcUnload and railmechtypeabcLoad here):
// nothing to reset; the model files' models are released, with their
// animations; the module's texture dictionary is made current, the module's
// model archive is read and, for each animated model file, its model and,
// when it has one, its animation and the animation's key list are loaded,
// every file getting the family's frame step. The family's shared size is
// then reset to the edit default.

struct DANIM_KEY;
struct RtAnimAnimation;

// One of the module's animated model files: the archive it is read from, the
// model's and the animation's names, the model and animation once loaded, the
// animation's key list and count, and its frame step.
struct AnimModelFile {
	void* archive;         // 0x00
	const char* name;      // 0x04
	const char* animName;  // 0x08
	void* model;           // 0x0C
	RtAnimAnimation* anim; // 0x10
	DANIM_KEY* keys;       // 0x14
	s32 keyCount;          // 0x18
	f32 step;              // 0x1C
	u8 unk20[0x4];         // 0x20
}; // 0x24

class HAnimClass
{
public:
	void GetHAnimKeyList(DANIM_KEY* keys, int count, RtAnimAnimation* animation);
};

extern "C" AnimModelFile railmechtypeabcModelFiles[3];

extern "C" const f32 railmechtypeabcEditUnset[1];
extern "C" const f32 lbl_6_rodata_1454[1];
extern "C" f32 lbl_6_bss_155C;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];
extern HAnimClass HAnim;

extern "C" void fn_80150958(void* clump);
extern "C" void fn_801A4C84(void* resource);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void fn_8020C2D8(void* anim);

extern "C" void railmechtypeabcReset(void) { }

extern "C" void railmechtypeabcUnload(void)
{
	AnimModelFile* files = railmechtypeabcModelFiles;

	for (int i = 0; i < 3; i++) {
		fn_80150958(files[i].model);
		if (files[i].anim != NULL) {
			fn_8020C2D8(files[i].anim);
		}
	}
}

extern "C" void railmechtypeabcLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	AnimModelFile* files = railmechtypeabcModelFiles;
	for (int i = 0; i < 3; i++) {
		files[i].model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].name),
		    files[i].archive);
		if (files[i].animName != NULL) {
			files[i].anim
			    = (RtAnimAnimation*)LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			        CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].animName),
			        files[i].archive);
			HAnim.GetHAnimKeyList(files[i].keys, files[i].keyCount, files[i].anim);
		}
		files[i].step = lbl_6_rodata_1454[0];
	}
	lbl_6_bss_155C = railmechtypeabcEditUnset[0];
}
