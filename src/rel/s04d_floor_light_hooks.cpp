#include "types.h"
#include "game/effect/eff_bomb.h"

// The floor light's Unload and Load hooks (s04dFloorLightUnload and
// s04dFloorLightLoad here): each of its models is released and the family's
// light setter object deleted; when the module's texture dictionary is there,
// it is made current, the module's model archive is read and each model loaded
// by its name with the model extension, the atomics of those whose flags have
// bit 0 set going through the family's callback. Then the light setter (a
// TObject with s04SetLightVtable) is made, its constructor written out here.

// one of the family's models: its flags, the model once loaded and its file
// name
typedef struct S04dFloorLightModel {
	u8 flags; // 0x00
	u8 unk01[0x3];
	void* model;       // 0x04
	const char* name;  // 0x08
} S04dFloorLightModel; // 0xC

extern "C" u8 s04dFloorLightModels[];
extern "C" char s04dFloorLightNameFormat[];
extern "C" TObject* s04dFloorLightSetter;
extern "C" u8 s04SetLightVtable[];
extern "C" s16 s04dFloorLightSetterParam;
extern "C" void* lbl_8042C110;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_4_A4348(void* atomic);
extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* __ct__7TObjectFP7TObject(void* object, void* parent);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s04dFloorLightUnload(void)
{
	S04dFloorLightModel* model = (S04dFloorLightModel*)s04dFloorLightModels;

	for (u8 i = 0; i < 5; i++) {
		if (model->model != NULL) {
			fn_80150958(model->model);
			model->model = NULL;
		}
		model++;
	}
	if (s04dFloorLightSetter != NULL) {
		delete s04dFloorLightSetter;
		s04dFloorLightSetter = NULL;
	}
}

extern "C" void s04dFloorLightLoad(void)
{
	char name[0x20];
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S04dFloorLightModel* model = (S04dFloorLightModel*)s04dFloorLightModels;

	for (u8 i = 0; i < 5; i++) {
		sprintf(name, s04dFloorLightNameFormat, model->name);
		model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		if (model->model != NULL && (model->flags & 1)) {
			fn_8014FFBC(model->model, fn_4_A4348, (void*)1);
		}
		model++;
	}
	u8* light = (u8*)Malloc__9THeapCtrlFUi(lbl_8042C148, 0x30);
	if (light != NULL) {
		__ct__7TObjectFP7TObject(light, lbl_8042C110);
		*(u8**)(light + 0x18) = s04SetLightVtable;
		*(u32*)(light + 0x2C) = 0;
		*(u8*)(light + 0x29)  = 4;
		*(s16*)(light + 0x2A) = s04dFloorLightSetterParam;
		*(u8*)(light + 0x28)  = 0;
	}
	s04dFloorLightSetter = (TObject*)light;
}
