#include "types.h"

// The crane's Unload and Load hooks (s04dCraneUnload and s04dCraneLoad here): its
// models are released; when the module's texture dictionary is there, it is
// made current, the module's model archive is read and each model loaded by
// its name with the model extension.

// one of the family's models: the model once loaded and its file name
typedef struct S04dCraneModel {
	u8 unk00[0x8];
	void* model; // 0x08
	u8 unk0C[0x8];
	const char* name; // 0x14
} S04dCraneModel;     // 0x18

extern "C" u8 s04dCraneModels[];
extern "C" char s04dCraneNameFormat[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_801A4C84(void* resource);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s04dCraneUnload(void)
{
	S04dCraneModel* model = (S04dCraneModel*)s04dCraneModels;

	for (u8 i = 0; i < 4; i++) {
		if (model->model != NULL) {
			fn_80150958(model->model);
			model->model = NULL;
		}
		model++;
	}
}

extern "C" void s04dCraneLoad(void)
{
	char name[0x20];
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S04dCraneModel* model = (S04dCraneModel*)s04dCraneModels;

	for (u8 i = 0; i < 4; i++) {
		sprintf(name, s04dCraneNameFormat, model->name);
		model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		model++;
	}
}
