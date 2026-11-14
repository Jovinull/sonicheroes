// Creates the heap used as the shared handle of the module around 0x801B3414 (HYPOTHESIS): the
// size is at least 0x400 bytes, rounded up to 32; the heap header (0x1C bytes) and its block
// (data aligned to 128 bytes inside an engine heap allocation) come from the engine allocator,
// and the new heap is initialised through fn_801B73B8. Returns the heap, or null when an
// allocation or the initialisation fails. Field names are inferred from this function only.
#include "game/rw_engine.h"

struct HeapBlock801B7814 {
	u8* data; // 0x0: 128-byte aligned start inside the allocation
	u32 size; // 0x4
	u32 used; // 0x8
};

struct Heap801B7814 {
	u32 size;                 // 0x0
	HeapBlock801B7814* block; // 0x4
	u32 word8;                // 0x8
	u32 wordC;                // 0xC
	u32 word10;               // 0x10
	u32 word14;               // 0x14
	s32 dirty;                // 0x18: set while fn_801B73B8 has to rebuild the heap
};

extern "C" {
s32 fn_801B73B8(Heap801B7814* heap);
}

static inline HeapBlock801B7814* HeapBlockCreate(u32 size)
{
	HeapBlock801B7814* block = (HeapBlock801B7814*)lbl_8042C9A4->rwmalloc(size + 0x8B);
	if (block) {
		block->data = (u8*)(((u32)block + 0x8B) & ~0x7F);
		block->size = size;
		block->used = 0;
	}
	return block;
}

static inline void HeapBlockDestroy(HeapBlock801B7814* block)
{
	if (block) {
		lbl_8042C9A4->rwfree(block);
	}
}

static inline s32 HeapUpdate(Heap801B7814* heap)
{
	if (heap->dirty == 0) {
		return 1;
	} else {
		return fn_801B73B8(heap);
	}
}

extern "C" {
Heap801B7814* fn_801B7814(u32 size)
{
	Heap801B7814* heap;
	HeapBlock801B7814* block;

	if (size < 0x400) {
		size = 0x400;
	}
	heap = (Heap801B7814*)lbl_8042C9A4->rwmalloc(sizeof(Heap801B7814));
	if (heap) {
		size = (size + 0x1F) & ~0x1F;
		if (size < 0x80) {
			size = 0x80;
		}
		block = HeapBlockCreate(size);
		if (block) {
			heap->size   = size;
			heap->block  = block;
			heap->wordC  = 0;
			heap->word10 = 0;
			heap->word14 = 0;
			heap->dirty  = 1;
			if (HeapUpdate(heap)) {
				return heap;
			}
			HeapBlockDestroy(block);
		}
		lbl_8042C9A4->rwfree(heap);
	}
	return 0;
}
}
