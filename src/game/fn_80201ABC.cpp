// Takes an entry from the free list at +0x1C of the record lbl_8040EB50 through the engine free-list
// function and hands it to fn_80201528 together with object. Names are UNKNOWN.
#include "game/rw_engine.h"

struct Rec80201ABC {
	u8 pad0[0x1C];
	RwFreeList* freeList; // 0x1C
};

extern "C" {
extern Rec80201ABC lbl_8040EB50;
void fn_80201528(void* object, void* entry);

void fn_80201ABC(void* object)
{
	void* entry;
	entry = lbl_8042C9A4->freeListAlloc(lbl_8040EB50.freeList);
	fn_80201528(object, entry);
}
}
