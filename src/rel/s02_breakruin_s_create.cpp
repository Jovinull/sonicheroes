#include "types.h"

// The factory rel/s02_break_ruin_s_register.cpp puts in the s02BreakruinS's
// editor record. The factory allocates 0xDC bytes and hands them to the
// module's constructor (left as assembly and named s02BreakruinSCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s02BreakruinSCtor(void* object, void* owner);

extern "C" void s02BreakruinSCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xDC);

	if (memory != NULL) {
		s02BreakruinSCtor(memory, lbl_8042C110);
	}
}
