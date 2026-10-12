#include "types.h"

// The reset, unload and load hooks and the factory rel/hintcolli_register.cpp
// puts in the hint collision's editor record. The empty hooks have nothing to
// do: the object loads nothing. The factory allocates 0x108 bytes and hands
// them to the module's constructor (left as assembly and named
// hintcolliObjectCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* hintcolliObjectCtor(void* object, void* owner);

extern "C" void hintcolliObjectReset(void) { }

extern "C" void hintcolliObjectUnload(void) { }

extern "C" void hintcolliObjectLoad(void) { }

extern "C" void hintcolliObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x108);

	if (memory != NULL) {
		hintcolliObjectCtor(memory, lbl_8042C110);
	}
}
