#include "types.h"

// The factory rel/trispring_register.cpp puts in the trispring's editor record.
// The factory allocates 0x54 bytes and hands them to the module's constructor
// (left as assembly and named trispringCtor here, as rel/reel_assets.cpp names
// the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* trispringCtor(void* object, void* owner);

extern "C" void trispringCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x54);

	if (memory != NULL) {
		trispringCtor(memory, lbl_8042C110);
	}
}
