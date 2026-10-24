#include "types.h"

// The factory rel/dfan_register.cpp puts in the dfan's editor record. The factory allocates 0x124 bytes and hands them to the module's constructor (left as assembly and named dfanCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* dfanCtor(void* object, void* owner);

extern "C" void dfanCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x124);

	if (memory != NULL) {
		dfanCtor(memory, lbl_8042C110);
	}
}
