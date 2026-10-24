#include "types.h"

// The egg capsule's Unload and Load hooks (s03EggCapUnload and s03EggCapLoad
// here): each of its models and the effect's UV animation are released; when
// the module's texture dictionary is there, it is made current, the module's
// model archive is read and each model loaded by its name (in stage 5, the
// ones whose flags have bit 0 set are left out). Then the effect's UV
// animation is loaded and, when the eighth model is there too, set on that
// model's first atomic as its custom texture effect.

// one of the family's models: its flags, the model once loaded and its file
// name
typedef struct S03EggCapModel {
	s32 flags;   // 0x00
	void* model; // 0x04
	u8 unk08[0x4];
	const char* name; // 0x0C
} S03EggCapModel;     // 0x10

// the custom texture effect set on the effect model (its UV animation first)
typedef struct S03EggCapEffect {
	void* animation; // 0x00
	u8 unk04[0x40];
} S03EggCapEffect;

// the game state (only the mode is read here)
typedef struct S03EggCapGameState {
	u8 unk00[0x2C];
	s32 mode; // 0x2C
} S03EggCapGameState;

extern "C" S03EggCapGameState lbl_8029C310;
extern "C" S03EggCapModel s03EggCapModels[];
extern "C" char s03EggCapEffectName[];
extern "C" void* s03EggCapEffectAnimation;
extern "C" S03EggCapEffect s03EggCapEffect;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8011B7CC(void* animation);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadUVAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(void* clump, void* atomic);
extern "C" void AtomicSetCustomFXTexture__FP8RpAtomicPv(void* atomic, void* effect);

extern "C" void s03EggCapUnload(void)
{
	S03EggCapModel* model = (S03EggCapModel*)s03EggCapModels;

	for (u8 i = 0; i < 9; i++) {
		if (model->model != NULL) {
			fn_80150958(model->model);
			model->model = NULL;
		}
		model++;
	}
	if (s03EggCapEffectAnimation != NULL) {
		fn_8011B7CC(s03EggCapEffectAnimation);
		s03EggCapEffectAnimation = NULL;
	}
}

extern "C" void s03EggCapLoad(void)
{
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S03EggCapModel* model = (S03EggCapModel*)s03EggCapModels;

	for (u8 i = 0; i < 9; i++) {
		if (lbl_8029C310.mode == 5 && (model->flags & 1)) {
			model++;
			continue;
		}
		model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), model->name), lbl_802FF5A0);
		model++;
	}
	void* animation = s03EggCapEffectAnimation
	    = LoadUVAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	        CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), s03EggCapEffectName),
	        lbl_802FF5A0);
	if (s03EggCapModels[7].model != NULL && animation != NULL) {
		s03EggCapEffect.animation = animation;
		AtomicSetCustomFXTexture__FP8RpAtomicPv(
		    objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(s03EggCapModels[7].model, NULL),
		    &s03EggCapEffect);
	}
}
