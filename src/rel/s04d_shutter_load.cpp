#include "types.h"

// The shutter's Load hook (s04dShutterLoad here): when the module's texture
// dictionary is there, it is made current, the module's model archive is read
// and each model loaded by its name with the model extension; fn_800B8BEC is
// called on each loaded model whose flags have bit 0 set.

// one of the family's models: its flags, the model once loaded and its file
// name
typedef struct S04dShutterModel {
	u8 flags; // 0x00
	u8 unk01[0x7];
	void* model;      // 0x08
	const char* name; // 0x0C
} S04dShutterModel;   // 0x10

extern "C" u8 s04dShutterModels[];
extern "C" char s04dShutterNameFormat[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_800B8BEC(void* clump, s32 flag);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s04dShutterLoad(void)
{
	char name[0x20];
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S04dShutterModel* model = (S04dShutterModel*)s04dShutterModels;

	for (u8 i = 0; i < 2; i++) {
		sprintf(name, s04dShutterNameFormat, model->name);
		model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		if (model->model != NULL && (model->flags & 1)) {
			fn_800B8BEC(model->model, 0);
		}
		model++;
	}
}
