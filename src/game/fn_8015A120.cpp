// Opens the world module for one engine instance (HYPOTHESIS: the RpWorld module "Open" routine):
// records the globals offset, creates the two 0x18-byte free lists of the module globals (the
// second at 0x4; the first is destroyed again when the second cannot be created), resets the
// engine render frame counter to 1 and the module word at 0x8, and counts the instance. Returns
// the instance, or null on failure.
// NonMatching: for the first free list the retail code sets up the constant arguments before the
// in-place list address; ours computes that address first (7 words differ).
#include "game/rw_engine.h"

extern "C" {
// World module bookkeeping (HYPOTHESIS: worldModule).
extern RwModuleInfo lbl_8042C928;
// .sdata free-list parameters (entries per block, blocks to preallocate) and in-place free-list
// structures of the two lists.
extern s32 lbl_8042BD18;
extern s32 lbl_8042BD1C;
extern s32 lbl_8042BD20;
extern s32 lbl_8042BD24;
extern u8 lbl_803EC658[];
extern u8 lbl_803EC67C[];

// HYPOTHESIS: RwFreeListCreateAndPreallocateSpace.
RwFreeList* fn_801966CC(
    s32 entrySize, s32 entriesPerBlock, s32 alignment, s32 numBlocks, void* inPlace);
}

#define RW_WORLD_GLOBAL(type, offset)                                                              \
	(*(type*)((u8*)lbl_8042C9A4 + lbl_8042C928.globalsOffset + (offset)))

extern "C" {
void* fn_8015A120(void* instance, s32 offset)
{
	lbl_8042C928.globalsOffset = offset;
	RW_WORLD_GLOBAL(RwFreeList*, 0x0)
	    = fn_801966CC(0x18, lbl_8042BD18, 4, lbl_8042BD1C, lbl_803EC658);
	if (!RW_WORLD_GLOBAL(RwFreeList*, 0x0)) {
		return 0;
	}
	RW_WORLD_GLOBAL(RwFreeList*, 0x4)
	    = fn_801966CC(0x18, lbl_8042BD20, 4, lbl_8042BD24, lbl_803EC67C);
	if (!RW_WORLD_GLOBAL(RwFreeList*, 0x4)) {
		RwFreeListDestroy(RW_WORLD_GLOBAL(RwFreeList*, 0x0));
		RW_WORLD_GLOBAL(RwFreeList*, 0x0) = 0;
		return 0;
	}
	lbl_8042C9A4->renderFrame   = 1;
	RW_WORLD_GLOBAL(void*, 0x8) = 0;
	lbl_8042C928.numInstances++;
	return instance;
}
}
