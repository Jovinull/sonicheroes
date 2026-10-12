#include "types.h"

// The factory rel/s13_senkan_mov_register.cpp puts in the s13SenkanMov's editor
// record. The factory allocates 0xFC bytes and hands them to the module's
// constructor (left as assembly and named s13SenkanMovCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s13SenkanMovCtor(void* object, void* owner);

extern "C" void s13SenkanMovCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xFC);

	if (memory != NULL) {
		s13SenkanMovCtor(memory, lbl_8042C110);
	}
}
