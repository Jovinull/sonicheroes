#include "types.h"

// The factory rel/s02_break_door_register.cpp puts in the s02Breakdoor's editor
// record. The factory allocates 0xD8 bytes and hands them to the module's
// constructor (left as assembly and named s02BreakdoorCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s02BreakdoorCtor(void* object, void* owner);

extern "C" void s02BreakdoorCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xD8);

	if (memory != NULL) {
		s02BreakdoorCtor(memory, lbl_8042C110);
	}
}
