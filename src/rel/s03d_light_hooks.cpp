#include "types.h"
#include "game/effect/eff_bomb.h"

// The light's Unload and Load hooks (s03dLightUnload and s03dLightLoad here):
// each of its models is released and the family's light setter object
// deleted; when the module's texture dictionary is there, it is made current,
// the module's model archive is read and each model loaded by its name with
// the model extension, its atomics going through the family's callback. Then
// the light setter (a TObject with s03SetLightVtable) is made, its constructor
// written out here.

// one of the family's models: the model once loaded and its file name
typedef struct S03dLightModel {
	u8 unk00[0x4];
	void* model;      // 0x04
	const char* name; // 0x08
} S03dLightModel;     // 0xC

extern "C" u8 s03dLightModels[];
extern "C" char s03dLightNameFormat[];
extern "C" TObject* s03dLightSetter;
extern "C" u8 s03SetLightVtable[];
extern "C" void* lbl_8042C110;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_4_7D568(void* atomic);
extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* __ct__7TObjectFP7TObject(void* object, void* parent);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s03dLightUnload(void)
{
	S03dLightModel* model = (S03dLightModel*)s03dLightModels;

	for (u8 i = 0; i < 8; i++) {
		if (model->model != NULL) {
			fn_80150958(model->model);
			model->model = NULL;
		}
		model++;
	}
	if (s03dLightSetter != NULL) {
		delete s03dLightSetter;
		s03dLightSetter = NULL;
	}
}

extern "C" void s03dLightLoad(void)
{
	char name[0x20];
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S03dLightModel* model = (S03dLightModel*)s03dLightModels;

	for (u8 i = 0; i < 8; i++) {
		sprintf(name, s03dLightNameFormat, model->name);
		model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		if (model->model != NULL) {
			fn_8014FFBC(model->model, fn_4_7D568, (void*)1);
		}
		model++;
	}
	u8* light = (u8*)Malloc__9THeapCtrlFUi(lbl_8042C148, 0x30);
	if (light != NULL) {
		__ct__7TObjectFP7TObject(light, lbl_8042C110);
		*(u8**)(light + 0x18) = s03SetLightVtable;
		*(u32*)(light + 0x2C) = 0;
		*(u8*)(light + 0x29)  = 4;
		*(s16*)(light + 0x2A) = 0x14;
		*(u8*)(light + 0x28)  = 0;
	}
	s03dLightSetter = (TObject*)light;
}
