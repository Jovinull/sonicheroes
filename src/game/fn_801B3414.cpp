// Closes the RenderWare module opened by fn_801B3474 (HYPOTHESIS: its "Close" routine): destroys
// the entry free list held in the engine globals and releases the shared handle. Always
// returns 1.
#include "game/rw_module_801B3414.h"

extern "C" {
s32 fn_801B3414(void)
{
	if (lbl_8042CA88 != 0) {
		RwFreeListDestroy(RW_MODULE_801B3414_FREE_LIST);
		RW_MODULE_801B3414_FREE_LIST = 0;
		fn_801B7778(lbl_8042CA8C);
		lbl_8042CA8C = 0;
		lbl_8042CA88 = 0;
	}
	return 1;
}
}
