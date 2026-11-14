// Allocates a matrix from the matrix free list and initializes it to the orthonormal identity
// (HYPOTHESIS: RwMatrixCreate). Returns null when allocation fails.
#include "game/rw_engine.h"

extern "C" {
// Matrix module bookkeeping (HYPOTHESIS: matrixModule).
extern RwModuleInfo lbl_8042C958;
// .sdata2 constants 1.0f and 0.0f of the matrix code (non-const: see RW_MATRIX_SET_IDENTITY).
extern f32 lbl_8042F694;
extern f32 lbl_8042F690;

RwMatrix* fn_80196470(void)
{
	RwMatrix* matrix = (RwMatrix*)lbl_8042C9A4->freeListAlloc(
	    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C958.globalsOffset));
	if (matrix != 0) {
		matrix->flags = RW_MATRIX_TYPE_ORTHONORMAL;
		RW_MATRIX_SET_IDENTITY(matrix, lbl_8042F694, lbl_8042F690);
	}
	return matrix;
}
}
