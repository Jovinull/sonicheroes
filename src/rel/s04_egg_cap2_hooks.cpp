#include "types.h"

// The egg capsule 2's Unload and Load hooks (s04EggCap2Unload and
// s04EggCap2Load here): its models are released, with fn_800B8ADC called first
// on those of kind 5; when the module's texture dictionary is there, it is
// made current, the module's model archive is read and each model loaded by
// its name with the model extension, with fn_800B8BEC called on those of kind
// 5.

// one of the family's models: the model once loaded, its kind and its file
// name
typedef struct S04EggCap2Model {
	void* model;      // 0x00
	s32 kind;         // 0x04
	const char* name; // 0x08
} S04EggCap2Model;    // 0xC

extern "C" u8 s04EggCap2Models[];
extern "C" char s04EggCap2NameFormat[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_800B8ADC(void* clump);
extern "C" void fn_800B8BEC(void* clump, s32 flag);
extern "C" void fn_801A4C84(void* resource);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s04EggCap2Unload(void)
{
	S04EggCap2Model* model = (S04EggCap2Model*)s04EggCap2Models;

	for (u8 i = 0; i < 9; i++) {
		if (model->model != NULL) {
			if (model->kind == 5) {
				fn_800B8ADC(model->model);
			}
			fn_80150958(model->model);
			model->model = NULL;
		}
		model++;
	}
}

extern "C" void s04EggCap2Load(void)
{
	char name[0x20];
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S04EggCap2Model* model = (S04EggCap2Model*)s04EggCap2Models;

	for (u8 i = 0; i < 9; i++) {
		sprintf(name, s04EggCap2NameFormat, model->name);
		model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		if (model->model != NULL && model->kind == 5) {
			fn_800B8BEC(model->model, 0);
		}
		model++;
	}
}
