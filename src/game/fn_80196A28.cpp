// Returns an entry to a free list (HYPOTHESIS: RwFreeListFree): finds the block whose entry range
// holds the entry (a block is its link, a heapSize-byte usage bitmap, then the entries), clears
// the entry's bit, and when the free list releases empty blocks (flag 0x2) frees a block whose
// bitmap is all clear unless it is the only block. Returns the free list, or null when no block
// holds the entry.
// NonMatching: retail reads heapSize once before the block loop and forms the bit index as
// index - (index & ~7); this source reloads heapSize per block and the compiler folds the bit
// index to index & 7, which shifts the register use (61 words). A cached heapSize gets its
// offset hoisted instead (88 words); C mode and explicit byte/bit locals do not help.
#include "game/rw_engine.h"

#define RW_FREE_LIST_FREE_BLOCKS 0x2

extern "C" {
RwFreeList* fn_80196A28(RwFreeList* freeList, void* entry)
{
	RwLLLink* end = &freeList->blockList.link;
	RwLLLink* cur;

	for (cur = freeList->blockList.link.next; cur != end; cur = cur->next) {
		u8* entries = (u8*)cur + (freeList->heapSize + sizeof(RwLLLink));
		if ((u8*)entry >= entries
		    && (u8*)entry <= entries + freeList->entriesPerBlock * freeList->entrySize) {
			u32 index  = ((u8*)entry - entries) / freeList->entrySize;
			u8* bitmap = (u8*)cur + sizeof(RwLLLink);
			bitmap[index / 8] &= (u8) ~(u8)(0x80 >> (index % 8));
			if (freeList->flags & RW_FREE_LIST_FREE_BLOCKS) {
				u32 used = 0;
				u32 i;
				for (i = 0; i < freeList->heapSize; i++) {
					used += bitmap[i];
				}
				if (used == 0 && !(cur == freeList->blockList.link.next && cur->next == end)) {
					RwLLLinkRemove(cur);
					lbl_8042C9A4->rwfree(cur);
				}
			}
			return freeList;
		}
	}
	return 0;
}
}
