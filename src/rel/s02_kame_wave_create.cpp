#include "types.h"

// The factory rel/s02d_kameashi_register.cpp puts in the s02KameWave's editor record. The factory allocates 0x58 bytes and hands them to the module's constructor (left as assembly and named s02KameWaveCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s02KameWaveCtor(void* object, void* owner);

extern "C" void s02KameWaveCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x58);

	if (memory != NULL) {
		s02KameWaveCtor(memory, lbl_8042C110);
	}
}
