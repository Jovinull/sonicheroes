#include "types.h"

// The factory rel/s13_houdai_yoko_register.cpp puts in the s13HoudaiYoko's
// editor record. The factory allocates 0x128 bytes and hands them to the
// module's constructor (left as assembly and named s13HoudaiYokoCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s13HoudaiYokoCtor(void* object, void* owner);

extern "C" void s13HoudaiYokoCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x128);

	if (memory != NULL) {
		s13HoudaiYokoCtor(memory, lbl_8042C110);
	}
}
