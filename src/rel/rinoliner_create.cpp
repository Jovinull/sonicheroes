#include "types.h"

// The factory rel/e_rinoliner_stage11.cpp puts in the rinolinerObject's editor
// record. The factory allocates 0x320 bytes and hands them to the module's
// constructor (left as assembly and named rinolinerObjectCtor here, as
// rel/reel_assets.cpp names the reel's), with the task at lbl_8042C10C as its
// owner.

extern "C" void* lbl_8042C10C;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* rinolinerObjectCtor(void* object, void* owner);

extern "C" void rinolinerObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x320);

	if (memory != NULL) {
		rinolinerObjectCtor(memory, lbl_8042C10C);
	}
}
