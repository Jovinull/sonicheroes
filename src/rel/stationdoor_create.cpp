#include "types.h"

// The factory rel/stationdoor_register.cpp puts in the stationdoor's editor record. The factory allocates 0x274 bytes and hands them to the module's constructor (left as assembly and named stationdoorCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* stationdoorCtor(void* object, void* owner);

extern "C" void stationdoorCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x274);

	if (memory != NULL) {
		stationdoorCtor(memory, lbl_8042C110);
	}
}
