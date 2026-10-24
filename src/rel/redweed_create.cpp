#include "types.h"

// The factory rel/redweed_register.cpp puts in the redweed's editor record. The factory allocates 0x108 bytes and hands them to the module's constructor (left as assembly and named redweedCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* redweedCtor(void* object, void* owner);

extern "C" void redweedCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x108);

	if (memory != NULL) {
		redweedCtor(memory, lbl_8042C110);
	}
}
