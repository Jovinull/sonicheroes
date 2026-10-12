#include "types.h"

// The factory rel/s04_e_bubble_register.cpp puts in the s04EBubble's editor
// record. The factory allocates 0xFC bytes and hands them to the module's
// constructor (left as assembly and named s04EBubbleCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s04EBubbleCtor(void* object, void* owner);

extern "C" void s04EBubbleCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0xFC);

	if (memory != NULL) {
		s04EBubbleCtor(memory, lbl_8042C110);
	}
}
