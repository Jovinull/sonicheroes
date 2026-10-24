#include "types.h"

// The factory rel/aligator_register.cpp puts in the aligator's editor record. The factory allocates 0x1E4 bytes and hands them to the module's constructor (left as assembly and named aligatorCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* aligatorCtor(void* object, void* owner);

extern "C" void aligatorCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x1E4);

	if (memory != NULL) {
		aligatorCtor(memory, lbl_8042C110);
	}
}
