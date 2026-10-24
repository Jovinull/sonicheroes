#include "types.h"

// The factory rel/rainfloor_register.cpp puts in the rainfloor's editor record. The factory allocates 0xF8 bytes and hands them to the module's constructor (left as assembly and named rainfloorCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* rainfloorCtor(void* object, void* owner);

extern "C" void rainfloorCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xF8);

	if (memory != NULL) {
		rainfloorCtor(memory, lbl_8042C110);
	}
}
