#include "types.h"

// The bigcannon family's Reset, Unload and Load hooks (bigcannonReset,
// bigcannonUnload and bigcannonLoad here): nothing to reset; the model files'
// models are released, with their animations; the module's texture dictionary
// is made current and, for each animated model file, its model and, when it
// has one, its animation and the animation's key list are loaded, every file
// getting the family's frame step.

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

extern "C" AnimModelFile bigcannonModelFiles[6];

extern "C" const f32 lbl_6_rodata_1240[1];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern HAnimClass HAnim;

extern "C" void fn_80150958(void* clump);
extern "C" void fn_801A4C84(void* resource);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void fn_8020C2D8(void* anim);

extern "C" void bigcannonReset(void) { }

extern "C" void bigcannonUnload(void)
{
	AnimModelFile* files = bigcannonModelFiles;

	for (int i = 0; i < 6; i++) {
		fn_80150958(files[i].model);
		if (files[i].anim != NULL) {
			fn_8020C2D8(files[i].anim);
		}
	}
}

extern "C" void bigcannonLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	AnimModelFile* files = bigcannonModelFiles;
	for (int i = 0; i < 6; i++) {
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
		files[i].step = lbl_6_rodata_1240[0];
	}
}
