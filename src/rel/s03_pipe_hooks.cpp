#include "types.h"

// The pipe's Unload and Load hooks (s03PipeUnload and s03PipeLoad here): each
// model of the current pipe set has its morph (type-1 entries) and model
// released; when the module's texture dictionary is there, it is made current
// and the pipe set is picked from the game mode (one set for modes 4 and 0x26,
// another for mode 5, with its model count and second table). The module's
// model archive is read, and each entry loads its morph (type 1, frame count
// kept) and its model by its name with the matching extension, the model
// through fn_800BDF30 when bit 2 of its flags is set. The dictionary also goes
// through fn_800BE274 before the models and fn_800BE1F4 after them.

// one entry of a pipe set: its type and flags, the model and its morph once
// loaded, the morph's frame count and its file name
typedef struct S03PipeModel {
	s8 type;  // 0x00
	u8 flags; // 0x01
	u8 unk02[0x2];
	void* model;      // 0x04
	void* animation;  // 0x08
	f32 duration;     // 0x0C
	const char* name; // 0x10
} S03PipeModel;       // 0x14

// the game state (only the mode is read here)
typedef struct S03PipeGameState {
	u8 unk00[0x2C];
	s32 mode; // 0x2C
} S03PipeGameState;

extern "C" S03PipeGameState lbl_8029C310;
extern "C" u8 lbl_4_bss_1388;
extern "C" s8 s03PipeCount;
extern "C" S03PipeModel* s03PipeModels;
extern "C" u8* lbl_4_bss_1390;
extern "C" S03PipeModel lbl_4_data_8CFC[];
extern "C" u8 lbl_4_data_8F40[];
extern "C" S03PipeModel lbl_4_data_92E0[];
extern "C" u8 lbl_4_data_9600[];
extern "C" char s03PipeMorphFormat[];
extern "C" char s03PipeNameFormat[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_8042C340[];
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8013BD74(void* morph);
extern "C" void fn_800BDF30(void* clump);
extern "C" void fn_800BE1F4(void* resource);
extern "C" void fn_800BE274(void* resource);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadDeltaMorphEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" f32 GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(void* anim, void* morph);

extern "C" void s03PipeUnload(void)
{
	S03PipeModel* model = s03PipeModels;

	for (u8 i = 0; i < s03PipeCount; i++) {
		if (model->animation != NULL) {
			if (model->type == 1) {
				fn_8013BD74(model->animation);
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

extern "C" void s03PipeLoad(void)
{
	char name[0x20];
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	s32 mode = lbl_8029C310.mode;
	if (mode == 4 || mode == 0x26) {
		lbl_4_bss_1388 = 2;
		s03PipeCount   = 0x1D;
		s03PipeModels  = lbl_4_data_8CFC;
		lbl_4_bss_1390 = lbl_4_data_8F40;
	} else if (mode == 5) {
		lbl_4_bss_1388 = 2;
		s03PipeCount   = 0x28;
		s03PipeModels  = lbl_4_data_92E0;
		lbl_4_bss_1390 = lbl_4_data_9600;
	}
	fn_800BE274(*(void**)(lbl_8042C1D0 + 0x8C18));
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S03PipeModel* model = s03PipeModels;

	for (u8 i = 0; i < s03PipeCount; i++) {
		if (model->type == 1) {
			sprintf(name, s03PipeMorphFormat, model->name);
			void* morph = LoadDeltaMorphEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
			if (morph != NULL) {
				model->duration
				    = GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(lbl_8042C340, morph);
				model->animation = morph;
			}
		}
		sprintf(name, s03PipeNameFormat, model->name);
		model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		if (model->model != NULL && (model->flags & 4)) {
			fn_800BDF30(model->model);
		}
		model++;
	}
	fn_800BE1F4(*(void**)(lbl_8042C1D0 + 0x8C18));
}
