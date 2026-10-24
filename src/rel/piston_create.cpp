#include "types.h"

// The factory rel/piston_register.cpp puts in the PISTON's editor record. The
// factory allocates 0x100 bytes and hands them to the object's constructor
// (left as assembly and named pistonCtor here, as rel/s03_egg_cap_create.cpp
// names the egg cap's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* pistonCtor(void* object, void* owner);

extern "C" void pistonCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x100);

	if (memory != NULL) {
		pistonCtor(memory, lbl_8042C110);
	}
}
