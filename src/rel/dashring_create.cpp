#include "types.h"

// The factory rel/dashring_object_register.cpp puts in the dashringObject's
// editor record. The factory allocates 0x6C bytes and hands them to the
// module's constructor (left as assembly and named dashringObjectCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* dashringObjectCtor(void* object, void* owner);

extern "C" void dashringObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x6C);

	if (memory != NULL) {
		dashringObjectCtor(memory, lbl_8042C110);
	}
}
