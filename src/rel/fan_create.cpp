#include "types.h"

// The factory rel/fan_object_register.cpp puts in the fanObject's editor
// record. The factory allocates 0xFC bytes and hands them to the module's
// constructor (left as assembly and named fanObjectCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* fanObjectCtor(void* object, void* owner);

extern "C" void fanObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xFC);

	if (memory != NULL) {
		fanObjectCtor(memory, lbl_8042C110);
	}
}
