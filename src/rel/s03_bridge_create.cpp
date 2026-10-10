#include "types.h"

// The factory rel/s03_bridge_register.cpp puts in the s03Bridge's editor
// record. The factory allocates 0x10C bytes and hands them to the module's
// constructor (left as assembly and named s03BridgeCtor here, as
// rel/reel_assets.cpp names the reel's).

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* s03BridgeCtor(void* object, void* owner);

extern "C" void s03BridgeCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x10C);

	if (memory != NULL) {
		s03BridgeCtor(memory, lbl_8042C110);
	}
}
