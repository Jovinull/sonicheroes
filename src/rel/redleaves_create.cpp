#include "types.h"

// The factory rel/redleaves_register.cpp puts in the redleaves's editor record. The factory allocates 0x104 bytes and hands them to the module's constructor (left as assembly and named redleavesCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* redleavesCtor(void* object, void* owner);

extern "C" void redleavesCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x104);

	if (memory != NULL) {
		redleavesCtor(memory, lbl_8042C110);
	}
}
