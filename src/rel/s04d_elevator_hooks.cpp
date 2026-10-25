#include "types.h"

// The elevator's Unload and Load hooks (s04dElevatorUnload and
// s04dElevatorLoad here): each of its models is released (through
// fn_800B8ADC first when bit 0 of its flags is set), then the effect's UV
// animation; when the module's texture dictionary is there, it is made
// current, the module's model archive is read, the effect's UV animation is
// loaded and each model loaded by its name with the model extension
// (through fn_800B8BEC when bit 0 of its flags is set). The UV animation is
// set on the fifth model's first atomic as its custom texture effect.

// one of the family's models: its flags, the model once loaded and its file
// name
typedef struct S04dElevatorModel {
	u8 flags; // 0x00
	u8 unk01[0x7];
	void* model;      // 0x08
	const char* name; // 0x0C
} S04dElevatorModel;  // 0x10

// the custom texture effect set on the effect model (its UV animation first)
typedef struct S04dElevatorEffect {
	void* animation; // 0x00
	u8 unk04[0x40];
} S04dElevatorEffect;

extern "C" u8 s04dElevatorModels[];
extern "C" char s04dElevatorEffectName[];
extern "C" char s04dElevatorNameFormat[];
extern "C" void* s04dElevatorEffectAnimation;
extern "C" S04dElevatorEffect s04dElevatorEffect;
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

extern "C" void s04dElevatorUnload(void)
{
	S04dElevatorModel* model = (S04dElevatorModel*)s04dElevatorModels;

	for (u8 i = 0; i < 5; i++) {
		if (model->model != NULL) {
			if (model->flags & 1) {
				fn_800B8ADC(model->model);
			}
			fn_80150958(model->model);
			model->model = NULL;
		}
		model++;
	}
	if (s04dElevatorEffectAnimation != NULL) {
		fn_8011B7CC(s04dElevatorEffectAnimation);
		s04dElevatorEffectAnimation = NULL;
	}
}

extern "C" void s04dElevatorLoad(void)
{
	char name[0x20];
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S04dElevatorModel* model = (S04dElevatorModel*)s04dElevatorModels;

	s04dElevatorEffectAnimation = LoadUVAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), s04dElevatorEffectName),
	    lbl_802FF5A0);
	for (u8 i = 0; i < 5; i++) {
		sprintf(name, s04dElevatorNameFormat, model->name);
		model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		if (model->model != NULL && (model->flags & 1)) {
			fn_800B8BEC(model->model, 0);
		}
		if (i == 4 && s04dElevatorEffectAnimation != NULL && model->model != NULL) {
			s04dElevatorEffect.animation = s04dElevatorEffectAnimation;
			AtomicSetCustomFXTexture__FP8RpAtomicPv(
			    objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(model->model, NULL), &s04dElevatorEffect);
		}
		model++;
	}
}
