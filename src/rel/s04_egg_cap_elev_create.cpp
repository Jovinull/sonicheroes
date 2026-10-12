#include "types.h"

// The factory rel/s04_egg_cap_elev_register.cpp puts in the s04EggCapElev's
// editor record. The factory allocates 0x108 bytes and hands them to the
// module's constructor (left as assembly and named s04EggCapElevCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s04EggCapElevCtor(void* object, void* owner);

extern "C" void s04EggCapElevCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x108);

	if (memory != NULL) {
		s04EggCapElevCtor(memory, lbl_8042C110);
	}
}
