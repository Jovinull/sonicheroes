#include "types.h"

// The factory rel/s14_tower_neon_a_register.cpp puts in the s14TowerNeonA
// family's editor record. The factory allocates 0x40 bytes and hands them to
// the constructor it shares with its sibling objects (left as assembly and
// named s14TowerNeonCtor here), as kind 0.

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s14TowerNeonCtor(void* object, void* owner, s32 kind);

extern "C" void s14TowerNeonACreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x40);

	if (memory != NULL) {
		s14TowerNeonCtor(memory, lbl_8042C110, 0);
	}
}
