#include "types.h"

// TObjS14ThunderSet3's destructor (s14ThunderSet3Dtor here; the class name is the string its
// constructor stores in the class-name word). It restores both vtables (the
// object's and its TObjSetObj base's, 0xB words further), runs the two bases
// down and frees the object when the delete flag asks for it, the body of
// sample1Dtor (rel/sample1_object.cpp). It is in stage13D, stage27D and stage28D.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

typedef struct SetObj {
	void* frame;   // 0x00
	void** vtable; // 0x04
} SetObj;

typedef struct S14ThunderSet3 {
	TObject base;  // 0x00
	SetObj setObj; // 0x28
} S14ThunderSet3;

extern "C" void* lbl_8042C148;
extern "C" void* s14ThunderSet3Vtable[];

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, TObject* object);
extern "C" void __dt__10TObjSetObjFv(SetObj* setObj, s32 flags);

extern "C" S14ThunderSet3* s14ThunderSet3Dtor(S14ThunderSet3* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = s14ThunderSet3Vtable;
		object->setObj.vtable = s14ThunderSet3Vtable + 0xB;
		__dt__10TObjSetObjFv(&object->setObj, 0);
		__dt__7TObjectFv(&object->base, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, &object->base);
		}
	}
	return object;
}
