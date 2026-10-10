#include "types.h"

// The factory rel/s11fire_object_register.cpp puts in the s11fireObject's
// editor record. The factory allocates 0x1AC bytes and hands them to the
// module's constructor (left as assembly and named s11fireObjectCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s11fireObjectCtor(void* object, void* owner);

extern "C" void s11fireObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x1AC);

	if (memory != NULL) {
		s11fireObjectCtor(memory, lbl_8042C110);
	}
}
