#include "types.h"

// The factory rel/s04d_elevator_register.cpp puts in the s04dElevator's editor
// record. The factory allocates 0x114 bytes and hands them to the module's
// constructor (left as assembly and named s04dElevatorCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s04dElevatorCtor(void* object, void* owner);

extern "C" void s04dElevatorCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x114);

	if (memory != NULL) {
		s04dElevatorCtor(memory, lbl_8042C110);
	}
}
