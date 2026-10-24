#include "types.h"

// The factory rel/bigcannon_register.cpp puts in the bigcannon's editor record. The factory allocates 0x268 bytes and hands them to the module's constructor (left as assembly and named bigcannonCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* bigcannonCtor(void* object, void* owner);

extern "C" void bigcannonCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x268);

	if (memory != NULL) {
		bigcannonCtor(memory, lbl_8042C110);
	}
}
