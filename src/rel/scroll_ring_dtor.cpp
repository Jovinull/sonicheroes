#include "types.h"

// TObjScrollRing's destructor. Unlike the rest of the ring family it walks
// down through three separate vtable states rather than one: reset to the
// first shape and release the embedded volume, reset to a second shape and
// release a counted array before running the embedded motion base down,
// then reset to a third (smaller) shape, release the array again and run
// the object base down. Each step re-checks the object pointer rather than
// sharing one guard — the same shape a destructor gets for its own body
// everywhere else in this family, here nested three deep because each step
// is the inlined body of what would otherwise be a separate base dtor.
//
// The claim is .text 0x8914 to 0x8A24 and nothing else. The three vtables
// stay in each module's data and are renamed to the shared names below; the
// run reads no constant, so it owns no rodata.
//
// The name is read from the layout: the run ends exactly where
// scrollRingCtor begins.
//
// The run is the same in all thirteen stage modules that carry it (twelve
// engine-core modules plus stage13D).
//
// The delete flag is a short. It is sign extended before the test, so a
// plain s32 parameter does not reproduce the compare.

extern "C" void* lbl_8042C148;

extern "C" void dtor_8003C52C(void* volume, s32 flags);
extern "C" void dtor_8005BD3C(void* motion, s32 flags);
extern "C" void __dt__7TObjectFv(void* object, s32 flags);
extern "C" void __destroy_new_array(void* array, void (*destructor)(void*, int));
extern "C" void scrollRingFieldDtor(void*, int);
extern "C" void fn_800189A4(void* heap, void* object);

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" void* scrollRingVtableA[];
extern "C" void* scrollRingVtableB[];
extern "C" void* scrollRingVtableC[];

extern "C" void* scrollRingDtor(void* object, s16 flags)
{
	u8* base = (u8*)object;

	if (object != NULL) {
		*(void**)(base + 0x18) = scrollRingVtableA;
		*(void**)(base + 0x54) = scrollRingVtableA + 0xC;

		dtor_8003C52C(base + 0x58, 0);

		if (object != NULL) {
			*(void**)(base + 0x18) = scrollRingVtableB;
			*(void**)(base + 0x54) = scrollRingVtableB + 0xC;

			if (*(void**)(base + 0x4C) != NULL) {
				__destroy_new_array(*(void**)(base + 0x4C), scrollRingFieldDtor);
				*(void**)(base + 0x4C) = NULL;
				*(u8*)(base + 0x28)    = 0;
			}

			dtor_8005BD3C(base + 0x50, 0);

			if (object != NULL) {
				*(void**)(base + 0x18) = scrollRingVtableC;

				if (*(void**)(base + 0x4C) != NULL) {
					__destroy_new_array(*(void**)(base + 0x4C), scrollRingFieldDtor);
					*(void**)(base + 0x4C) = NULL;
					*(u8*)(base + 0x28)    = 0;
				}

				__dt__7TObjectFv(object, 0);
			}
		}

		if (flags > 0) {
			fn_800189A4(lbl_8042C148, object);
		}
	}
	return object;
}
