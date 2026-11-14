// Calls a callback for every entry in use in a free list (HYPOTHESIS: RwFreeListForAllUsed): for
// each block, copies its in-use bitmap (heap block of the engine), then for every set bit calls
// the callback with the entry's address (entries start after the bitmap, aligned to the list
// alignment) and the user data. Returns the list, or null when the bitmap copy cannot be
// allocated.
// NonMatching: same 77 instructions, but the saved-register assignment of the 15 live values
// differs (37 words); declaration orders tried so far do not reproduce it.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

// Free list header (HYPOTHESIS: RwFreeList; fields used here only).
struct FreeList80196BCC {
	u32 entrySize;     // 0x0
	u32 entriesBlock;  // 0x4
	u32 heapSize;      // 0x8: bitmap bytes per block
	u32 alignment;     // 0xC
	RwLinkList blocks; // 0x10
};

typedef void (*FreeListCallBack80196BCC)(void* entry, void* data);

extern "C" {
FreeList80196BCC* fn_80196BCC(
    FreeList80196BCC* freeList, FreeListCallBack80196BCC callback, void* data)
{
	u8* src;
	RwLLLink* cur;
	u32 bit;
	u32 i;
	u8 value;
	u8* bits;
	RwLLLink* next;
	RwLLLink* end;
	u32 size;
	u8* base;
	u32 first;
	u32 index;

	size = freeList->heapSize;
	cur  = freeList->blocks.link.next;
	end  = &freeList->blocks.link;
	while (cur != end) {
		src  = (u8*)cur + sizeof(RwLLLink);
		bits = (u8*)lbl_8042C9A4->rwmalloc(size);
		if (!bits) {
			return 0;
		}
		memcpy(bits, src, size);
		next  = cur->next;
		src   = bits;
		base  = (u8*)cur + size;
		i     = 0;
		first = 0;
		for (; i < size; i++) {
			value = *src;
			if (value) {
				index = first;
				for (bit = 0; bit < 8; bit++) {
					if (value & (u8)(0x80 >> bit)) {
						callback((u8*)((u32)(base + freeList->alignment + 7)
						             & ~(freeList->alignment - 1))
						        + freeList->entrySize * index,
						    data);
					}
					index++;
				}
			}
			first += 8;
			src++;
		}
		lbl_8042C9A4->rwfree(bits);
		cur = next;
	}
	return freeList;
}
}
