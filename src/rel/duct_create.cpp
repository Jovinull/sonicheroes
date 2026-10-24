#include "types.h"

// The factory rel/duct_register.cpp puts in the duct's editor record. The factory allocates 0xE0 bytes and hands them to the module's constructor (left as assembly and named ductCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* ductCtor(void* object, void* owner);

extern "C" void ductCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xE0);

	if (memory != NULL) {
		ductCtor(memory, lbl_8042C110);
	}
}
