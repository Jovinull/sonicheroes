#include "types.h"

// The factory rel/reafredgreen_register.cpp puts in the reafredgreen's editor record. The factory allocates 0x138 bytes and hands them to the module's constructor (left as assembly and named reafredgreenCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* reafredgreenCtor(void* object, void* owner);

extern "C" void reafredgreenCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x138);

	if (memory != NULL) {
		reafredgreenCtor(memory, lbl_8042C110);
	}
}
