#include "types.h"

// The factory rel/itembaloon_register.cpp puts in the scrolling item balloon's
// editor record. The factory allocates 0x11C bytes and hands them to the
// module's constructor (left as assembly and named scrolllitemObjectCtor here,
// as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* scrolllitemObjectCtor(void* object, void* owner);

extern "C" void scrolllitemObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x11C);

	if (memory != NULL) {
		scrolllitemObjectCtor(memory, lbl_8042C110);
	}
}
