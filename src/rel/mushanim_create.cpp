#include "types.h"

// The factory rel/mushanim_register.cpp puts in the mushanim's editor record. The factory allocates 0x110 bytes and hands them to the module's constructor (left as assembly and named mushanimCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* mushanimCtor(void* object, void* owner);

extern "C" void mushanimCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x110);

	if (memory != NULL) {
		mushanimCtor(memory, lbl_8042C110);
	}
}
