#include "types.h"

// The factory rel/metal_sonic_2nd_register.cpp puts in the metalSonic2nd's editor record. The factory allocates 0x378 bytes and hands them to the module's constructor (left as assembly and named metalSonic2ndCtor here, as rel/reel_assets.cpp names the reel's), with the task at lbl_8042C10C as its owner.

extern "C" void* lbl_8042C10C;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* metalSonic2ndCtor(void* object, void* owner);

extern "C" void metalSonic2ndCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x378);

	if (memory != NULL) {
		metalSonic2ndCtor(memory, lbl_8042C10C);
	}
}
