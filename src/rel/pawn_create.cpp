#include "types.h"

// The factory rel/pawn_assets.cpp puts in the pawn's editor record. The factory
// allocates 0x390 bytes and hands them to the module's constructor (left as
// assembly and named pawnCtor here, as rel/reel_assets.cpp names the reel's),
// with the task at lbl_8042C10C as its owner.

extern "C" void* lbl_8042C10C;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* pawnCtor(void* object, void* owner);

extern "C" void pawnCreate(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x390);

	if (memory != NULL) {
		pawnCtor(memory, lbl_8042C10C);
	}
}
