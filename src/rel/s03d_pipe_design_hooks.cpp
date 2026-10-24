#include "types.h"

// The pipe design's Unload and Load hooks (s03dPipeDesignUnload and
// s03dPipeDesignLoad here): each of its models is released; when the module's
// texture dictionary is there, it is made current, the module's model archive
// is read and each model loaded by its name with the model extension,
// fn_800BDF30 being called on each one that loads. The dictionary also goes
// through fn_800BE274 before the models and fn_800BE1F4 after them.

// one of the family's models: the model once loaded and its file name
typedef struct S03dPipeDesignModel {
	u8 unk00[0x4];
	void* model;       // 0x04
	const char* name;  // 0x08
} S03dPipeDesignModel; // 0xC

extern "C" u8 s03dPipeDesignModels[];
extern "C" char s03dPipeDesignNameFormat[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_800BDF30(void* clump);
extern "C" void fn_800BE1F4(void* resource);
extern "C" void fn_800BE274(void* resource);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s03dPipeDesignUnload(void)
{
	S03dPipeDesignModel* model = (S03dPipeDesignModel*)s03dPipeDesignModels;

	for (u8 i = 0; i < 6; i++) {
		if (model->model != NULL) {
			fn_80150958(model->model);
			model->model = NULL;
		}
		model++;
	}
}

extern "C" void s03dPipeDesignLoad(void)
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
	S03dPipeDesignModel* model = (S03dPipeDesignModel*)s03dPipeDesignModels;

	for (u8 i = 0; i < 6; i++) {
		sprintf(name, s03dPipeDesignNameFormat, model->name);
		model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		if (model->model != NULL) {
			fn_800BDF30(model->model);
		}
		model++;
	}
	fn_800BE1F4(*(void**)(lbl_8042C1D0 + 0x8C18));
}
