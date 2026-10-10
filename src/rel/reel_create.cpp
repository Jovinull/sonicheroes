#include "types.h"

// The factory rel/reel_object_register.cpp puts in the reelObject's editor
// record. The factory allocates 0xF8 bytes and hands them to the module's
// constructor (left as assembly and named reelObjectCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* reelObjectCtor(void* object, void* owner);

extern "C" void reelObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xF8);

	if (memory != NULL) {
		reelObjectCtor(memory, lbl_8042C110);
	}
}
