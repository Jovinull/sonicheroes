#include "types.h"

// The factory rel/scaffold12_object_register.cpp puts in the scaffold12Object's
// editor record. The factory allocates 0x144 bytes and hands them to the
// module's constructor (left as assembly and named scaffold12ObjectCtor here,
// as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* scaffold12ObjectCtor(void* object, void* owner);

extern "C" void scaffold12ObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x144);

	if (memory != NULL) {
		scaffold12ObjectCtor(memory, lbl_8042C110);
	}
}
