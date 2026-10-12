#include "types.h"

// The factory rel/capture_register.cpp puts in the capture enemy's editor
// record. The factory allocates 0x58C bytes and hands them to the module's
// constructor (left as assembly and named captureObjectCtor here, as
// rel/reel_assets.cpp names the reel's), with the task at lbl_8042C10C as its
// owner.

extern "C" void* lbl_8042C10C;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* captureObjectCtor(void* object, void* owner);

extern "C" void captureObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x58C);

	if (memory != NULL) {
		captureObjectCtor(memory, lbl_8042C10C);
	}
}
