#include "types.h"

// TObjEnemyPawn::CreateInstance (the PS2 build's name): a new pawn under the
// object list's enemy root, or NULL when the heap is full.

extern "C" void* lbl_8042C10C;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* pawnCtor(void* object, void* owner);

extern "C" void* CreateInstance__13TObjEnemyPawnFv(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x390);

	if (memory != NULL) {
		memory = pawnCtor(memory, lbl_8042C10C);
	}
	return memory;
}
