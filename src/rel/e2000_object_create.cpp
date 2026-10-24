#include "types.h"

// The factory rel/e2000_object_register.cpp puts in the e2000Object's editor record. The factory allocates 0x2F0 bytes and hands them to the module's constructor (left as assembly and named e2000ObjectCtor here, as rel/reel_assets.cpp names the reel's), with the task at lbl_8042C10C as its owner.

extern "C" void* lbl_8042C10C;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* e2000ObjectCtor(void* object, void* owner);

extern "C" void e2000ObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x2F0);

	if (memory != NULL) {
		e2000ObjectCtor(memory, lbl_8042C10C);
	}
}
