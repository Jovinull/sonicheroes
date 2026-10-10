#include "types.h"

// poleCreate in the four stage modules built from the other revision of this
// object (stage13D, 26D, 27D and 28D), whose registration differs from the one
// rel/pole_assets.cpp matches: the factory itself is the same, allocating 0x110
// bytes and handing them to the module's constructor.

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* poleCtor(void* object, void* owner);

extern "C" void poleCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x110);

	if (memory != NULL) {
		poleCtor(memory, lbl_8042C110);
	}
}
