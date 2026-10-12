#include "types.h"

// The factory rel/s13_houdai_l_register.cpp puts in the s13HoudaiL's editor
// record. The factory allocates 0x13C bytes and hands them to the module's
// constructor (left as assembly and named s13HoudaiLCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s13HoudaiLCtor(void* object, void* owner);

extern "C" void s13HoudaiLCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x13C);

	if (memory != NULL) {
		s13HoudaiLCtor(memory, lbl_8042C110);
	}
}
