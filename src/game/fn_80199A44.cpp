// Allocates from a block heap (HYPOTHESIS: the RenderWare GameCube driver heap used by
// fn_801B7814): rounds the size up to 32 bytes, takes the smallest free block that fits and, when
// it is more than 64 bytes too large, splits the rest off as a new free block (merged with a free
// block that follows). Advances the heap's first-free pointer past used blocks when the chosen
// block was first. Returns the block data (0x20 bytes after its header), or null when nothing fits.
// Field names are inferred from this function only. The retail free test is written as
// (~used & 1), which the compiler keeps as nor/clrlwi.
// NonMatching: the rounded size and the walk pointer swap r6/r7 (24 words differ).
#include "types.h"

// Heap block header (0x20 bytes).
struct HeapBlock80199A44 {
	void* heap;              // 0x0
	HeapBlock80199A44* next; // 0x4
	HeapBlock80199A44* prev; // 0x8
	u32 size;                // 0xC
	u32 used;                // 0x10: bit 0
	u8 pad14[0xC];
};

struct Heap80199A44 {
	u8 pad0[0x4];
	HeapBlock80199A44* firstFree; // 0x4
};

extern "C" {
void* fn_80199A44(Heap80199A44* heap, u32 size)
{
	u32 rounded              = (size + 0x1F) & ~0x1F;
	HeapBlock80199A44* block = heap->firstFree;
	HeapBlock80199A44* best  = 0;

	for (; block; block = block->next) {
		if ((~block->used & 1) && block->size >= rounded && (!best || block->size < best->size)) {
			best = block;
		}
	}
	if (!best) {
		return 0;
	}

	if (best->size > rounded + 0x40) {
		HeapBlock80199A44* split = (HeapBlock80199A44*)((u8*)best + rounded + 0x20);
		HeapBlock80199A44* next  = best->next;
		if (next && (~next->used & 1)) {
			split->next = next->next;
			split->size = best->next->size + (best->size - rounded);
		} else {
			split->next = next;
			split->size = best->size - rounded - 0x20;
		}
		best->next  = split;
		split->used = 0;
		split->prev = best;
		if (split->next) {
			split->next->prev = split;
		}
		best->size  = rounded;
		split->heap = best->heap;
	}

	if (best == heap->firstFree) {
		do {
			heap->firstFree = heap->firstFree->next;
		} while (heap->firstFree && (heap->firstFree->used & 1));
	}
	best->used = 1;
	return (u8*)best + 0x20;
}
}
