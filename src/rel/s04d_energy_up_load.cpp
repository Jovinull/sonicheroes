#include "types.h"

// The energy booster's Load hook (s04dEnergyUpLoad here): when the module's
// texture dictionary is there, it is made current, the module's model archive
// is read and each model loaded by its name with the model extension;
// fn_800B8BEC is called on each loaded model whose flags have bit 0 set, and
// fn_800BDF30 on those with bit 2 set. The family's material animation is set
// up first, and each loaded model's atomics get the family's callback; the
// dictionary also goes through fn_800BE274 before the models and fn_800BE1F4
// after them.

// one of the family's models: its flags, the model once loaded and its file
// name
typedef struct S04dEnergyUpModel {
	u8 unk00;
	u8 flags; // 0x01
	u8 unk02[0x6];
	void* model; // 0x08
	u8 unk0C[0x8];
	const char* name; // 0x14
} S04dEnergyUpModel;  // 0x18

// the family's material animation (fn_8015C6F8 and its neighbours set it up)
typedef struct S04dEnergyUpMatAnim {
	u8 unk00[0x18];
} S04dEnergyUpMatAnim;

extern "C" u8 s04dEnergyUpModels[];
extern "C" S04dEnergyUpMatAnim s04dEnergyUpMatAnim;
extern "C" char s04dEnergyUpNameFormat[];
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_800B8BEC(void* clump, s32 flag);
extern "C" void fn_800BDF30(void* clump);
extern "C" void fn_800BE1F4(void* resource);
extern "C" void fn_800BE274(void* resource);
extern "C" void fn_8015C728(S04dEnergyUpMatAnim* anim);
extern "C" void fn_8015C6F8(S04dEnergyUpMatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C704(S04dEnergyUpMatAnim* anim, s32 a, s32 b);
extern "C" void fn_8015C710(S04dEnergyUpMatAnim* anim, s32 a, s32 b, s32 c);
extern "C" void fn_8015C720(S04dEnergyUpMatAnim* anim, s32 a);
extern "C" void fn_8014FFBC(void* clump, void* (*callback)(void*), void* data);
extern "C" void* fn_4_9617C(void* atomic);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s04dEnergyUpLoad(void)
{
	char name[0x20];
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	fn_8015C728(&s04dEnergyUpMatAnim);
	fn_8015C6F8(&s04dEnergyUpMatAnim, 3, 4);
	fn_8015C704(&s04dEnergyUpMatAnim, 1, 0);
	fn_8015C710(&s04dEnergyUpMatAnim, 1, 3, 6);
	fn_8015C720(&s04dEnergyUpMatAnim, 3);
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	fn_800BE274(*(void**)(lbl_8042C1D0 + 0x8C18));
	S04dEnergyUpModel* model = (S04dEnergyUpModel*)s04dEnergyUpModels;

	for (u8 i = 0; i < 2; i++) {
		sprintf(name, s04dEnergyUpNameFormat, model->name);
		model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		if (model->model != NULL && (model->flags & 1)) {
			fn_800B8BEC(model->model, 0);
		}
		if (model->model != NULL && (model->flags & 4)) {
			fn_800BDF30(model->model);
		}
		if (model->model != NULL) {
			fn_8014FFBC(model->model, fn_4_9617C, NULL);
		}
		model++;
	}
	fn_800BE1F4(*(void**)(lbl_8042C1D0 + 0x8C18));
}
