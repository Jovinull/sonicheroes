#include "types.h"

// The factory the module's register puts in TObjFlower's editor record ("FLOWER"). The factory
// allocates 0x110 bytes and hands them to TObjFlower's constructor (left as assembly).
// Only stage09D has it.

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* __ct__10TObjFlowerFP7TObject(void* object, void* owner);

extern "C" void flowerCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x110);

	if (memory != NULL) {
		__ct__10TObjFlowerFP7TObject(memory, lbl_8042C110);
	}
}
