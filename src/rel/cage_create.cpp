#include "types.h"

// The factory rel/cage_object_register.cpp puts in the cageObject's editor
// record. The factory allocates 0x158 bytes and hands them to the module's
// constructor (left as assembly and named cageObjectCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* cageObjectCtor(void* object, void* owner);

extern "C" void cageObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x158);

	if (memory != NULL) {
		cageObjectCtor(memory, lbl_8042C110);
	}
}
