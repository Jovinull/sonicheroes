// Unlinks a free list from the engine list, frees every block it owns and releases the header
// unless it is static (HYPOTHESIS: RenderWare RwFreeListDestroy). NonMatching: retail
// rematerialises the block-list terminator (freeList + 0x10) in a volatile register before each
// loop test, while this source keeps it in a saved register (r30/r31), which shifts the register
// allocation (32 words differ, one extra instruction). Tried a while on the head pointer, explicit
// head re-reads, inline first/terminator helpers, a pre-computed terminator and compilers GC/1.0 to
// 2.7.

#include "game/rw_engine.h"

extern "C" {
// Free list that holds the RwFreeList headers themselves (HYPOTHESIS).
extern RwFreeList* lbl_8042C964;

s32 RwFreeListDestroy(RwFreeList* freeList)
{
	RwLLLinkRemove(&freeList->link);

	RwLLLink* block = freeList->blockList.link.next;
	while (block != &freeList->blockList.link) {
		RwLLLinkRemove(block);
		lbl_8042C9A4->rwfree(block);
		block = freeList->blockList.link.next;
	}

	if (!(freeList->flags & RW_FREE_LIST_STATIC)) {
		if (lbl_8042C964 == freeList || lbl_8042C964 == 0) {
			lbl_8042C9A4->rwfree(freeList);
		} else {
			lbl_8042C9A4->freeListFree(lbl_8042C964, freeList);
		}
	}
	return 1;
}
}
