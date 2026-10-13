#include "types.h"

// The factory rel/propeller_register.cpp puts in the propeller's editor record.
// The factory allocates 0x164 bytes and hands them to TObjPropeller's
// constructor (rel/propeller_ctor.cpp).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* __ct__13TObjPropellerFP7TObject(void* object, void* owner);

extern "C" void propellerCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x164);

	if (memory != NULL) {
		__ct__13TObjPropellerFP7TObject(memory, lbl_8042C110);
	}
}
