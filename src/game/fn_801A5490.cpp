// Takes an entry from a free list through the engine memory function
// (HYPOTHESIS: RwFreeListAlloc wrapper). Returns the entry, or null.
#include "game/rw_engine.h"

extern "C" {
void* fn_801A5490(RwFreeList* freeList)
{
	return lbl_8042C9A4->freeListAlloc(freeList);
}
}
