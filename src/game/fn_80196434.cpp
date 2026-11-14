// Returns a matrix to the matrix free list of the current engine instance
// (HYPOTHESIS: RwMatrixDestroy). Always returns 1.
#include "game/rw_engine.h"

extern "C" {
// Matrix module bookkeeping (HYPOTHESIS: matrixModule).
extern RwModuleInfo lbl_8042C958;

s32 fn_80196434(RwMatrix* matrix)
{
	lbl_8042C9A4->freeListFree(
	    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C958.globalsOffset), matrix);
	return 1;
}
}
