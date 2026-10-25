#include "types.h"

// The egg capsule elevator's Unload and Load hooks (s04EggCapElevUnload and
// s04EggCapElevLoad here): each of its models is released (through
// fn_800B8ADC first for kind-5 models), and the effect's UV animation with the
// first one; when the module's texture dictionary is there, it is made
// current, the module's model archive is read, the effect's UV animation is
// loaded and each model loaded by its name with the model extension (kind-5
// models through fn_800B8BEC). The UV animation is set as the custom texture
// effect on the first atomic of the type-1 models.

// one of the family's models: the model once loaded, its type and kind, and
// its file name
typedef struct S04EggCapElevModel {
	void* model;      // 0x00
	s32 type;         // 0x04
	s32 kind;         // 0x08
	const char* name; // 0x0C
} S04EggCapElevModel; // 0x10

// the custom texture effect set on the type-1 models (its UV animation first)
typedef struct S04EggCapElevEffect {
	void* animation; // 0x00
	u8 unk04[0x40];
} S04EggCapElevEffect;

extern "C" u8 s04EggCapElevModels[];
extern "C" char s04EggCapElevEffectName[];
extern "C" char s04EggCapElevNameFormat[];
extern "C" void* s04EggCapElevEffectAnimation;
extern "C" S04EggCapElevEffect s04EggCapElevEffect;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_800B8ADC(void* clump);
extern "C" void fn_800B8BEC(void* clump, s32 flag);
extern "C" void fn_8011B7CC(void* animation);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadUVAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(void* clump, void* atomic);
extern "C" void AtomicSetCustomFXTexture__FP8RpAtomicPv(void* atomic, void* effect);

extern "C" void s04EggCapElevUnload(void)
{
	S04EggCapElevModel* model = (S04EggCapElevModel*)s04EggCapElevModels;

	for (u8 i = 0; i < 4; i++) {
		if (model->model != NULL) {
			if (model->kind == 5) {
				fn_800B8ADC(model->model);
			}
			fn_80150958(model->model);
			model->model = NULL;
		}
		if (s04EggCapElevEffectAnimation != NULL) {
			fn_8011B7CC(s04EggCapElevEffectAnimation);
			s04EggCapElevEffectAnimation = NULL;
		}
		model++;
	}
}

extern "C" void s04EggCapElevLoad(void)
{
	char name[0x20];
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	s04EggCapElevEffectAnimation = LoadUVAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), s04EggCapElevEffectName),
	    lbl_802FF5A0);
	S04EggCapElevModel* model    = (S04EggCapElevModel*)s04EggCapElevModels;

	for (u8 i = 0; i < 4; i++) {
		sprintf(name, s04EggCapElevNameFormat, model->name);
		model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		if (model->model != NULL && model->kind == 5) {
			fn_800B8BEC(model->model, 0);
		}
		if (s04EggCapElevEffectAnimation != NULL && model->model != NULL && model->type == 1) {
			s04EggCapElevEffect.animation = s04EggCapElevEffectAnimation;
			AtomicSetCustomFXTexture__FP8RpAtomicPv(
			    objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(model->model, NULL),
			    &s04EggCapElevEffect);
		}
		model++;
	}
}
