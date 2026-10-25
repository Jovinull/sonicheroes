#include "types.h"

// The sign board's Unload and Load hooks (s03SignBoardUnload and
// s03SignBoardLoad here): each of its models (through fn_800B8ADC first for
// kind-5 boards) and UV animations are released; when the module's texture
// dictionary is there, it is made current, the module's model archive is read
// and each model loaded by its name with the model extension (kind-5 boards
// through fn_800B8BEC). Type-3 boards also get their UV animation, set on the
// model's first atomic as its custom texture effect.

// one of the family's models: its type and kind, the model and its UV
// animation once loaded, and its file name
typedef struct S03SignBoardModel {
	s8 type; // 0x00
	u8 unk01[0x3];
	u32 kind;        // 0x04
	void* model;     // 0x08
	void* animation; // 0x0C
	u8 unk10[0x4];
	const char* name; // 0x14
} S03SignBoardModel;  // 0x18

// the custom texture effect set on the model (its UV animation first)
typedef struct S03SignBoardEffect {
	void* animation; // 0x00
	u8 unk04[0x40];
} S03SignBoardEffect;

extern "C" u8 s03SignBoardModels[];
extern "C" char s03SignBoardNameFormat[];
extern "C" char s03SignBoardAnimationFormat[];
extern "C" S03SignBoardEffect s03SignBoardEffect;
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

extern "C" void s03SignBoardUnload(void)
{
	S03SignBoardModel* model = (S03SignBoardModel*)s03SignBoardModels;

	for (u8 i = 0; i < 3; i++) {
		if (model->model != NULL) {
			if (model->kind == 5) {
				fn_800B8ADC(model->model);
			}
			fn_80150958(model->model);
			model->model = NULL;
		}
		if (model->animation != NULL) {
			fn_8011B7CC(model->animation);
			model->animation = NULL;
		}
		model++;
	}
}

extern "C" void s03SignBoardLoad(void)
{
	char name[0x20];
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S03SignBoardModel* model = (S03SignBoardModel*)s03SignBoardModels;

	for (u8 i = 0; i < 3; i++) {
		sprintf(name, s03SignBoardNameFormat, model->name);
		model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		if (model->model != NULL && model->kind == 5) {
			fn_800B8BEC(model->model, 0);
		}
		if (model->type == 3) {
			sprintf(name, s03SignBoardAnimationFormat, model->name);
			model->animation = LoadUVAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
			if (model->animation != NULL) {
				s03SignBoardEffect.animation = model->animation;
				AtomicSetCustomFXTexture__FP8RpAtomicPv(
				    objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(model->model, NULL),
				    &s03SignBoardEffect);
			}
		}
		model++;
	}
}
