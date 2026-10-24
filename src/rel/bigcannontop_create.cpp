#include "types.h"

// The factory rel/bigcannontop_register.cpp puts in the bigcannontop's editor record. The factory allocates 0x148 bytes and hands them to the module's constructor (left as assembly and named bigcannontopCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* bigcannontopCtor(void* object, void* owner);

extern "C" void bigcannontopCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x148);

	if (memory != NULL) {
		bigcannontopCtor(memory, lbl_8042C110);
	}
}
