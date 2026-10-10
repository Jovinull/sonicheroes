#include "types.h"

// The factory rel/laserfence_object_register.cpp puts in the laserfenceObject's
// editor record. The factory allocates 0xF8 bytes and hands them to the
// module's constructor (left as assembly and named laserfenceObjectCtor here,
// as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* laserfenceObjectCtor(void* object, void* owner);

extern "C" void laserfenceObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xF8);

	if (memory != NULL) {
		laserfenceObjectCtor(memory, lbl_8042C110);
	}
}
