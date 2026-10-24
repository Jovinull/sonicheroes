#include "types.h"

// The factory rel/s04d_ashiba_register.cpp puts in the s04dAshiba's editor record. The factory allocates 0x104 bytes and hands them to the module's constructor (left as assembly and named s04dAshibaCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s04dAshibaCtor(void* object, void* owner);

extern "C" void s04dAshibaCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x104);

	if (memory != NULL) {
		s04dAshibaCtor(memory, lbl_8042C110);
	}
}
