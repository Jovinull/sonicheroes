#include "types.h"

// The turtle's Unload and Load hooks (s02dKameashiUnload and
// s02dKameashiLoad here): its body model, the body's animation and the shell's
// UV animation are released, then both leg models and their morphs. When the
// module's texture dictionary is there, it is made current, the module's model
// archive is read, the body model and its animation are loaded, then each leg
// model (its atomics going through the leg callback, which keeps the leg's
// atomic) and its morph, whose frame count and one-second step are kept and
// which is set on the leg's atomic. Finally the archive is read again for the
// shell's UV animation, set on the second leg's atomic as its custom texture
// effect.

// what the leg callback gets: the leg's index and where to keep the atomic it
// finds
typedef struct S02dKameashiCallbackData {
	s8 index;
	void** atomic; // 0x04
} S02dKameashiCallbackData;

// the custom texture effect set on the second leg (its UV animation first)
typedef struct S02dKameashiEffect {
	void* animation; // 0x00
	u8 unk04[0x40];
} S02dKameashiEffect;

extern "C" void* s02dKameashiBodyModel;
extern "C" void* s02dKameashiBodyAnimation;
extern "C" f32 s02dKameashiLegFrames[2];
extern "C" f32 s02dKameashiLegStep[2];
extern "C" void* s02dKameashiShellAnimation;
extern "C" S02dKameashiEffect s02dKameashiShellEffect;
extern "C" void* s02dKameashiLegModels[2];
extern "C" void* s02dKameashiLegAtomics[2];
extern "C" void* s02dKameashiLegMorphs[2];
extern "C" char* s02dKameashiLegNames[2];
extern "C" char* s02dKameashiLegMorphNames[2];
extern "C" char s02dKameashiBodyName[];
extern "C" char s02dKameashiBodyAnimationName[];
extern "C" char s02dKameashiShellAnimationName[];
extern "C" const S02dKameashiCallbackData lbl_3_rodata_1960;
extern "C" const f32 lbl_3_rodata_19AC;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_8042C340[];
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8013BD74(void* morph);
extern "C" void fn_8020C2D8(void* animation);
extern "C" void fn_8011B7CC(void* animation);
extern "C" void fn_8013D344(void* atomic, void* morph);
extern "C" void fn_801491A8(void* atomic);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_3_9C5FC(void* atomic);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadDeltaMorphEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadUVAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" f32 GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(void* anim, void* morph);
extern "C" void AtomicSetCustomFXTexture__FP8RpAtomicPv(void* atomic, void* effect);

extern "C" void s02dKameashiUnload(void)
{
	if (s02dKameashiBodyModel != NULL) {
		fn_80150958(s02dKameashiBodyModel);
		s02dKameashiBodyModel = NULL;
	}
	if (s02dKameashiBodyAnimation != NULL) {
		fn_8020C2D8(s02dKameashiBodyAnimation);
		s02dKameashiBodyAnimation = NULL;
	}
	if (s02dKameashiShellAnimation != NULL) {
		fn_8011B7CC(s02dKameashiShellAnimation);
		s02dKameashiShellAnimation = NULL;
	}
	for (s32 i = 0; i < 2; i++) {
		if (s02dKameashiLegModels[i] != NULL) {
			fn_80150958(s02dKameashiLegModels[i]);
			s02dKameashiLegModels[i] = NULL;
		}
		if (s02dKameashiLegMorphs[i] != NULL) {
			fn_8013BD74(s02dKameashiLegMorphs[i]);
			s02dKameashiLegMorphs[i] = NULL;
		}
	}
}

extern "C" void s02dKameashiLoad(void)
{
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	s02dKameashiBodyModel     = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), s02dKameashiBodyName),
	    lbl_802FF5A0);
	s02dKameashiBodyAnimation = LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), s02dKameashiBodyAnimationName),
	    lbl_802FF5A0);
	for (s32 i = 0; i < 2; i++) {
		s02dKameashiLegModels[i] = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), s02dKameashiLegNames[i]),
		    lbl_802FF5A0);
		if (s02dKameashiLegModels[i] != NULL) {
			S02dKameashiCallbackData data = lbl_3_rodata_1960;

			data.index  = i;
			data.atomic = &s02dKameashiLegAtomics[i];
			fn_8014FFBC(s02dKameashiLegModels[i], fn_3_9C5FC, &data);
		}
		s02dKameashiLegMorphs[i] = LoadDeltaMorphEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), s02dKameashiLegMorphNames[i]),
		    lbl_802FF5A0);
		if (s02dKameashiLegMorphs[i] != NULL) {
			s02dKameashiLegFrames[i] = GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(
			    lbl_8042C340, s02dKameashiLegMorphs[i]);
			s02dKameashiLegStep[i] = lbl_3_rodata_19AC / s02dKameashiLegFrames[i];
			fn_8013D344(s02dKameashiLegAtomics[i], s02dKameashiLegMorphs[i]);
		}
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	if ((s02dKameashiShellAnimation
	        = LoadUVAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	            CheckFileID__7ONEFILEFPc(
	                *(void**)(lbl_8042C298 + 0xA50), s02dKameashiShellAnimationName),
	            lbl_802FF5A0))
	    != NULL) {
		s02dKameashiShellEffect.animation = s02dKameashiShellAnimation;
		AtomicSetCustomFXTexture__FP8RpAtomicPv(
		    s02dKameashiLegAtomics[1], &s02dKameashiShellEffect);
		fn_801491A8(s02dKameashiLegAtomics[1]);
	}
}
