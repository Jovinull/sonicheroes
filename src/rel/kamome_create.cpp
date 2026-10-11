#include "types.h"

// The factory rel/kamome_register.cpp puts in the kamome's editor record. The
// factory allocates 0x44 bytes and hands them to the module's constructor,
// kamomeCtor (rel/kamome_ctor.cpp).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* kamomeCtor(void* object, void* owner);

extern "C" void kamomeCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x44);

	if (memory != NULL) {
		kamomeCtor(memory, lbl_8042C110);
	}
}
