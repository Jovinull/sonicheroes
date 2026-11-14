// Opens the RenderWare module around 0x801B3414 once (HYPOTHESIS: a module "Open" routine, the
// counterpart of fn_801B3414): creates its shared handle (fn_801B7814), the 0x34-byte entry
// free list in the engine globals and initialises the remaining module globals. Returns 1 when
// it opened the module, 0 when it was already open or a creation failed (the handle is then
// released again).
#include "game/rw_module_801B3414.h"

extern "C" {
// .sdata parameters: handle argument, initial value of globals field 0x38, free-list entries
// per block and blocks to preallocate.
extern s32 lbl_8042BE90;
extern s32 lbl_8042BE94;
extern s32 lbl_8042BE98;
extern s32 lbl_8042BE9C;
// In-place free-list structure.
extern u8 lbl_803EDC40[];

// HYPOTHESIS: RwFreeListCreateAndPreallocateSpace.
RwFreeList* fn_801966CC(
    s32 entrySize, s32 entriesPerBlock, s32 alignment, s32 numBlocks, void* inPlace);
void fn_801B7940(void* list);

s32 fn_801B3474(void)
{
	if (lbl_8042CA88 == 0) {
		lbl_8042CA8C = fn_801B7814(lbl_8042BE90);
		if (!lbl_8042CA8C) {
			return 0;
		}
		RW_MODULE_801B3414_FREE_LIST
		    = fn_801966CC(0x34, lbl_8042BE98, 4, lbl_8042BE9C, lbl_803EDC40);
		if (!RW_MODULE_801B3414_FREE_LIST) {
			fn_801B7778(lbl_8042CA8C);
			lbl_8042CA8C = 0;
			return 0;
		}
		*(s32*)(RW_MODULE_801B3414_GLOBALS + 0x38) = lbl_8042BE94;
		fn_801B7940(RW_MODULE_801B3414_GLOBALS + 0x4);
		*(s32*)(RW_MODULE_801B3414_GLOBALS + 0x34) = 0;
		*(s32*)(RW_MODULE_801B3414_GLOBALS + 0x30) = 0;
		lbl_8042CA88                               = 1;
		return 1;
	}
	return 0;
}
}
