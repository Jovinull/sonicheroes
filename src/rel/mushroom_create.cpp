#include "types.h"

// The factory rel/mushroom_register.cpp puts in the mushroom's editor record.
// The factory allocates 0x120 bytes and hands them to the module's constructor
// (left as assembly and named mushroomCtor here, as rel/reel_assets.cpp names
// the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* mushroomCtor(void* object, void* owner);

extern "C" void mushroomCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x120);

	if (memory != NULL) {
		mushroomCtor(memory, lbl_8042C110);
	}
}
