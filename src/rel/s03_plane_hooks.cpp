#include "types.h"

// The plane's Unload and Load hooks (s03PlaneUnload and s03PlaneLoad here): its
// animation and its model are released; when the module's texture dictionary
// is there, it is made current, the module's model archive is read and the
// model and its animation loaded by the family's name with their extensions,
// the animation's length being kept with it.

// the family's model, its animation and the animation's length, and the
// family's file name
typedef struct S03PlaneModel {
	void* model;      // 0x00
	void* animation;  // 0x04
	f32 duration;     // 0x08
	const char* name; // 0x0C
} S03PlaneModel;

extern "C" S03PlaneModel s03PlaneModel;
extern "C" char s03PlaneNameFormat[];
extern "C" char s03PlaneAnimationFormat[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_8020C2D8(void* animation);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s03PlaneUnload(void)
{
	S03PlaneModel* model = &s03PlaneModel;

	if (model->animation != NULL) {
		fn_8020C2D8(model->animation);
		model->animation = NULL;
	}
	if (model->model != NULL) {
		fn_80150958(model->model);
		model->model = NULL;
	}
}

extern "C" void s03PlaneLoad(void)
{
	char name[0x20];
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S03PlaneModel* model = &s03PlaneModel;

	sprintf(name, s03PlaneNameFormat, model->name);
	s03PlaneModel.model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
	sprintf(name, s03PlaneAnimationFormat, model->name);
	void* animation = LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
	    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
	if (animation != NULL) {
		model->duration  = *(f32*)((u8*)animation + 0xC);
		model->animation = animation;
	}
}
