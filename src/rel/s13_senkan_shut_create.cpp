#include "types.h"

// The factory rel/s13_senkan_shut_register.cpp puts in the s13SenkanShut's
// editor record. The factory allocates 0xD0 bytes and hands them to the
// module's constructor (left as assembly and named s13SenkanShutCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s13SenkanShutCtor(void* object, void* owner);

extern "C" void s13SenkanShutCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xD0);

	if (memory != NULL) {
		s13SenkanShutCtor(memory, lbl_8042C110);
	}
}
