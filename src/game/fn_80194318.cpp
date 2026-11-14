// Creates a growable array of entrySize-byte entries with room for 20 (HYPOTHESIS: _rwSListCreate).
// Either allocation failing records core error 0x80000013 (out of memory, with the requested size)
// and returns null, releasing the header if it was allocated. Returns the array.
#include "game/rw_engine.h"

#define RW_SLIST_INITIAL_ENTRIES 20

extern "C" {
RwSList* fn_80194318(s32 entrySize)
{
	RwSList* sList = (RwSList*)lbl_8042C9A4->rwmalloc(sizeof(RwSList));
	if (sList == 0) {
		RwError error;
		error.pluginID  = RW_ID_CORE_PLUGIN;
		error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, sizeof(RwSList));
		fn_80193FE8(&error);
		return 0;
	}
	sList->numElementsFilled  = 0;
	sList->numElementsAlloced = RW_SLIST_INITIAL_ENTRIES;
	sList->entrySize          = entrySize;
	sList->listElements = (u8*)lbl_8042C9A4->rwmalloc(sList->numElementsAlloced * sList->entrySize);
	if (sList->listElements == 0) {
		RwError error;
		error.pluginID = RW_ID_CORE_PLUGIN;
		error.errorCode
		    = fn_8019408C(RW_ERROR_NO_MEMORY, sList->numElementsAlloced * sList->entrySize);
		fn_80193FE8(&error);
		lbl_8042C9A4->rwfree(sList);
		return 0;
	}
	return sList;
}
}
