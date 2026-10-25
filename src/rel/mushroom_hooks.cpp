#include "types.h"

// The mushroom family's Reset, Unload and Load hooks (mushroomReset,
// mushroomUnload and mushroomLoad here): nothing to reset; the model files'
// models are released, with their animations; the module's texture dictionary
// is made current, the family's material animation is set up and the module's
// model archive is read, then each animated model file gets its model loaded,
// its atomics going through the family's callback, and, when it has one, its
// animation and the animation's key list, every file getting the family's
// frame step.

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

// the family's material animation (fn_8015C6F8 and its neighbours set it up)
typedef struct MatAnim {
	u8 unk00[0x18];
} MatAnim;

class HAnimClass
{
public:
	void GetHAnimKeyList(DANIM_KEY* keys, int count, RtAnimAnimation* animation);
};

extern "C" AnimModelFile mushroomModelFiles[2];
extern "C" MatAnim mushroomMatAnim;
extern "C" const f32 mushroomFrameStep;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];
extern HAnimClass HAnim;

extern "C" void fn_80150958(void* clump);
extern "C" void fn_8020C2D8(void* anim);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_8015C728(MatAnim* anim);
extern "C" void fn_8015C6F8(MatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C704(MatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C710(MatAnim* anim, s32 a, s32 b, s32 c);
extern "C" void fn_8015C720(MatAnim* anim, s32 a);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_7_7BE38(void* atomic);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void mushroomReset(void) { }

extern "C" void mushroomUnload(void)
{
	AnimModelFile* files = mushroomModelFiles;

	for (int i = 0; i < 2; i++) {
		fn_80150958(files[i].model);
		if (files[i].anim != NULL) {
			fn_8020C2D8(files[i].anim);
		}
	}
}

extern "C" void mushroomLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	fn_8015C728(&mushroomMatAnim);
	fn_8015C6F8(&mushroomMatAnim, 3, 6);
	fn_8015C704(&mushroomMatAnim, 1, 0);
	fn_8015C710(&mushroomMatAnim, 1, 3, 8);
	fn_8015C720(&mushroomMatAnim, 3);
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	AnimModelFile* files = mushroomModelFiles;
	for (int i = 0; i < 2; i++) {
		files[i].model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].name),
		    files[i].archive);
		if (files[i].model != NULL) {
			fn_8014FFBC(files[i].model, fn_7_7BE38, NULL);
		}
		if (files[i].animName != NULL) {
			files[i].anim
			    = (RtAnimAnimation*)LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			        CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].animName),
			        files[i].archive);
			HAnim.GetHAnimKeyList(files[i].keys, files[i].keyCount, files[i].anim);
		}
		files[i].step = mushroomFrameStep;
	}
}
