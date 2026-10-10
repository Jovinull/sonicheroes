#include "types.h"

// The factory rel/gokurakucho_register.cpp puts in the gokurakucho's editor
// record. The factory allocates 0xA0 bytes and hands them to the module's
// constructor (left as assembly and named gokurakuchoCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* gokurakuchoCtor(void* object, void* owner);

extern "C" void gokurakuchoCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xA0);

	if (memory != NULL) {
		gokurakuchoCtor(memory, lbl_8042C110);
	}
}
