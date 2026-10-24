#include "types.h"

// The water's Unload and Load hooks (s02WaterUnload and s02WaterLoad here):
// the water's UV animation and its ten models are released; the module's
// texture dictionary is made current, the module's model archive is read, the
// UV animation is loaded (its frame count kept) and each model loaded by its
// name, the UV animation being set on every model's first atomic as its custom
// texture effect.

// the custom texture effect set on the models (its UV animation first)
typedef struct S02WaterEffect {
	void* animation; // 0x00
	u8 unk04[0x40];
} S02WaterEffect;

extern "C" void* s02WaterModels[10];
extern "C" void* s02WaterAnimation;
extern "C" S02WaterEffect s02WaterEffect;
extern "C" f32 s02WaterAnimationFrames;
extern "C" char* s02WaterModelNames[10];
extern "C" char s02WaterAnimationName[];
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
extern "C" f32 objRpUVAnimAnimationGetTotalFrame__FP17RpUVAnimAnimation(void* animation);
extern "C" void* objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(void* clump, void* atomic);
extern "C" void AtomicSetCustomFXTexture__FP8RpAtomicPv(void* atomic, void* effect);

extern "C" void s02WaterUnload(void)
{
	if (s02WaterAnimation != NULL) {
		fn_8011B7CC(s02WaterAnimation);
		s02WaterAnimation = NULL;
	}
	for (u8 i = 0; i < 10; i++) {
		if (s02WaterModels[i] != NULL) {
			fn_80150958(s02WaterModels[i]);
			s02WaterModels[i] = NULL;
		}
	}
}

extern "C" void s02WaterLoad(void)
{
	fn_801A4C84(*(void**)(lbl_8042C1D0 + 0x8C18));
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	void* animation = s02WaterAnimation
	    = LoadUVAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	        CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), s02WaterAnimationName),
	        lbl_802FF5A0);
	if (animation != NULL) {
		s02WaterAnimationFrames
		    = objRpUVAnimAnimationGetTotalFrame__FP17RpUVAnimAnimation(animation);
	}
	for (u8 i = 0; i < 10; i++) {
		s02WaterModels[i] = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), s02WaterModelNames[i]),
		    lbl_802FF5A0);
		if (s02WaterModels[i] != NULL && s02WaterAnimation != NULL) {
			s02WaterEffect.animation = s02WaterAnimation;
			AtomicSetCustomFXTexture__FP8RpAtomicPv(
			    objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(s02WaterModels[i], NULL),
			    &s02WaterEffect);
		}
	}
}
