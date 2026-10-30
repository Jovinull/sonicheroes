#include "types.h"

// The factory that creates a TObjTutaC (the class name its constructor stores). The
// factory allocates 0x58 bytes and hands them to the module's constructor
// (left as assembly and named tutacCtor here, as rel/tutaetc_create.cpp names
// the tutaetc's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* tutacCtor(void* object, void* owner);

extern "C" void tutacCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x58);

	if (memory != NULL) {
		tutacCtor(memory, lbl_8042C110);
	}
}
