#include "types.h"

// The factory rel/s03_big_bridge2_register.cpp puts in the s03BigBridge2's editor record. The factory allocates 0x54 bytes and hands them to the module's constructor (left as assembly and named s03BigBridge2Ctor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s03BigBridge2Ctor(void* object, void* owner);

extern "C" void s03BigBridge2Create(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x54);

	if (memory != NULL) {
		s03BigBridge2Ctor(memory, lbl_8042C110);
	}
}
