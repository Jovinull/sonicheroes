#include "types.h"

// The factory rel/s13_houdai_register.cpp puts in the s13HoudaiFix family's
// editor record. The factory allocates 0x140 bytes and hands them to the
// constructor it shares with its sibling objects (left as assembly and named
// s13HoudaiCtor here), as kind 2.

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s13HoudaiCtor(void* object, void* owner, s32 kind);

extern "C" void s13HoudaiFixCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x140);

	if (memory != NULL) {
		s13HoudaiCtor(memory, lbl_8042C110, 2);
	}
}
