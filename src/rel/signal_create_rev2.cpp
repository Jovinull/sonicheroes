#include "types.h"

// signalCreate in the four stage modules built from the other revision of this
// object (stage13D, 26D, 27D and 28D), whose registration differs from the one
// rel/signal_assets.cpp matches: the factory itself is the same, allocating
// 0xFC bytes and handing them to the module's constructor.

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* signalCtor(void* object, void* owner);

extern "C" void signalCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xFC);

	if (memory != NULL) {
		signalCtor(memory, lbl_8042C110);
	}
}
