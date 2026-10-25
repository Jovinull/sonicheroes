#include "types.h"

// The green frog's Load hook (froggreenLoad here): the module's texture
// dictionary is made current, the family's material animation is set up and
// the module's model archive is read, then each animated model file gets its
// model loaded, its atomics going through the family's callback, and, when it
// has one, its animation (an animation in the second interpolation scheme
// being converted and the original released) and the animation's key list,
// every file getting the family's frame step. On stage 9 only the first file
// is loaded: the second is left empty.

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

typedef struct GameState {
	u8 unk00[0x34];
	s32* stage; // 0x34: the stage id is its second word
} GameState;

class HAnimClass
{
public:
	void GetHAnimKeyList(DANIM_KEY* keys, int count, RtAnimAnimation* animation);
};

extern "C" AnimModelFile froggreenModelFiles[2];
extern "C" MatAnim froggreenMatAnim;
extern "C" const f32 froggreenFrameStep;
extern "C" GameState lbl_8029C310;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];
extern HAnimClass HAnim;

extern "C" void fn_8020C2D8(void* anim);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_8015C728(MatAnim* anim);
extern "C" void fn_8015C6F8(MatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C704(MatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C710(MatAnim* anim, s32 a, s32 b, s32 c);
extern "C" void fn_8015C720(MatAnim* anim, s32 a);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_7_770CC(void* atomic);
extern "C" RtAnimAnimation* fn_8022CF5C(RtAnimAnimation* anim);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void froggreenLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	fn_8015C728(&froggreenMatAnim);
	fn_8015C6F8(&froggreenMatAnim, 3, 6);
	fn_8015C704(&froggreenMatAnim, 1, 0);
	fn_8015C710(&froggreenMatAnim, 1, 3, 8);
	fn_8015C720(&froggreenMatAnim, 3);
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	for (int i = 0; i < 2; i++) {
		AnimModelFile* file = &froggreenModelFiles[i];

		if (lbl_8029C310.stage[1] == 9 && i >= 1) {
			file->model = NULL;
			file->anim  = NULL;
			break;
		}
		file->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), file->name), file->archive);
		if (file->model != NULL) {
			fn_8014FFBC(file->model, fn_7_770CC, NULL);
		}
		if (file->animName != NULL) {
			file->anim
			    = (RtAnimAnimation*)LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			        CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), file->animName),
			        file->archive);
			if (file->anim->interpInfo->typeID != 2 && file->anim->interpInfo->typeID == 1) {
				RtAnimAnimation* converted = fn_8022CF5C(file->anim);
				fn_8020C2D8(file->anim);
				file->anim = converted;
			}
			HAnim.GetHAnimKeyList(file->keys, file->keyCount, file->anim);
		}
		file->step = froggreenFrameStep;
	}
}
