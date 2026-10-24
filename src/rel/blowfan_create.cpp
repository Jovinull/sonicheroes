#include "types.h"

// The factory rel/blowfan_register.cpp puts in the blowfan's editor record. The factory allocates 0xFC bytes and hands them to the module's constructor (left as assembly and named blowfanCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* blowfanCtor(void* object, void* owner);

extern "C" void blowfanCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xFC);

	if (memory != NULL) {
		blowfanCtor(memory, lbl_8042C110);
	}
}
