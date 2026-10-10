#include "types.h"

// The factory rel/s04_egg_cap2_register.cpp puts in the s04EggCap2's editor
// record. The factory allocates 0x10C bytes and hands them to the module's
// constructor (left as assembly and named s04EggCap2Ctor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s04EggCap2Ctor(void* object, void* owner);

extern "C" void s04EggCap2Create(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x10C);

	if (memory != NULL) {
		s04EggCap2Ctor(memory, lbl_8042C110);
	}
}
