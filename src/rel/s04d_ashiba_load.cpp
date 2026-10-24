#include "types.h"

// The scaffold's Load hook (s04dAshibaLoad here): when the module's texture
// dictionary is there, it is made current, the module's model archive is read
// and each model loaded by its name with the model extension; fn_800B8BEC is
// called on each loaded model whose flags have bit 0 set. The family's material
// animation is set up first, and each loaded model's atomics get the family's
// callback.

// one of the family's models: its flags, the model once loaded and its file
// name
typedef struct S04dAshibaModel {
	u8 flags; // 0x00
	u8 unk01[0x7];
	void* model;      // 0x08
	const char* name; // 0x0C
} S04dAshibaModel;    // 0x10

// the family's material animation (fn_8015C6F8 and its neighbours set it up)
typedef struct S04dAshibaMatAnim {
	u8 unk00[0x18];
} S04dAshibaMatAnim;

extern "C" u8 s04dAshibaModels[];
extern "C" S04dAshibaMatAnim s04dAshibaMatAnim;
extern "C" char s04dAshibaNameFormat[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_800B8BEC(void* clump, s32 flag);
extern "C" void fn_8015C728(S04dAshibaMatAnim* anim);
extern "C" void fn_8015C6F8(S04dAshibaMatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C704(S04dAshibaMatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C710(S04dAshibaMatAnim* anim, s32 a, s32 b, s32 c);
extern "C" void fn_8015C720(S04dAshibaMatAnim* anim, s32 a);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_4_97E38(void* atomic);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s04dAshibaLoad(void)
{
	char name[0x20];
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	fn_8015C728(&s04dAshibaMatAnim);
	fn_8015C6F8(&s04dAshibaMatAnim, 3, 4);
	fn_8015C704(&s04dAshibaMatAnim, 1, 0);
	fn_8015C710(&s04dAshibaMatAnim, 1, 3, 6);
	fn_8015C720(&s04dAshibaMatAnim, 3);
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S04dAshibaModel* model = (S04dAshibaModel*)s04dAshibaModels;

	for (u8 i = 0; i < 4; i++) {
		sprintf(name, s04dAshibaNameFormat, model->name);
		model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		if (model->model != NULL && (model->flags & 1)) {
			fn_800B8BEC(model->model, 0);
		}
		if (model->model != NULL) {
			fn_8014FFBC(model->model, fn_4_97E38, NULL);
		}
		model++;
	}
}
