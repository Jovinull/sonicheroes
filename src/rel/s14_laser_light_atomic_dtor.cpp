#include "types.h"

// TObjS14LaserLightAtomic's destructor (s14LaserLightAtomicDtor here; the class name is the string its
// constructor stores in the class-name word). It restores the vtable, runs the
// object base down and frees the object when the delete flag asks for it, the
// body of rel/shield_splinter_dtor.cpp. Only stage13D has it.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

extern "C" void* lbl_8042C148;
extern "C" void* s14LaserLightAtomicVtable[];

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, TObject* object);

extern "C" TObject* s14LaserLightAtomicDtor(TObject* object, s16 flags)
{
	if (object != NULL) {
		object->vtable = s14LaserLightAtomicVtable;

		__dt__7TObjectFv(object, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, object);
		}
	}
	return object;
}
