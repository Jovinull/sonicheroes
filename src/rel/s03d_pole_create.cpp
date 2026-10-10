#include "types.h"

// The factory rel/s03d_pole_register.cpp puts in the s03dPole's editor record.
// The factory allocates 0xEC bytes and hands them to the module's constructor
// (left as assembly and named s03dPoleCtor here, as rel/reel_assets.cpp names
// the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s03dPoleCtor(void* object, void* owner);

extern "C" void s03dPoleCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xEC);

	if (memory != NULL) {
		s03dPoleCtor(memory, lbl_8042C110);
	}
}
