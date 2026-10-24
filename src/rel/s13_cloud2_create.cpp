#include "types.h"

// The factory rel/s13_cloud_register.cpp puts in the s13Cloud2's editor record. The factory allocates 0xC0 bytes and hands them to the module's constructor (left as assembly and named s13Cloud2Ctor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s13Cloud2Ctor(void* object, void* owner);

extern "C" void s13Cloud2Create(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xC0);

	if (memory != NULL) {
		s13Cloud2Ctor(memory, lbl_8042C110);
	}
}
