#include "types.h"

// The energy pipe's Unload and Load hooks (s04ENERGYPipeUpUnload and
// s04ENERGYPipeUpLoad here): each of its 26 entries has its morph (type-1
// entries) and model released; when the module's texture dictionary is there,
// it is made current, the family's material animation is set up and the
// module's model archive is read. Each entry loads its morph (type 1, frame
// count kept) and its model by its name with the matching extension, the model
// through fn_800BDF30 when bit 2 of its flags is set and its atomics through
// the family's callback. The dictionary also goes through fn_800BE274 before
// the models and fn_800BE1F4 after them.

// one entry: its type and flags, the model and its morph once loaded, the
// morph's frame count and its file name
typedef struct S04ENERGYPipeUpModel {
	s8 type;  // 0x00
	u8 flags; // 0x01
	u8 unk02[0x2];
	void* model;        // 0x04
	void* animation;    // 0x08
	f32 duration;       // 0x0C
	const char* name;   // 0x10
} S04ENERGYPipeUpModel; // 0x14

// the family's material animation (fn_8015C6F8 and its neighbours set it up)
typedef struct S04ENERGYPipeUpMatAnim {
	u8 unk00[0x18];
} S04ENERGYPipeUpMatAnim;

extern "C" u8 s04ENERGYPipeUpModels[];
extern "C" S04ENERGYPipeUpMatAnim s04ENERGYPipeUpMatAnim;
extern "C" char s04ENERGYPipeUpMorphFormat[];
extern "C" char s04ENERGYPipeUpNameFormat[];
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
extern "C" void fn_8015C728(S04ENERGYPipeUpMatAnim* anim);
extern "C" void fn_8015C6F8(S04ENERGYPipeUpMatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C704(S04ENERGYPipeUpMatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C710(S04ENERGYPipeUpMatAnim* anim, s32 a, s32 b, s32 c);
extern "C" void fn_8015C720(S04ENERGYPipeUpMatAnim* anim, s32 a);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_4_98C04(void* atomic);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadDeltaMorphEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" f32 GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(void* anim, void* morph);

extern "C" void s04ENERGYPipeUpUnload(void)
{
	S04ENERGYPipeUpModel* model = (S04ENERGYPipeUpModel*)s04ENERGYPipeUpModels;

	for (u8 i = 0; i < 26; i++) {
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

extern "C" void s04ENERGYPipeUpLoad(void)
{
	char name[0x20];
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	fn_8015C728(&s04ENERGYPipeUpMatAnim);
	fn_8015C6F8(&s04ENERGYPipeUpMatAnim, 3, 4);
	fn_8015C704(&s04ENERGYPipeUpMatAnim, 1, 0);
	fn_8015C710(&s04ENERGYPipeUpMatAnim, 1, 3, 6);
	fn_8015C720(&s04ENERGYPipeUpMatAnim, 3);
	fn_800BE274(*(void**)(lbl_8042C1D0 + 0x8C18));
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S04ENERGYPipeUpModel* model = (S04ENERGYPipeUpModel*)s04ENERGYPipeUpModels;

	for (u8 i = 0; i < 26; i++) {
		if (model->type == 1) {
			sprintf(name, s04ENERGYPipeUpMorphFormat, model->name);
			void* morph = LoadDeltaMorphEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
			if (morph != NULL) {
				model->duration
				    = GetTotalFrame__10DAnimClassFP17RpDMorphAnimation(lbl_8042C340, morph);
				model->animation = morph;
			}
		}
		sprintf(name, s04ENERGYPipeUpNameFormat, model->name);
		model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		if (model->model != NULL && (model->flags & 4)) {
			fn_800BDF30(model->model);
		}
		if (model->model != NULL) {
			fn_8014FFBC(model->model, fn_4_98C04, NULL);
		}
		model++;
	}
	fn_800BE1F4(*(void**)(lbl_8042C1D0 + 0x8C18));
}
