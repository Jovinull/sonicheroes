#include "types.h"

// The air car's Unload and Load hooks (s03AircarUnload and s03AircarLoad
// here): each of its models is released; the stage the cars are for is picked
// from the game mode (two modes use stage 17 and stage 4 with their own name
// prefix, the others the current stage and its prefix), the loading range and
// the cars' route parameters are set for it, then, when the module's texture
// dictionary is there, it is made current, the module's model archive is read
// and the models in range loaded by the prefix and their names.

// one of the cars' models: the model once loaded and its file name
typedef struct S03AircarModel {
	u8 unk00[0x8];
	void* model;      // 0x08
	const char* name; // 0x0C
} S03AircarModel;     // 0x10

// the game state (only the mode is read here)
typedef struct S03AircarGameState {
	u8 unk00[0x2C];
	s32 mode; // 0x2C
} S03AircarGameState;

extern "C" S03AircarGameState lbl_8029C310;
extern "C" u8 s03AircarModels[];
extern "C" char* lbl_4_data_11C5C[];
extern "C" char* lbl_4_data_B500[];
extern "C" s32 s03AircarStage;
extern "C" u8 lbl_4_bss_10E8;
extern "C" s32 s03AircarFirstModel;
extern "C" u8 lbl_4_data_777F;
extern "C" u8 lbl_4_data_7780;
extern "C" u8 lbl_4_data_7781;
extern "C" s32 lbl_4_data_7784;
extern "C" char s03AircarNameFormat[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" char* fn_800194C4(S03AircarGameState* state);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s03AircarUnload(void)
{
	S03AircarModel* model = (S03AircarModel*)s03AircarModels;

	for (u8 i = 0; i < 0x27; i++) {
		if (model->model != NULL) {
			fn_80150958(model->model);
			model->model = NULL;
		}
		model++;
	}
}

extern "C" void s03AircarLoad(void)
{
	char name[0x20];
	char* prefix;
	s32 mode = lbl_8029C310.mode;

	if (mode == 0x28) {
		s03AircarStage = 0x11;
		prefix         = lbl_4_data_11C5C[0];
	} else if (mode == 0x26) {
		s03AircarStage = 4;
		prefix         = lbl_4_data_B500[0];
	} else {
		s03AircarStage = mode;
		prefix         = fn_800194C4(&lbl_8029C310);
	}
	s32 stage      = s03AircarStage;
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	lbl_4_data_777F     = 3;
	lbl_4_bss_10E8      = 0;
	lbl_4_data_7780     = 0x27;
	lbl_4_data_7781     = 0xD;
	s03AircarFirstModel = 0;
	lbl_4_data_7784     = 7;
	if (stage == 0x11) {
		s03AircarFirstModel = 0xD;
	} else if (stage == 5) {
		lbl_4_data_777F = 2;
		lbl_4_data_7781 = 6;
		lbl_4_data_7784 = 5;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S03AircarModel* model = (S03AircarModel*)s03AircarModels;

	for (u8 i = 0; i < 0x27; i++) {
		if (i < s03AircarFirstModel) {
			model++;
			continue;
		}
		if (stage == 5 && i > 0x12) {
			return;
		}
		if (stage == 5 && i % 13 >= 6) {
			model++;
			continue;
		}
		sprintf(name, s03AircarNameFormat, prefix, model->name);
		model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		model++;
	}
}
