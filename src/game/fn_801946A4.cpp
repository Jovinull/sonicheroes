// Releases a growable array header and hands its element storage to the caller
// (HYPOTHESIS: _rwSListToArray): returns the storage when the array holds entries; an empty
// array's storage is freed and null is returned.
#include "game/rw_engine.h"

extern "C" {
void* fn_801946A4(RwSList* sList)
{
	void* array = 0;
	if (sList->numElementsFilled != 0) {
		array = sList->listElements;
	} else if (sList->listElements != 0) {
		lbl_8042C9A4->rwfree(sList->listElements);
		sList->listElements = 0;
		array               = 0;
	}
	lbl_8042C9A4->rwfree(sList);
	return array;
}
}
