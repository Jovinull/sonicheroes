#include "types.h"

// The factory rel/raildash_register.cpp puts in the raildash's editor record. The factory allocates 0x184 bytes and hands them to the module's constructor (left as assembly and named raildashCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* raildashCtor(void* object, void* owner);

extern "C" void raildashCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x184);

	if (memory != NULL) {
		raildashCtor(memory, lbl_8042C110);
	}
}
