#include "types.h"

// The factory rel/king_pawn_register.cpp puts in the king pawn's editor
// record. Unless the byte at 0x22 of the object at lbl_8042C180 is set, the
// factory allocates 0x2A0 bytes and hands them to the module's constructor
// (left as assembly and named kingPawnCtor here), with the task at
// lbl_8042C110 as its owner.

extern "C" u8* lbl_8042C180;
extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* kingPawnCtor(void* object, void* owner);

extern "C" void kingPawnCreate(void)
{
	if (*(s8*)(lbl_8042C180 + 0x22) == 0) {
		void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x2A0);

		if (memory != NULL) {
			kingPawnCtor(memory, lbl_8042C110);
		}
	}
}
