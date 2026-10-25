#include "types.h"

// The ivyjump family's Reset, Unload and Load hooks (ivyjumpReset,
// ivyjumpUnload and ivyjumpLoad here): nothing to reset; the model files'
// models are released, with their animations; the module's texture dictionary
// is made current, the family's material animation is set up and the module's
// model archive is read, then each animated model file gets its model loaded,
// its atomics going through the family's callback, and, when it has one, its
// animation (an animation in the second interpolation scheme being converted
// and the original released) and the animation's key list, every file getting
// the family's frame step; the first file's animation then also fills the
// family's five jump keys.

struct DANIM_KEY;

// the interpolation scheme an animation is keyed in
typedef struct RtAnimInterpolatorInfo {
	s32 typeID; // 0x00
} RtAnimInterpolatorInfo;

// an RtAnimAnimation: only its interpolation scheme is read here
typedef struct RtAnimAnimation {
	RtAnimInterpolatorInfo* interpInfo; // 0x00
} RtAnimAnimation;

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

extern "C" AnimModelFile ivyjumpModelFiles[2];
extern "C" MatAnim ivyjumpMatAnim;
extern "C" const f32 ivyjumpFrameStep;
extern "C" u8 ivyjumpJumpKeys[];
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
extern "C" void* fn_7_794E0(void* atomic);
extern "C" RtAnimAnimation* fn_8022CF5C(RtAnimAnimation* anim);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void ivyjumpReset(void) { }

extern "C" void ivyjumpUnload(void)
{
	AnimModelFile* files = ivyjumpModelFiles;

	for (int i = 0; i < 2; i++) {
		fn_80150958(files[i].model);
		if (files[i].anim != NULL) {
			fn_8020C2D8(files[i].anim);
		}
	}
}

extern "C" void ivyjumpLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	fn_8015C728(&ivyjumpMatAnim);
	fn_8015C6F8(&ivyjumpMatAnim, 3, 4);
	fn_8015C704(&ivyjumpMatAnim, 1, 0);
	fn_8015C710(&ivyjumpMatAnim, 1, 1, 6);
	fn_8015C720(&ivyjumpMatAnim, 3);
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	AnimModelFile* files = ivyjumpModelFiles;
	for (int i = 0; i < 2; i++) {
		files[i].model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].name),
		    files[i].archive);
		if (files[i].model != NULL) {
			fn_8014FFBC(files[i].model, fn_7_794E0, NULL);
		}
		if (files[i].animName != NULL) {
			files[i].anim
			    = (RtAnimAnimation*)LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			        CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), files[i].animName),
			        files[i].archive);
			if (files[i].anim->interpInfo->typeID != 2 && files[i].anim->interpInfo->typeID == 1) {
				RtAnimAnimation* converted = fn_8022CF5C(files[i].anim);
				fn_8020C2D8(files[i].anim);
				files[i].anim = converted;
			}
			HAnim.GetHAnimKeyList(files[i].keys, files[i].keyCount, files[i].anim);
		}
		files[i].step = ivyjumpFrameStep;
	}
	HAnim.GetHAnimKeyList((DANIM_KEY*)ivyjumpJumpKeys, 5, ivyjumpModelFiles[0].anim);
}
