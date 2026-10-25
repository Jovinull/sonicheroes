#include "types.h"

// The factory rel/wall_register.cpp puts in the wall enemy's editor
// record. The factory allocates 0x318 bytes and hands them to the module's
// constructor (left as assembly and named wallObjectCtor here), with the task
// at lbl_8042C10C as its owner.

extern "C" void* lbl_8042C10C;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* wallObjectCtor(void* object, void* owner);

extern "C" void wallObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x318);

	if (memory != NULL) {
		wallObjectCtor(memory, lbl_8042C10C);
	}
}
