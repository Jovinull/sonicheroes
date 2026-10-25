#include "types.h"
#include "game/effect/eff_bomb.h"

// The solar robot's Unload and Load hooks (s04SolarRoboUnload and
// s04SolarRoboLoad here): the family's object is deleted, the face material
// and the four face textures are forgotten, and each model's animation and
// the model are released; when the module's texture dictionary is there, it
// is made current, the module's model archive is read and each model loaded
// by its name with the model extension, type-2 models also getting their
// animation with its length kept. Then the four face textures ("m4_a1" to
// "m4_a4") are looked up in the dictionary, and the first model's material
// using "m4_a1" is kept.

// one of the family's models: its type, the model and its animation once
// loaded, the animation's length and its file name
typedef struct S04SolarRoboModel {
	s8 type; // 0x00
	u8 unk01[0x7];
	void* model;      // 0x08
	void* animation;  // 0x0C
	f32 duration;     // 0x10
	const char* name; // 0x14
} S04SolarRoboModel;  // 0x18

extern "C" S04SolarRoboModel s04SolarRoboModels[];
extern "C" void* s04SolarRoboFaceTextures[4];
extern "C" TObject* s04SolarRoboObject;
extern "C" void* s04SolarRoboFaceMaterial;
extern "C" char s04SolarRoboNameFormat[];
extern "C" char s04SolarRoboAnimationFormat[];
extern "C" char s04SolarRoboFaceTextureFormat[];
extern "C" char s04SolarRoboFaceTextureName[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_801A4C84(void* resource);
extern "C" void* fn_801A4BBC(void* dictionary, const char* name);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8020C2D8(void* animation);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* objRpClumpGetMaterialWithSpecificTexture__FP7RpClumpP10RpMaterialPc(
    void* clump, void* material, const char* texture);

extern "C" void s04SolarRoboUnload(void)
{
	S04SolarRoboModel* model = s04SolarRoboModels;

	if (s04SolarRoboObject != NULL) {
		delete s04SolarRoboObject;
		s04SolarRoboObject = NULL;
	}
	s04SolarRoboFaceMaterial    = NULL;
	s04SolarRoboFaceTextures[0] = NULL;
	s04SolarRoboFaceTextures[1] = NULL;
	s04SolarRoboFaceTextures[2] = NULL;
	s04SolarRoboFaceTextures[3] = NULL;
	for (u8 i = 0; i < 2; i++) {
		if (model->animation != NULL) {
			fn_8020C2D8(model->animation);
			model->animation = NULL;
		}
		if (model->model != NULL) {
			fn_80150958(model->model);
			model->model = NULL;
		}
		model++;
	}
}

extern "C" void s04SolarRoboLoad(void)
{
	char texture[0x10];
	char name[0x20];
	u8 i;
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S04SolarRoboModel* model = s04SolarRoboModels;

	for (i = 0; i < 2; i++) {
		sprintf(name, s04SolarRoboNameFormat, model->name);
		model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		if (model->type == 2) {
			sprintf(name, s04SolarRoboAnimationFormat, model->name);
			void* animation = LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
			if (animation != NULL) {
				model->duration  = *(f32*)((u8*)animation + 0xC);
				model->animation = animation;
			}
		}
		model++;
	}
	for (i = 0; i < 4; i++) {
		sprintf(texture, s04SolarRoboFaceTextureFormat, i + 1);
		s04SolarRoboFaceTextures[i] = fn_801A4BBC(*(void**)(lbl_8042C1D0 + 0x8C18), texture);
	}
	s04SolarRoboFaceMaterial = objRpClumpGetMaterialWithSpecificTexture__FP7RpClumpP10RpMaterialPc(
	    s04SolarRoboModels[0].model, NULL, s04SolarRoboFaceTextureName);
}
