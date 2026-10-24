#include "types.h"

// The factory rel/railboard_register.cpp puts in the railboard's editor record. The factory allocates 0x12C bytes and hands them to the module's constructor (left as assembly and named railboardCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* railboardCtor(void* object, void* owner);

extern "C" void railboardCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x12C);

	if (memory != NULL) {
		railboardCtor(memory, lbl_8042C110);
	}
}
