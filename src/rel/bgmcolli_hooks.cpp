#include "types.h"

// The reset, unload and load hooks and the factory
// rel/bgmcolli_object_register.cpp puts in the bgmcolliObject's editor record.
// The empty hooks have nothing to do: the object loads nothing. The factory
// allocates 0xF0 bytes and hands them to the module's constructor (left as
// assembly and named bgmcolliObjectCtor here, as rel/reel_assets.cpp names the
// reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* bgmcolliObjectCtor(void* object, void* owner);

extern "C" void bgmcolliObjectReset(void) { }

extern "C" void bgmcolliObjectUnload(void) { }

extern "C" void bgmcolliObjectLoad(void) { }

extern "C" void bgmcolliObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xF0);

	if (memory != NULL) {
		bgmcolliObjectCtor(memory, lbl_8042C110);
	}
}
