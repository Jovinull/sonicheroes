#include "types.h"

// The factory rel/formgate_register.cpp puts in the formation gate's editor
// record. The factory allocates 0x114 bytes and hands them to the module's
// constructor (left as assembly and named formgateObjectCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* formgateObjectCtor(void* object, void* owner);

extern "C" void formgateObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x114);

	if (memory != NULL) {
		formgateObjectCtor(memory, lbl_8042C110);
	}
}
