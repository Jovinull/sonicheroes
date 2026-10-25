#include "types.h"

// The big egg capsule's Unload and Load hooks (s04EggCapBigUnload and
// s04EggCapBigLoad here): each of its models and texture effects is released,
// then the effect's UV animation; when the module's texture dictionary is
// there, it is made current, the module's model archive is read, the UV
// animation is loaded (its frame count kept) and each model loaded by its
// name with the model extension. Every type-1 model gets a texture effect of
// its own from the engine's allocator, holding the UV animation and set on the
// model's first atomic.

// one of the family's models: the model once loaded, its type, its texture
// effect and its file name
typedef struct S04EggCapBigModel {
	void* model; // 0x00
	s32 type;    // 0x04
	u8 unk08[0x4];
	void** effect;    // 0x0C
	const char* name; // 0x10
} S04EggCapBigModel;  // 0x14

extern "C" u8 s04EggCapBigModels[];
extern "C" char s04EggCapBigEffectName[];
extern "C" char s04EggCapBigNameFormat[];
extern "C" void* s04EggCapBigEffectAnimation;
extern "C" f32 s04EggCapBigEffectFrames;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8* lbl_8042C9A4;
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
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

extern "C" void s04EggCapBigUnload(void)
{
	S04EggCapBigModel* model = (S04EggCapBigModel*)s04EggCapBigModels;

	for (u8 i = 0; i < 6; i++) {
		if (model->model != NULL) {
			fn_80150958(model->model);
			model->model = NULL;
		}
		if (model->effect != NULL) {
			(*(void (**)(void*))(lbl_8042C9A4 + 0x138))(model->effect);
			model->effect = NULL;
		}
		model++;
	}
	if (s04EggCapBigEffectAnimation != NULL) {
		fn_8011B7CC(s04EggCapBigEffectAnimation);
		s04EggCapBigEffectAnimation = NULL;
	}
}

extern "C" void s04EggCapBigLoad(void)
{
	char name[0x20];
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	void* animation = s04EggCapBigEffectAnimation
	    = LoadUVAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	        CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), s04EggCapBigEffectName),
	        lbl_802FF5A0);
	if (animation != NULL) {
		s04EggCapBigEffectFrames
		    = objRpUVAnimAnimationGetTotalFrame__FP17RpUVAnimAnimation(animation);
	}
	S04EggCapBigModel* model = (S04EggCapBigModel*)s04EggCapBigModels;

	for (u8 i = 0; i < 6; i++) {
		sprintf(name, s04EggCapBigNameFormat, model->name);
		model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		if (s04EggCapBigEffectAnimation != NULL && model->model != NULL && model->type == 1) {
			void** effect = (void**)(*(void* (**)(u32))(lbl_8042C9A4 + 0x134))(0x44);
			if (effect != NULL) {
				model->effect  = effect;
				*model->effect = s04EggCapBigEffectAnimation;
				AtomicSetCustomFXTexture__FP8RpAtomicPv(
				    objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(model->model, NULL), model->effect);
			}
		}
		model++;
	}
}
