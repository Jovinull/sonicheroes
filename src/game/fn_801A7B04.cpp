// Releases a palette quantizer (HYPOTHESIS: _rwPalQuantTerm): deletes its colour tree, destroys
// the node free list and frees its two heap blocks.
#include "game/rw_palquant.h"

extern "C" {
void fn_801A7B04(RwPalQuant* quant)
{
	fn_801A77E0(quant, quant->root, lbl_8042BE60);
	quant->root = 0;
	RwFreeListDestroy(quant->nodeFreeList);
	lbl_8042C9A4->rwfree(quant->buffer4);
	lbl_8042C9A4->rwfree(quant->buffer0);
}
}
