#include "types.h"

// TObjEnemySearcher::CreateInstance (the PS2 build's name): allocates 0x348
// bytes and constructs a searcher in them (the module's constructor, left as
// assembly and named searcherObjectCtor here), owned by the task at
// lbl_8042C10C; returns it.

extern "C" void* lbl_8042C10C;
extern "C" void* lbl_8042C148;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void* searcherObjectCtor(void* object, void* owner);

extern "C" void* CreateInstance__17TObjEnemySearcherFv(void)
{
	void* memory = Malloc__9THeapCtrlFUi(lbl_8042C148, 0x348);

	if (memory != NULL) {
		memory = searcherObjectCtor(memory, lbl_8042C10C);
	}
	return memory;
}
