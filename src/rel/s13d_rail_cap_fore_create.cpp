#include "types.h"

// The factory rel/s13d_rail_cap_fore_register.cpp puts in the s13dRailCapFore
// family's editor record. The factory allocates 0x38 bytes and hands them to
// the constructor it shares with its sibling objects (left as assembly and
// named s13dRailCapCtor here), as kind 0.

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s13dRailCapCtor(void* object, void* owner, s32 kind);

extern "C" void s13dRailCapForeCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x38);

	if (memory != NULL) {
		s13dRailCapCtor(memory, lbl_8042C110, 0);
	}
}
