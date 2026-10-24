#include "types.h"

// The door's Unload and Load hooks (s03DoorUnload and s03DoorLoad here): each
// of its models' animation (a morph for type-1 doors, a hierarchy animation
// for type-2 ones) and model are released; when the module's texture
// dictionary is there, it is made current, the module's model archive is read
// and each door's animation (with its length kept) and model loaded by its
// name with the matching extension, the model through fn_800BDF30 when bit 2
// of its flags is set. The dictionary also goes through fn_800BE274 before the
// models and fn_800BE1F4 after them.

// one of the family's models: its type and flags, the model and its animation
// once loaded, the animation's length and its file name
typedef struct S03DoorModel {
	s8 type;  // 0x00
	u8 flags; // 0x01
	u8 unk02[0x2];
	void* model;      // 0x04
	void* animation;  // 0x08
	f32 duration;     // 0x0C
	const char* name; // 0x10
} S03DoorModel;       // 0x14

extern "C" u8 s03DoorModels[];
extern "C" char s03DoorMorphFormat[];
extern "C" char s03DoorAnimationFormat[];
extern "C" char s03DoorNameFormat[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_8042C340[];
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8013BD74(void* morph);
extern "C" void fn_8020C2D8(void* animation);
extern "C" void fn_800BDF30(void* clump);
extern "C" void fn_800BE1F4(void* resource);
extern "C" void fn_800BE274(void* resource);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadDeltaMorphEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" f32 GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(void* anim, void* morph);

extern "C" void s03DoorUnload(void)
{
	S03DoorModel* model = (S03DoorModel*)s03DoorModels;

	for (u8 i = 0; i < 3; i++) {
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

extern "C" void s03DoorLoad(void)
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
	S03DoorModel* model = (S03DoorModel*)s03DoorModels;

	for (u8 i = 0; i < 3; i++) {
		if (model->type == 1) {
			sprintf(name, s03DoorMorphFormat, model->name);
			void* morph = LoadDeltaMorphEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
			if (morph != NULL) {
				model->duration
				    = GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(lbl_8042C340, morph);
				model->animation = morph;
			}
		} else if (model->type == 2) {
			sprintf(name, s03DoorAnimationFormat, model->name);
			void* animation = LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
			if (animation != NULL) {
				model->duration  = *(f32*)((u8*)animation + 0xC);
				model->animation = animation;
			}
		}
		sprintf(name, s03DoorNameFormat, model->name);
		model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		if (model->model != NULL && (model->flags & 4)) {
			fn_800BDF30(model->model);
		}
		model++;
	}
	fn_800BE1F4(*(void**)(lbl_8042C1D0 + 0x8C18));
}
