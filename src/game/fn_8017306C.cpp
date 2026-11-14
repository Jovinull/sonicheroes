// Takes an entry from the free list held at +0x1DC of the record lbl_803EC968 through the engine
// free-list function. Returns the entry, or null.
#include "game/rw_engine.h"

struct Rec8017306C {
	u8 pad0[0x1DC];
	RwFreeList* freeList; // 0x1DC
};

extern "C" {
extern Rec8017306C lbl_803EC968;

void* fn_8017306C(void)
{
	return lbl_8042C9A4->freeListAlloc(lbl_803EC968.freeList);
}
}
