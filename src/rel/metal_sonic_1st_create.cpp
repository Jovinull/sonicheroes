#include "types.h"

// The factory rel/metal_sonic_1st_register.cpp puts in the metalSonic1st's editor record. The factory allocates 0x3F8 bytes and hands them to the module's constructor (left as assembly and named metalSonic1stCtor here, as rel/reel_assets.cpp names the reel's), with the task at lbl_8042C10C as its owner.

extern "C" void* lbl_8042C10C;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* metalSonic1stCtor(void* object, void* owner);

extern "C" void metalSonic1stCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x3F8);

	if (memory != NULL) {
		metalSonic1stCtor(memory, lbl_8042C10C);
	}
}
