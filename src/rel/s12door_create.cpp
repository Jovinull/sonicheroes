#include "types.h"

// The factory rel/s12door_object_register.cpp puts in the s12doorObject's
// editor record. The factory allocates 0xFC bytes and hands them to the
// module's constructor (left as assembly and named s12doorObjectCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s12doorObjectCtor(void* object, void* owner);

extern "C" void s12doorObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xFC);

	if (memory != NULL) {
		s12doorObjectCtor(memory, lbl_8042C110);
	}
}
