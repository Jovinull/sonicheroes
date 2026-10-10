#include "types.h"

// The factory rel/bigrings_object_register.cpp puts in the bigringsObject's
// editor record. The factory allocates 0x6C bytes and hands them to the
// module's constructor (left as assembly and named bigringsObjectCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* bigringsObjectCtor(void* object, void* owner);

extern "C" void bigringsObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x6C);

	if (memory != NULL) {
		bigringsObjectCtor(memory, lbl_8042C110);
	}
}
