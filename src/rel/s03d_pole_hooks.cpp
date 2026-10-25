#include "types.h"

// The pole's Unload and Load hooks (s03dPoleUnload and s03dPoleLoad here):
// each of its models' animation (a morph for type-1 entries, a hierarchy
// animation for type-2 ones) and model are released; when the module's
// texture dictionary is there, it is made current and the module's model
// archive is read. Type-1 entries only load their morph (its frame count
// kept); the others load their model by its name with the model extension,
// and type-2 ones also their animation, with its length kept. The dictionary
// also goes through fn_800BE274 before the models and fn_800BE1F4 after them.

// one of the family's models: its type, the model and its animation
// once loaded, the animation's length and its file name
typedef struct S03dPoleModel {
	s8 type; // 0x00
	u8 unk01[0x7];
	void* model;      // 0x08
	void* animation;  // 0x0C
	f32 duration;     // 0x10
	const char* name; // 0x14
} S03dPoleModel;      // 0x18

extern "C" u8 s03dPoleModels[];
extern "C" char s03dPoleMorphFormat[];
extern "C" char s03dPoleAnimationFormat[];
extern "C" char s03dPoleNameFormat[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_8042C340[];
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8013BD74(void* morph);
extern "C" void fn_8020C2D8(void* animation);
extern "C" void fn_800BE1F4(void* resource);
extern "C" void fn_800BE274(void* resource);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadDeltaMorphEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" f32 GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(void* anim, void* morph);

extern "C" void s03dPoleUnload(void)
{
	S03dPoleModel* model = (S03dPoleModel*)s03dPoleModels;

	for (u8 i = 0; i < 2; i++) {
		if (model->animation != NULL) {
			if (model->type == 1) {
				fn_8013BD74(model->animation);
			}
			if (model->type == 2) {
				fn_8020C2D8(model->animation);
			}
			model->animation = NULL;
		}
		if (model->model != NULL) {
			fn_80150958(model->model);
			model->model = NULL;
		}
		model++;
	}
}

extern "C" void s03dPoleLoad(void)
{
	char name[0x20];
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	fn_800BE274(*(void**)(lbl_8042C1D0 + 0x8C18));
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S03dPoleModel* model = (S03dPoleModel*)s03dPoleModels;

	for (u8 i = 0; i < 2; i++) {
		if (model->type == 1) {
			sprintf(name, s03dPoleMorphFormat, model->name);
			void* morph = LoadDeltaMorphEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
			if (morph != NULL) {
				model->duration
				    = GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(lbl_8042C340, morph);
				model->animation = morph;
			}
		} else {
			sprintf(name, s03dPoleNameFormat, model->name);
			model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
			if (model->type == 2) {
				sprintf(name, s03dPoleAnimationFormat, model->name);
				void* animation = LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
				    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
				if (animation != NULL) {
					model->duration  = *(f32*)((u8*)animation + 0xC);
					model->animation = animation;
				}
			}
		}
		model++;
	}
	fn_800BE1F4(*(void**)(lbl_8042C1D0 + 0x8C18));
}
