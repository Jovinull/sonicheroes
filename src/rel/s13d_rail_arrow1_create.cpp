#include "types.h"

// The factory rel/s13d_rail_arrow_1_register.cpp puts in the s13dRailArrow1
// family's editor record. The factory allocates 0xCC bytes and hands them to
// the constructor it shares with its sibling objects (left as assembly and
// named s13dRailArrowCtor here), as kind 0.

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s13dRailArrowCtor(void* object, void* owner, s32 kind);

extern "C" void s13dRailArrow1Create(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xCC);

	if (memory != NULL) {
		s13dRailArrowCtor(memory, lbl_8042C110, 0);
	}
}
