#include "types.h"

// The factory rel/propeller_register.cpp puts in the propeller's editor record.
// The factory allocates 0x164 bytes and hands them to the module's constructor
// (left as assembly and named propellerCtor here, as rel/reel_assets.cpp names
// the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* propellerCtor(void* object, void* owner);

extern "C" void propellerCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x164);

	if (memory != NULL) {
		propellerCtor(memory, lbl_8042C110);
	}
}
