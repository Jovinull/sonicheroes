#include "types.h"

// The factory rel/rainivy_register.cpp puts in the rainivy's editor record. The factory allocates 0x100 bytes and hands them to the module's constructor (left as assembly and named rainivyCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* rainivyCtor(void* object, void* owner);

extern "C" void rainivyCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x100);

	if (memory != NULL) {
		rainivyCtor(memory, lbl_8042C110);
	}
}
