#include "types.h"

// The factory rel/goal_ring_register.cpp puts in the goal ring's editor record.
// The factory allocates 0x100 bytes and hands them to TObjGoalring's
// constructor (rel/goal_ring_ctor.cpp).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* __ct__12TObjGoalringFP7TObject(void* object, void* owner);

extern "C" void goalRingCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x100);

	if (memory != NULL) {
		__ct__12TObjGoalringFP7TObject(memory, lbl_8042C110);
	}
}
