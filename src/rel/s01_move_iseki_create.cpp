#include "types.h"

// The factory the module's register puts in the s01MoveIseki's editor record.
// The factory allocates 0xF4 bytes and hands them to the module's constructor
// (left as assembly and named s01MoveIsekiCtor here, as rel/reel_assets.cpp
// names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s01MoveIsekiCtor(void* object, void* owner);

extern "C" void s01MoveIsekiCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xF4);

	if (memory != NULL) {
		s01MoveIsekiCtor(memory, lbl_8042C110);
	}
}
