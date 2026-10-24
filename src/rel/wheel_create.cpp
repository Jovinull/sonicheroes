#include "types.h"

// The factory rel/wheel_register.cpp puts in the WHEEL's editor record. The
// factory allocates 0x120 bytes and hands them to the object's constructor
// (left as assembly and named wheelCtor here, as rel/s03_egg_cap_create.cpp
// names the egg cap's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* wheelCtor(void* object, void* owner);

extern "C" void wheelCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x120);

	if (memory != NULL) {
		wheelCtor(memory, lbl_8042C110);
	}
}
