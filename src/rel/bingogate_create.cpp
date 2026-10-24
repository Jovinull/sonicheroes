#include "types.h"

// The factory rel/bingogate_register.cpp puts in the bingogate's editor record. The factory allocates 0x174 bytes and hands them to the module's constructor (left as assembly and named bingogateCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* bingogateCtor(void* object, void* owner);

extern "C" void bingogateCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x174);

	if (memory != NULL) {
		bingogateCtor(memory, lbl_8042C110);
	}
}
