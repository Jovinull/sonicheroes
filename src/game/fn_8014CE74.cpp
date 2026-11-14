// Closes the module around 0x8014A3A0 for one engine instance (HYPOTHESIS: a module "Close"
// routine): when the last instance closes, frees the engine heap blocks held in entries 10 down
// to 4 of the table lbl_803EC568 and the block lbl_8042C878, clearing each pointer. Returns the
// instance.
#include "game/rw_engine.h"

extern "C" {
// Module bookkeeping (only the instance count is used here).
extern RwModuleInfo lbl_8042C8A8;
// Heap blocks of the module (entries 0-3 are not released here).
extern void* lbl_803EC568[12];
extern void* lbl_8042C878;

void* fn_8014CE74(void* instance)
{
	if (--lbl_8042C8A8.numInstances == 0) {
		s32 i;
		for (i = 10; i >= 4; i--) {
			lbl_8042C9A4->rwfree(lbl_803EC568[i]);
			lbl_803EC568[i] = 0;
		}
		lbl_8042C9A4->rwfree(lbl_8042C878);
		lbl_8042C878 = 0;
	}
	return instance;
}
}
