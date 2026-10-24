#include "types.h"

// TObjRing's destructor and constructor (the PS2 build's class; ringDtor and
// ringCtor here), the base of the set ring and the scroll ring, whose own
// destructors inline this one (rel/scroll_ring_dtor.cpp). The destructor
// releases the rings, if any, and runs the object base down; the constructor
// starts with no rings and the object active. TObjRing's vtable is the one the
// scroll ring's units name scrollRingVtableC.

extern "C" void* lbl_8042C148;
extern "C" const char* ringClassName;

extern "C" void __ct__7TObjectFP7TObject(void* object, void* parent);
extern "C" void __dt__7TObjectFv(void* object, s32 flags);
extern "C" void __destroy_new_array(void* array, void (*destructor)(void*, int));
extern "C" void scrollRingFieldDtor(void*, int);
extern "C" void Free__9THeapCtrlFPv(void* heap, void* object);

extern "C" void* scrollRingVtableC[];

extern "C" void* ringDtor(void* object, s16 flags)
{
	u8* base = (u8*)object;

	if (object != NULL) {
		*(void**)(base + 0x18) = scrollRingVtableC;
		if (*(void**)(base + 0x4C) != NULL) {
			__destroy_new_array(*(void**)(base + 0x4C), scrollRingFieldDtor);
			*(void**)(base + 0x4C) = NULL;
			*(u8*)(base + 0x28)    = 0;
		}
		__dt__7TObjectFv(object, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, object);
		}
	}
	return object;
}

extern "C" void* ringCtor(void* object, void* parent)
{
	u8* base = (u8*)object;

	__ct__7TObjectFP7TObject(object, parent);
	*(void**)(base + 0x18)       = scrollRingVtableC;
	*(const char**)(base + 0x00) = ringClassName;
	*(s16*)(base + 0x1E)         = 0x50;
	*(u8*)(base + 0x2B)          = 0;
	*(u8*)(base + 0x2A)          = 1;
	*(void**)(base + 0x4C)       = NULL;
	return object;
}
