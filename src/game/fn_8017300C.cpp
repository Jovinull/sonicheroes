// Returns an entry to the free list held at +0x1DC of the record lbl_803EC968 through the engine
// free-list function.
#include "game/rw_engine.h"

struct Rec8017300C {
	u8 pad0[0x1DC];
	RwFreeList* freeList; // 0x1DC
};

extern "C" {
extern Rec8017300C lbl_803EC968;

void fn_8017300C(void* entry)
{
	lbl_8042C9A4->freeListFree(lbl_803EC968.freeList, entry);
}
}
