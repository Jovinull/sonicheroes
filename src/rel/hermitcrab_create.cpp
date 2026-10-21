#include "types.h"

// The factory rel/hermitcrab_register.cpp puts in the HERMITCRAB OBJECT's editor record. The
// factory allocates 0x100 bytes and hands them to the object's constructor
// (left as assembly and named hermitcrabObjectCtor here, as rel/s03_egg_cap_create.cpp
// names the egg cap's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* hermitcrabObjectCtor(void* object, void* owner);

extern "C" void hermitcrabObjectCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x100);

	if (memory != NULL) {
		hermitcrabObjectCtor(memory, lbl_8042C110);
	}
}
