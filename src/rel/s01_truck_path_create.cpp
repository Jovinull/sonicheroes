#include "types.h"

// The factory rel/s01_truck_path_register.cpp puts in the s01TruckPath's editor
// record. The factory allocates 0x118 bytes and hands them to the module's
// constructor (left as assembly and named s01TruckPathCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s01TruckPathCtor(void* object, void* owner);

extern "C" void s01TruckPathCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x118);

	if (memory != NULL) {
		s01TruckPathCtor(memory, lbl_8042C110);
	}
}
