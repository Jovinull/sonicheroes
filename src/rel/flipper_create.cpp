#include "types.h"

// The factory rel/flipper_register.cpp puts in the flipper's editor record. The factory allocates 0x210 bytes and hands them to the module's constructor (left as assembly and named flipperCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* flipperCtor(void* object, void* owner);

extern "C" void flipperCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x210);

	if (memory != NULL) {
		flipperCtor(memory, lbl_8042C110);
	}
}
