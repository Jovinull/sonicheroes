#include "types.h"

// TObjHintColli's destructor (the PS2 build's name, by its place in the PS2
// order): the area's model is taken out of its world slot and released, the
// hint is cleared, then the collision, the set-object base and the object
// base run down and the object is freed when the delete flag asks for it.

typedef struct RpClump RpClump;

typedef struct World {
	u8 unk0[0x72A4]; // 0x0000
	void* scene;     // 0x72A4
} World;

typedef struct HintColli {
	u8 unk000[0x18];     // 0x000
	void** vtable;       // 0x018
	u8 unk01C[0xC];      // 0x01C
	void* frame;         // 0x028, the set object's
	void** setObjVtable; // 0x02C
	u8 colli[0xD0];      // 0x030 (C_COLLI and fields)
	RpClump* model;      // 0x100
	s32 hint;            // 0x104
} HintColli;

extern "C" World* lbl_8042C1D0;
extern "C" void* lbl_8042C148;
extern "C" void* hintcolliVtable[];

extern "C" void fn_8015BBF8(void* scene, RpClump* clump);
extern "C" void fn_80150958(RpClump* clump);
extern "C" void __dt__7C_COLLIFv(void* colli, s32 flags);
extern "C" void __dt__10TObjSetObjFv(void* setObj, s32 flags);
extern "C" void __dt__7TObjectFv(void* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, void* object);

extern "C" HintColli* __dt__13TObjHintColliFv(HintColli* object, s16 flags)
{
	if (object != NULL) {
		object->vtable       = hintcolliVtable;
		object->setObjVtable = hintcolliVtable + 0xB;
		if (object->model != NULL) {
			fn_8015BBF8(lbl_8042C1D0->scene, object->model);
			fn_80150958(object->model);
			object->model = NULL;
		}
		object->hint = 0;
		__dt__7C_COLLIFv(object->colli, 0);
		__dt__10TObjSetObjFv(&object->frame, 0);
		__dt__7TObjectFv(object, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, object);
		}
	}
	return object;
}
