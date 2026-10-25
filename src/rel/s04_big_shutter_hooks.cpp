#include "types.h"

// The big shutter's Unload and Load hooks (s04BigShutterUnload and
// s04BigShutterLoad here): each of its models' animation and model are
// released (the model through fn_800B8ADC first when bit 0 of its flags is
// set); when the module's texture dictionary is there, it is made current, the
// module's model archive is read and each model loaded by its name with the
// model extension (through fn_800B8BEC when bit 0 of its flags is set).
// Type-2 models also get their animation, with its length kept.

// one of the family's models: its type and flags, the model and its animation
// once loaded, the animation's length and its file name
typedef struct S04BigShutterModel {
	s8 type;  // 0x00
	u8 flags; // 0x01
	u8 unk02[0x6];
	void* model;      // 0x08
	void* animation;  // 0x0C
	f32 duration;     // 0x10
	const char* name; // 0x14
} S04BigShutterModel; // 0x18

extern "C" u8 s04BigShutterModels[];
extern "C" char s04BigShutterNameFormat[];
extern "C" char s04BigShutterAnimationFormat[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_800B8ADC(void* clump);
extern "C" void fn_800B8BEC(void* clump, s32 flag);
extern "C" void fn_8020C2D8(void* animation);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s04BigShutterUnload(void)
{
	S04BigShutterModel* model = (S04BigShutterModel*)s04BigShutterModels;

	for (u8 i = 0; i < 3; i++) {
		if (model->animation != NULL) {
			fn_8020C2D8(model->animation);
			model->animation = NULL;
		}
		if (model->model != NULL) {
			if (model->flags & 1) {
				fn_800B8ADC(model->model);
			}
			fn_80150958(model->model);
			model->model = NULL;
		}
		model++;
	}
}

extern "C" void s04BigShutterLoad(void)
{
	char name[0x20];
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S04BigShutterModel* model = (S04BigShutterModel*)s04BigShutterModels;

	for (u8 i = 0; i < 3; i++) {
		sprintf(name, s04BigShutterNameFormat, model->name);
		model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		if (model->model != NULL && (model->flags & 1)) {
			fn_800B8BEC(model->model, 0);
		}
		if (model->type == 2) {
			sprintf(name, s04BigShutterAnimationFormat, model->name);
			void* animation = LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
			if (animation != NULL) {
				model->duration  = *(f32*)((u8*)animation + 0xC);
				model->animation = animation;
			}
		}
		model++;
	}
}
