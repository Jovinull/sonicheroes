#include "types.h"

// TObjScatteredRing's destructor (the PS2 build's class; scatteredRingDtor
// here): its rings released, then TObjRing's destructor (rel/ring_cdtor.cpp)
// inlined.

extern "C" void* lbl_8042C148;

extern "C" void __dt__7TObjectFv(void* object, s32 flags);
extern "C" void __destroy_new_array(void* array, void (*destructor)(void*, int));
extern "C" void scrollRingFieldDtor(void*, int);
extern "C" void Free__9THeapCtrlFPv(void* heap, void* object);

extern "C" void* scatteredRingVtable[];
extern "C" void* scrollRingVtableC[];

extern "C" void* scatteredRingDtor(void* object, s16 flags)
{
	u8* base = (u8*)object;

	if (object != NULL) {
		*(void**)(base + 0x18) = scatteredRingVtable;
		if (*(void**)(base + 0x4C) != NULL) {
			__destroy_new_array(*(void**)(base + 0x4C), scrollRingFieldDtor);
			*(void**)(base + 0x4C) = NULL;
			*(u8*)(base + 0x28)    = 0;
		}
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
