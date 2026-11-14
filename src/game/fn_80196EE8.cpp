// Opens the memory functions of the engine (HYPOTHESIS: _rwMemoryOpen): creates the free list of
// free lists (0x24-byte entries, 16 per block, 32-byte aligned, in place at lbl_803ED440) after
// initialising the free-list list lbl_8042C968, and installs the given memory functions or the C
// library ones (malloc, free, realloc and the zeroing allocator fn_80196E98). Returns 1, or 0 when
// the free list cannot be created.
// NonMatching: the re-read of the new list pointer lands in r0 instead of r3 (2 words differ).
#include "game/rw_engine.h"

// Memory functions (HYPOTHESIS: RwMemoryFunctions).
struct RwMemoryFunctions80196EE8 {
	void* (*rwmalloc)(u32 size);
	void (*rwfree)(void* block);
	void* (*rwrealloc)(void* block, u32 size);
	void* (*rwcalloc)(u32 count, u32 size);
};

struct MemoryFunctionWords80196EE8 {
	u32 w[4];
};

// Free list header; only the list link is used here (HYPOTHESIS: RwFreeList).
struct FreeListHeader80196EE8 {
	u8 pad0[0x1C];
	RwLLLink link; // 0x1C
};

extern "C" {
// Free-list subsystem state: enabled flag, free list of free lists and list of free lists.
extern s32 lbl_8042C960;
extern FreeListHeader80196EE8* lbl_8042C964;
extern RwLinkList lbl_8042C968;
extern u8 lbl_803ED440[];

void* malloc(u32 size);
void free(void* block);
void* realloc(void* block, u32 size);
void* fn_80196E98(u32 count, u32 size);
// HYPOTHESIS: RwFreeListCreateAndPreallocateSpace with no preallocation.
FreeListHeader80196EE8* fn_8019650C(
    s32 entrySize, s32 entriesPerBlock, s32 alignment, s32 numBlocks, void* inPlace);
}

static inline s32 FreeListsOpen(void)
{
	lbl_8042C968.link.next = &lbl_8042C968.link;
	lbl_8042C968.link.prev = &lbl_8042C968.link;
	lbl_8042C960           = 1;
	lbl_8042C964           = fn_8019650C(0x24, 0x10, 0x20, 0, lbl_803ED440);
	if (!*(FreeListHeader80196EE8* volatile*)&lbl_8042C964) {
		lbl_8042C960 = 0;
		return 0;
	}
	// rwLinkListRemoveLLLink is a macro: the list pointer is re-read for each half.
	lbl_8042C964->link.prev->next = lbl_8042C964->link.next;
	lbl_8042C964->link.next->prev = lbl_8042C964->link.prev;
	return 1;
}

extern "C" {
s32 fn_80196EE8(const RwMemoryFunctions80196EE8* functions)
{
	if (!FreeListsOpen()) {
		return 0;
	}
	if (functions) {
		// The four engine memory function slots, copied as one block of words.
		*(MemoryFunctionWords80196EE8*)&lbl_8042C9A4->rwmalloc
		    = *(const MemoryFunctionWords80196EE8*)functions;
	} else {
		lbl_8042C9A4->rwmalloc  = malloc;
		lbl_8042C9A4->rwfree    = free;
		lbl_8042C9A4->rwrealloc = realloc;
		lbl_8042C9A4->rwcalloc  = fn_80196E98;
	}
	return 1;
}
}
