#include "types.h"

// The factory rel/autodoor_register.cpp puts in the autodoor's editor record. The factory allocates 0x124 bytes and hands them to the module's constructor (left as assembly and named autodoorCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* autodoorCtor(void* object, void* owner);

extern "C" void autodoorCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x124);

	if (memory != NULL) {
		autodoorCtor(memory, lbl_8042C110);
	}
}
