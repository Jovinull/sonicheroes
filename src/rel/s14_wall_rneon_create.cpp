#include "types.h"

// The factory rel/s14_holea_neon_register.cpp puts in the s14WallRNeon family's
// editor record. The factory allocates 0x44 bytes and hands them to the
// constructor it shares with its sibling objects (left as assembly and named
// s14NeonCtor here), as kind 4.

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s14NeonCtor(void* object, void* owner, s32 kind);

extern "C" void s14WallRNeonCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x44);

	if (memory != NULL) {
		s14NeonCtor(memory, lbl_8042C110, 4);
	}
}
