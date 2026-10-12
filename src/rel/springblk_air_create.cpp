#include "types.h"

// The factory rel/springblk_air_register.cpp puts in the springblkAir's editor
// record. The factory allocates 0x130 bytes and hands them to the module's
// constructor (left as assembly and named springblkAirCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* springblkAirCtor(void* object, void* owner);

extern "C" void springblkAirCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x130);

	if (memory != NULL) {
		springblkAirCtor(memory, lbl_8042C110);
	}
}
