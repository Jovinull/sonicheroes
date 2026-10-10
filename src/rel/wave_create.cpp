#include "types.h"

// The factory rel/wave_register.cpp puts in the wave's editor record. The
// factory allocates 0x5C bytes and hands them to the module's constructor (left
// as assembly and named waveCtor here, as rel/reel_assets.cpp names the
// reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* waveCtor(void* object, void* owner);

extern "C" void waveCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x5C);

	if (memory != NULL) {
		waveCtor(memory, lbl_8042C110);
	}
}
