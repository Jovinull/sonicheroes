#include "types.h"

// The factory rel/slotsmall_register.cpp puts in the slotsmall's editor record. The factory allocates 0x290 bytes and hands them to the module's constructor (left as assembly and named slotsmallCtor here, as rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* slotsmallCtor(void* object, void* owner);

extern "C" void slotsmallCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x290);

	if (memory != NULL) {
		slotsmallCtor(memory, lbl_8042C110);
	}
}
