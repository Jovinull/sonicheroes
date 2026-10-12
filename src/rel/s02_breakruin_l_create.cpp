#include "types.h"

// The factory rel/s02_break_ruin_l_register.cpp puts in the s02BreakruinL's
// editor record. The factory allocates 0x50 bytes and hands them to the
// module's constructor (left as assembly and named s02BreakruinLCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s02BreakruinLCtor(void* object, void* owner);

extern "C" void s02BreakruinLCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x50);

	if (memory != NULL) {
		s02BreakruinLCtor(memory, lbl_8042C110);
	}
}
