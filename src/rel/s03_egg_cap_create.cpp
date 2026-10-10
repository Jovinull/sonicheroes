#include "types.h"

// The factory rel/s03_egg_cap_register.cpp puts in the s03EggCap's editor
// record. The factory allocates 0x120 bytes and hands them to the module's
// constructor (left as assembly and named s03EggCapCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s03EggCapCtor(void* object, void* owner);

extern "C" void s03EggCapCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x120);

	if (memory != NULL) {
		s03EggCapCtor(memory, lbl_8042C110);
	}
}
