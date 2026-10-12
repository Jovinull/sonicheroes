#include "types.h"

// The factory rel/flyer_register.cpp puts in the flyer's editor record. The
// factory allocates 0x3C4 bytes and hands them to the module's constructor
// (left as assembly and named flyerObjectCtor here, as rel/reel_assets.cpp
// names the reel's), with the task at lbl_8042C10C as its owner.

extern "C" void* lbl_8042C10C;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* flyerObjectCtor(void* object, void* owner);

extern "C" void flyerObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x3C4);

	if (memory != NULL) {
		flyerObjectCtor(memory, lbl_8042C10C);
	}
}
