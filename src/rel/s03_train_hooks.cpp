#include "types.h"

// The train's Unload and Load hooks (s03TrainUnload and s03TrainLoad here):
// each of its models and their animations are released, and the module's
// animation pointer cleared; when the module's texture dictionary is there, it
// is made current, the module's model archive is read and each model loaded by
// its name with the model extension. The kind-2 models also get their
// animation (the name with the animation extension), its length kept with it
// and the animation kept as the module's.

// one of the family's models: its kind, the model and its animation once
// loaded, the animation's length and its file name
typedef struct S03TrainModel {
	s8 kind; // 0x00
	u8 unk01[0x3];
	void* model;      // 0x04
	void* animation;  // 0x08
	f32 duration;     // 0x0C
	const char* name; // 0x10
} S03TrainModel;      // 0x14

extern "C" u8 s03TrainModels[];
extern "C" void* s03TrainAnimation;
extern "C" char s03TrainNameFormat[];
extern "C" char s03TrainAnimationFormat[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8020C2D8(void* animation);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s03TrainUnload(void)
{
	S03TrainModel* model = (S03TrainModel*)s03TrainModels;

	for (u8 i = 0; i < 2; i++) {
		if (model->animation != NULL) {
			fn_8020C2D8(model->animation);
			model->animation = NULL;
		}
		if (model->model != NULL) {
			fn_80150958(model->model);
			model->model = NULL;
		}
		model++;
	}
	s03TrainAnimation = NULL;
}

extern "C" void s03TrainLoad(void)
{
	char name[0x20];
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S03TrainModel* model = (S03TrainModel*)s03TrainModels;

	for (u8 i = 0; i < 2; i++) {
		sprintf(name, s03TrainNameFormat, model->name);
		model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		if (model->kind == 2) {
			sprintf(name, s03TrainAnimationFormat, model->name);
			void* animation = LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
			if (animation != NULL) {
				model->duration   = *(f32*)((u8*)animation + 0xC);
				model->animation  = animation;
				s03TrainAnimation = animation;
			}
		}
		model++;
	}
}
