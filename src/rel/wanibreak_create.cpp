#include "types.h"

// The factory rel/wanibreak_register.cpp puts in the wanibreak's editor record. The factory allocates 0xE8 bytes and hands them to the module's constructor (left as assembly and named wanibreakCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* wanibreakCtor(void* object, void* owner);

extern "C" void wanibreakCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xE8);

	if (memory != NULL) {
		wanibreakCtor(memory, lbl_8042C110);
	}
}
