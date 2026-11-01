#include "types.h"

// Makes the special stages' third sled link object (bobLinkTurnCreate here;
// the class has no PS2 name), in stage01D and stage07D: 0x68 bytes from the
// object heap, handed to the class's constructor (left as assembly and named
// bobLinkTurnCtor here) with the caller's parameters.

extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* bobLinkTurnCtor(void* object, void* params);

extern "C" void bobLinkTurnCreate(void* params)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x68);

	if (memory != NULL) {
		bobLinkTurnCtor(memory, params);
	}
}
