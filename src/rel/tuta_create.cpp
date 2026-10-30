#include "types.h"

// The factory that creates a TObjTuta (the class name its constructor stores). The
// factory allocates 0x58 bytes and hands them to the module's constructor
// (left as assembly and named tutaCtor here, as rel/tutaetc_create.cpp names
// the tutaetc's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* tutaCtor(void* object, void* owner);

extern "C" void tutaCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x58);

	if (memory != NULL) {
		tutaCtor(memory, lbl_8042C110);
	}
}
