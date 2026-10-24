#include "types.h"

// The factory rel/wcannon_register.cpp puts in the wcannon's editor record. The factory allocates 0x28C bytes and hands them to the module's constructor (left as assembly and named wcannonCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* wcannonCtor(void* object, void* owner);

extern "C" void wcannonCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x28C);

	if (memory != NULL) {
		wcannonCtor(memory, lbl_8042C110);
	}
}
