#include "types.h"

// The factory rel/egghawk_colli_register.cpp puts in the egghawkColli's editor
// record. The factory allocates 0xC8 bytes and hands them to the module's
// constructor (left as assembly and named egghawkColliCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* egghawkColliCtor(void* object, void* owner);

extern "C" void egghawkColliCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xC8);

	if (memory != NULL) {
		egghawkColliCtor(memory, lbl_8042C110);
	}
}
