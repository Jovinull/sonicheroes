// Opens the material module for one engine instance (HYPOTHESIS: the RpMaterial module "Open"
// routine, counterpart of fn_801547FC): records the module globals offset, creates the material
// free list (entry size from the material plugin registry lbl_8028D290) in the engine globals
// and counts the instance. Returns the instance, or null when the free list cannot be created.
// NonMatching: the retail code reads the registry size through its full address
// (lis/addi/lwz 0x0) where ours folds the low half into the load (one instruction shorter). The
// same form appears in every unmatched RenderWare module open routine; its cause is UNKNOWN.
#include "game/rw_engine.h"

extern "C" {
// Material module bookkeeping (HYPOTHESIS: materialModule) and plugin registry
// (materialTKList).
extern RwModuleInfo lbl_8042C8F8;
extern RwPluginRegistry lbl_8028D290;
// .sdata free-list parameters: entries per block and blocks to preallocate.
extern s32 lbl_8042BD08;
extern s32 lbl_8042BD0C;
// In-place free-list structure.
extern u8 lbl_803EC608[];

// HYPOTHESIS: RwFreeListCreateAndPreallocateSpace.
RwFreeList* fn_801966CC(
    s32 entrySize, s32 entriesPerBlock, s32 alignment, s32 numBlocks, void* inPlace);

#define RW_MATERIAL_FREE_LIST (*(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C8F8.globalsOffset))

void* fn_80154770(void* instance, s32 offset)
{
	lbl_8042C8F8.globalsOffset = offset;
	RW_MATERIAL_FREE_LIST
	    = fn_801966CC(lbl_8028D290.sizeOfStruct, lbl_8042BD08, 4, lbl_8042BD0C, lbl_803EC608);
	if (!RW_MATERIAL_FREE_LIST) {
		return 0;
	}
	lbl_8042C8F8.numInstances++;
	return instance;
}
}
