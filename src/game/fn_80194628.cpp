// Destroys a growable array (HYPOTHESIS: _rwSListDestroy): frees its element storage when it has
// any allocated, then the array header, with the engine memory function. Always returns 1.
#include "game/rw_engine.h"

extern "C" {
s32 fn_80194628(RwSList* sList)
{
	if (sList->listElements != 0 && sList->numElementsAlloced != 0) {
		lbl_8042C9A4->rwfree(sList->listElements);
		sList->listElements       = 0;
		sList->numElementsAlloced = 0;
	}
	lbl_8042C9A4->rwfree(sList);
	return 1;
}
}
