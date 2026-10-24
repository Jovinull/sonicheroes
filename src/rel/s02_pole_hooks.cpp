#include "types.h"

// The pole's Unload and Load hooks (s02PoleUnload and s02PoleLoad here): the
// UV animation and both models of each of its two kinds are released; the
// module's texture dictionary is made current, the module's model archive is
// read, the UV animation is loaded (its frame count kept) and each model is
// loaded by its name, the ones whose name is empty being left out (their slot
// cleared). The second model of each kind gets the UV animation on its first
// atomic as its custom texture effect. Each model goes through an inline
// helper, called once per model of a kind.

// the custom texture effect set on the second models (its UV animation first)
typedef struct S02PoleEffect {
	void* animation; // 0x00
	u8 unk04[0x40];
} S02PoleEffect;

extern "C" void* s02PoleAnimation;
extern "C" void* s02PoleModels[2][2];
extern "C" f32 s02PoleAnimationFrames;
extern "C" S02PoleEffect s02PoleEffect;
extern "C" char* s02PoleModelNames[2][2];
extern "C" char s02PoleAnimationName[];
extern "C" char s02PoleEmptyName[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int strcmp(const char* a, const char* b);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8011B7CC(void* animation);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadUVAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" f32 objRpUVAnimAnimationGetTotalFrame__FP17RpUVAnimAnimation(void* animation);
extern "C" void* objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(void* clump, void* atomic);
extern "C" void AtomicSetCustomFXTexture__FP8RpAtomicPv(void* atomic, void* effect);

// one model's release
static inline void s02PoleRelease(void** model)
{
	if (*model != NULL) {
		fn_80150958(*model);
		*model = NULL;
	}
}

// one model's load, by its name unless the name is empty
static inline void s02PoleLoadModel(void** model, char** name)
{
	if (strcmp(*name, s02PoleEmptyName) != 0) {
		*model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), *name), lbl_802FF5A0);
	} else {
		*model = NULL;
	}
}

// the same, with the UV animation set on the loaded model
static inline void s02PoleLoadEffectModel(void** model, char** name)
{
	if (strcmp(*name, s02PoleEmptyName) != 0) {
		*model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), *name), lbl_802FF5A0);
		if (*model != NULL) {
			s02PoleEffect.animation = s02PoleAnimation;
			AtomicSetCustomFXTexture__FP8RpAtomicPv(
			    objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(*model, NULL), &s02PoleEffect);
		}
	} else {
		*model = NULL;
	}
}

extern "C" void s02PoleUnload(void)
{
	if (s02PoleAnimation != NULL) {
		fn_8011B7CC(s02PoleAnimation);
		s02PoleAnimation = NULL;
	}
	for (u8 i = 0; i < 2; i++) {
		s02PoleRelease(&s02PoleModels[i][0]);
		s02PoleRelease(&s02PoleModels[i][1]);
	}
}

extern "C" void s02PoleLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	void* animation = s02PoleAnimation
	    = LoadUVAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	        CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), s02PoleAnimationName),
	        lbl_802FF5A0);
	if (animation != NULL) {
		s02PoleAnimationFrames
		    = objRpUVAnimAnimationGetTotalFrame__FP17RpUVAnimAnimation(animation);
	}
	for (u8 i = 0; i < 2; i++) {
		s02PoleLoadModel(&s02PoleModels[i][0], &s02PoleModelNames[i][0]);
		s02PoleLoadEffectModel(&s02PoleModels[i][1], &s02PoleModelNames[i][1]);
	}
}
