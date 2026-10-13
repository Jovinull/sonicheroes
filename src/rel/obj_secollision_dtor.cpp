#include "types.h"

// The objSecollision object's destructor (objSecollisionDtor here). It restores
// both class vtables, ends the placement when its condition has bit 0x10000 set
// (the bit objSecollisionExec sets after a one-shot sound), destroys the
// collision and placement bases and the object base, and frees the object when
// the deleting-destructor flag asks for it.

typedef struct ObjSecollisionSetData {
	u8 unk00[0x18];
	u32 flags; // 0x18
} ObjSecollisionSetData;

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

typedef struct ObjSecollision {
	TObject base;                   // 0x00
	ObjSecollisionSetData* setdata; // 0x28
	void** vtable2;                 // 0x2C
	u8 colli[0x94];                 // 0x30
} ObjSecollision;

extern "C" void* lbl_8042C148;
extern "C" void* objSecollisionVtable[];

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, TObject* object);
extern "C" void __dt__7C_COLLIFv(void* colli, s32 flags);
extern "C" void __dt__10TObjSetObjFv(void* setobj, s32 flags);
extern "C" void SetEnd__10TObjSetObjFv(void* setobj);

// TObjSetObj::TstConditionBit, inline in the class.
static inline s32 objSecollisionTstConditionBit(ObjSecollision* object, u32 flag)
{
	return (object->setdata->flags & flag) != 0;
}

extern "C" ObjSecollision* objSecollisionDtor(ObjSecollision* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable = objSecollisionVtable;
		object->vtable2     = objSecollisionVtable + 0xB;

		if (objSecollisionTstConditionBit(object, 0x10000) == 1) {
			SetEnd__10TObjSetObjFv(&object->setdata);
		}

		__dt__7C_COLLIFv(object->colli, 0);
		__dt__10TObjSetObjFv(&object->setdata, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, &object->base);
		}
	}
	return object;
}
