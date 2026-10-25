#include "types.h"
#include "game/effect/eff_bomb.h"

// The energy bubble's Unload and Load hooks (s04EBubbleUnload and
// s04EBubbleLoad here): its model's animation and the model are released, and
// the family's manager object is deleted; when the module's texture dictionary
// is there, it is made current, the module's model archive is read and the
// model loaded by its name with the model extension (through fn_800B8BEC when
// bit 0 of its flags is set, fn_800BDF30 when bit 2 is), type-2 models also
// getting their animation with its length kept. Then the manager object (a
// TObject with s04EBubbleManagerVtable as its vtable) is made, its constructor
// written out here.

// one of the family's models: its type and flags, the model and its animation
// once loaded, the animation's length and its file name
typedef struct S04EBubbleModel {
	s8 type;  // 0x00
	u8 flags; // 0x01
	u8 unk02[0x6];
	void* model;      // 0x08
	void* animation;  // 0x0C
	f32 duration;     // 0x10
	const char* name; // 0x14
} S04EBubbleModel;    // 0x18

extern "C" u8 s04EBubbleModels[];
extern "C" char s04EBubbleNameFormat[];
extern "C" char s04EBubbleAnimationFormat[];
extern "C" char* s04EBubbleManagerClassName;
extern "C" u8 s04EBubbleManagerVtable[];
extern "C" TObject* s04EBubbleManagerObject;
extern "C" void* lbl_8042C110;
extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" u8 lbl_802FF5A0[];

extern "C" int sprintf(char* buffer, const char* format, ...);
extern "C" void fn_801A4C84(void* resource);
extern "C" void fn_80150958(void* clump);
extern "C" void fn_800B8BEC(void* clump, s32 flag);
extern "C" void fn_800BDF30(void* clump);
extern "C" void fn_8020C2D8(void* animation);
extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* __ct__7TObjectFP7TObject(void* object, void* parent);
extern "C" void LoadOneFile__7ONEFILEFPc(void* onefile, void* name);
extern "C" void* CheckFileID__7ONEFILEFPc(void* onefile, const char* name);
extern "C" void* LoadClumpEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);
extern "C" void* LoadHAnimationEx__7ONEFILEFUiPc(void* onefile, void* id, void* archive);

extern "C" void s04EBubbleUnload(void)
{
	S04EBubbleModel* model = (S04EBubbleModel*)s04EBubbleModels;

	for (u8 i = 0; i < 1; i++) {
		if (model->animation != NULL) {
			fn_8020C2D8(model->animation);
			model->animation = NULL;
		}
		if (model->model != NULL) {
			fn_80150958(model->model);
			model->model = NULL;
		}
	}
	delete s04EBubbleManagerObject;
	s04EBubbleManagerObject = NULL;
}

extern "C" void s04EBubbleLoad(void)
{
	char name[0x20];
	void* resource = *(void**)(lbl_8042C1D0 + 0x8C18);

	if (resource != NULL) {
		fn_801A4C84(resource);
	} else {
		return;
	}
	LoadOneFile__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), lbl_802FF5A0);
	S04EBubbleModel* model = (S04EBubbleModel*)s04EBubbleModels;

	for (u8 i = 0; i < 1; i++) {
		sprintf(name, s04EBubbleNameFormat, model->name);
		model->model = LoadClumpEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
		    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
		if (model->model != NULL && (model->flags & 1)) {
			fn_800B8BEC(model->model, 0);
		}
		if (model->model != NULL && (model->flags & 4)) {
			fn_800BDF30(model->model);
		}
		if (model->type == 2) {
			sprintf(name, s04EBubbleAnimationFormat, model->name);
			void* animation = LoadHAnimationEx__7ONEFILEFUiPc(*(void**)(lbl_8042C298 + 0xA50),
			    CheckFileID__7ONEFILEFPc(*(void**)(lbl_8042C298 + 0xA50), name), lbl_802FF5A0);
			if (animation != NULL) {
				model->duration  = *(f32*)((u8*)animation + 0xC);
				model->animation = animation;
			}
		}
		model++;
	}
	u8* manager = (u8*)Malloc__9THeapCtrlFUi(lbl_8042C148, 0x2C);
	if (manager != NULL) {
		__ct__7TObjectFP7TObject(manager, lbl_8042C110);
		*(u8**)(manager + 0x18)  = s04EBubbleManagerVtable;
		*(char**)(manager + 0x0) = s04EBubbleManagerClassName;
		*(s16*)(manager + 0x1E)  = 0x2C;
		*(u32*)(manager + 0x28)  = 0;
	}
	s04EBubbleManagerObject = (TObject*)manager;
}
