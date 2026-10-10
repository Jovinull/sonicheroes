#include "types.h"

// The factory rel/ivyjump_register.cpp puts in the ivyjump's editor record. The
// factory allocates 0x160 bytes and hands them to the module's constructor
// (left as assembly and named ivyjumpCtor here, as rel/reel_assets.cpp names
// the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* ivyjumpCtor(void* object, void* owner);

extern "C" void ivyjumpCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x160);

	if (memory != NULL) {
		ivyjumpCtor(memory, lbl_8042C110);
	}
}
