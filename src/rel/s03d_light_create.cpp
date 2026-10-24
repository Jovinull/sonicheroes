#include "types.h"

// The factory rel/s03d_light_register.cpp puts in the s03dLight's editor record. The factory allocates 0x4C bytes and hands them to the module's constructor (left as assembly and named s03dLightCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s03dLightCtor(void* object, void* owner);

extern "C" void s03dLightCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x4C);

	if (memory != NULL) {
		s03dLightCtor(memory, lbl_8042C110);
	}
}
