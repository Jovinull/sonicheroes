#include "types.h"

// The factory rel/s03_door_register.cpp puts in the s03Door's editor record.
// The factory allocates 0xEC bytes and hands them to the module's constructor
// (left as assembly and named s03DoorCtor here, as rel/reel_assets.cpp names
// the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s03DoorCtor(void* object, void* owner);

extern "C" void s03DoorCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xEC);

	if (memory != NULL) {
		s03DoorCtor(memory, lbl_8042C110);
	}
}
