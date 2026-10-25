#include "types.h"

// The moving ruins' Unload and Load hooks (s01MoveIsekiUnload and
// s01MoveIsekiLoad here), over three ruins. The Unload releases each ruin's
// atomic (through fn_800B8B48) and model, its second model and its UV
// animation. The Load keeps the module's texture dictionary and makes it
// current, reads the module's model archive, loads each ruin's model (keeping
// its first atomic and that atomic's geometry, the atomic going through
// fn_800B8CC4), then each ruin's second model and its UV animation: the
// second model's atomics go through two callbacks that find the atomic and
// the data the ruin needs, the atomic's 0x48 field is kept and the UV
// animation is set on that atomic as its custom texture effect.

// the custom texture effect of one ruin (its UV animation first)
typedef struct S01MoveIsekiEffect {
	void* animation; // 0x00
	u8 unk04[0x40];
} S01MoveIsekiEffect;

extern "C" void* s01MoveIsekiModels[3];
extern "C" void* s01MoveIsekiAtomics[3];
extern "C" void* s01MoveIsekiGeometries[3];
extern "C" void* s01MoveIsekiEffectModels[3];
extern "C" u8* s01MoveIsekiEffectAtomics[3];
extern "C" void* s01MoveIsekiAnimations[3];
extern "C" u32 lbl_3_data_ADFC[3];
extern "C" char* s01MoveIsekiModelNames[3];
extern "C" char* s01MoveIsekiEffectModelNames[3];
extern "C" char s01MoveIsekiAnimationName[];
extern "C" u32 lbl_3_bss_15EC[3];
extern "C" void* s01MoveIsekiDictionary;
extern "C" S01MoveIsekiEffect s01MoveIsekiEffects[3];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8011B7CC(void* animation);
extern "C" void fn_800B8B48(void* atomic);
extern "C" void fn_800B8CC4(void* atomic, s32 flag);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_3_861C4(void* atomic);
extern "C" void* fn_3_861CC(void* atomic);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadUVAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(void* clump, void* atomic);
extern "C" void AtomicSetCustomFXTexture__FP8RpAtomicPv(void* atomic, void* effect);

extern "C" void s01MoveIsekiUnload(void)
{
	for (s8 i = 0; i < 3; i++) {
		if (s01MoveIsekiModels[i] != NULL) {
			fn_800B8B48(s01MoveIsekiAtomics[i]);
			s01MoveIsekiAtomics[i]    = NULL;
			s01MoveIsekiGeometries[i] = NULL;
			fn_80150958(s01MoveIsekiModels[i]);
			s01MoveIsekiModels[i] = NULL;
		}
		if (s01MoveIsekiEffectModels[i] != NULL) {
			fn_80150958(s01MoveIsekiEffectModels[i]);
			s01MoveIsekiEffectModels[i] = NULL;
		}
		if (s01MoveIsekiAnimations[i] != NULL) {
			fn_8011B7CC(s01MoveIsekiAnimations[i]);
			s01MoveIsekiAnimations[i] = NULL;
		}
	}
}

extern "C" void s01MoveIsekiLoad(void)
{
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		s01MoveIsekiDictionary = resource;
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	for (s32 i = 0; i < 3; i++) {
		s01MoveIsekiModels[i] = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), s01MoveIsekiModelNames[i]),
		    lbl_802FF5A0);
		if (s01MoveIsekiModels[i] != NULL) {
			s01MoveIsekiAtomics[i]
			    = objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(s01MoveIsekiModels[i], NULL);
			if (s01MoveIsekiAtomics[i] != NULL) {
				s01MoveIsekiGeometries[i] = *(void**)((u8*)s01MoveIsekiAtomics[i] + 0x18);
				fn_800B8CC4(s01MoveIsekiAtomics[i], 0);
			}
		}
	}
	for (s32 i = 0; i < 3; i++) {
		s01MoveIsekiEffectModels[i] = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(
		        *(void**)(lbl_8042C298 + 0xA50), s01MoveIsekiEffectModelNames[i]),
		    lbl_802FF5A0);
		s01MoveIsekiAnimations[i]   = LoadUVAnimationEx__7ONEFILEFUiPc(
		    *(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), s01MoveIsekiAnimationName),
		    lbl_802FF5A0);
		if (s01MoveIsekiEffectModels[i] != NULL) {
			fn_8014FFBC(s01MoveIsekiEffectModels[i], fn_3_861C4, &s01MoveIsekiEffectAtomics[i]);
			fn_8014FFBC(s01MoveIsekiEffectModels[i], fn_3_861CC, &lbl_3_bss_15EC[i]);
			lbl_3_data_ADFC[i] = *(u32*)(s01MoveIsekiEffectAtomics[i] + 0x48);
			if (s01MoveIsekiAnimations[i] != NULL) {
				s01MoveIsekiEffects[i].animation = s01MoveIsekiAnimations[i];
				AtomicSetCustomFXTexture__FP8RpAtomicPv(
				    s01MoveIsekiEffectAtomics[i], &s01MoveIsekiEffects[i]);
			}
		}
	}
}
