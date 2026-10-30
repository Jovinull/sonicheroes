#include "types.h"

// The factory the module's register puts in TObjPropeller07's editor record ("PROPELLER"). The factory
// allocates 0x120 bytes and hands them to TObjPropeller07's constructor (left as assembly).
// Only stage07D has it.

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* __ct__15TObjPropeller07FP7TObject(void* object, void* owner);

extern "C" void propeller07Create(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x120);

	if (memory != NULL) {
		__ct__15TObjPropeller07FP7TObject(memory, lbl_8042C110);
	}
}
