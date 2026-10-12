#include "types.h"

// The factory rel/light_collision_register.cpp puts in the light collision's
// editor record. The factory allocates 0x40 bytes and hands them to the
// module's constructor (left as assembly and named lightCollisionCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* lightCollisionCtor(void* object, void* owner);

extern "C" void lightCollisionCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x40);

	if (memory != NULL) {
		lightCollisionCtor(memory, lbl_8042C110);
	}
}
