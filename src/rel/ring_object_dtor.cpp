#include "types.h"

// TObjSetRing's destructor (the PS2 build's class; ringObjectDtor here): the
// rings released, the set object run down, then TObjRing's destructor
// (rel/ring_cdtor.cpp) inlined, which releases the rings again if any are
// left, and the object base run down. Its two vtables are the ones the scroll
// ring's units name scrollRingVtableB and scrollRingVtableC.

extern "C" void* lbl_8042C148;

extern "C" void __dt__10TObjSetObjFv(void* motion, s32 flags);
extern "C" void __dt__7TObjectFv(void* object, s32 flags);
extern "C" void __destroy_new_array(void* array, void (*destructor)(void*, int));
extern "C" void scrollRingFieldDtor(void*, int);
extern "C" void Free__9THeapCtrlFPv(void* heap, void* object);

extern "C" void* scrollRingVtableB[];
extern "C" void* scrollRingVtableC[];

extern "C" void* ringObjectDtor(void* object, s16 flags)
{
	u8* base = (u8*)object;

	if (object != NULL) {
		*(void**)(base + 0x18) = scrollRingVtableB;
		*(void**)(base + 0x54) = scrollRingVtableB + 0xC;
		if (*(void**)(base + 0x4C) != NULL) {
			__destroy_new_array(*(void**)(base + 0x4C), scrollRingFieldDtor);
			*(void**)(base + 0x4C) = NULL;
			*(u8*)(base + 0x28)    = 0;
		}
		__dt__10TObjSetObjFv(base + 0x50, 0);
		if (object != NULL) {
			*(void**)(base + 0x18) = scrollRingVtableC;
			if (*(void**)(base + 0x4C) != NULL) {
				__destroy_new_array(*(void**)(base + 0x4C), scrollRingFieldDtor);
				*(void**)(base + 0x4C) = NULL;
				*(u8*)(base + 0x28)    = 0;
			}
			__dt__7TObjectFv(object, 0);
		}
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, object);
		}
	}
	return object;
}
