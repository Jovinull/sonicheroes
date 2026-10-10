#include "types.h"

// The factory rel/pepe_register.cpp puts in the pepe's editor record. The
// factory allocates 0x100 bytes and hands them to the module's constructor
// (left as assembly and named pepeCtor here, as rel/reel_assets.cpp names the
// reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* pepeCtor(void* object, void* owner);

extern "C" void pepeCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x100);

	if (memory != NULL) {
		pepeCtor(memory, lbl_8042C110);
	}
}
