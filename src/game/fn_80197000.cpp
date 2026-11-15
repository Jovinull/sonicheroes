// Closes the memory functions (HYPOTHESIS: _rwMemoryClose): destroys every free list still on the
// free-list list lbl_8042C968, then the free list of free lists lbl_8042C964 itself, and clears it
// and the enabled flag lbl_8042C960. The free-list destruction is RwFreeListDestroy inlined.
// NonMatching: as in RwFreeListDestroy, retail recomputes the block-list terminator from the free
// list pointer after each free while this source keeps it in a saved register, which shifts the
// register allocation of both inlined copies (101 words, two instructions). C mode does not help.
#include "game/rw_engine.h"

extern "C" {
extern s32 lbl_8042C960;
extern RwFreeList* lbl_8042C964;
extern RwLinkList lbl_8042C968;
}

// Unlinks a free list, frees its blocks and releases the header unless it is static (the body of
// RwFreeListDestroy).
static inline void DestroyFreeList80197000(RwFreeList* freeList)
{
	RwLLLink* block;

	RwLLLinkRemove(&freeList->link);
	block = freeList->blockList.link.next;
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
}

extern "C" {
void fn_80197000(void)
{
	while (lbl_8042C968.link.next != &lbl_8042C968.link) {
		DestroyFreeList80197000((RwFreeList*)((u8*)lbl_8042C968.link.next - 0x1C));
	}
	DestroyFreeList80197000(lbl_8042C964);
	lbl_8042C964 = 0;
	lbl_8042C960 = 0;
}
}
