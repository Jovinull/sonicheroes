#include "types.h"

// The capture enemy's other factory (captureObjectNew here), the same in the
// seven stage modules that carry the capture: as captureObjectCreate, but it
// returns the new object.

extern "C" void* lbl_8042C10C;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* captureObjectCtor(void* object, void* owner);

extern "C" void* captureObjectNew(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x58C);

	if (memory != NULL) {
		memory = captureObjectCtor(memory, lbl_8042C10C);
	}
	return memory;
}
