// Appends count entries to a growable array (HYPOTHESIS:
// _rwSListGetNewEntries): when they do not fit, the storage grows to the old
// capacity plus count plus a quarter through the engine realloc function (on
// failure core error 0x80000013, out of memory, with the requested size, and
// null). Returns the first new entry.
#include "game/rw_engine.h"

extern "C" {
void* fn_80194510(RwSList* sList, s32 count)
{
	if (sList->numElementsFilled + count >= sList->numElementsAlloced) {
		u8* elements = (u8*)lbl_8042C9A4->rwrealloc(sList->listElements,
		    sList->entrySize * (sList->numElementsAlloced + count + sList->numElementsAlloced / 4));
		if (elements == 0) {
			RwError error;
			error.pluginID  = RW_ID_CORE_PLUGIN;
			error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY,
			    sList->entrySize
			        * (sList->numElementsAlloced + count + sList->numElementsAlloced / 4));
			fn_80193FE8(&error);
			return 0;
		}
		sList->listElements = elements;
		sList->numElementsAlloced
		    = sList->numElementsAlloced + count + sList->numElementsAlloced / 4;
	}
	{
		u8* entry = sList->listElements + sList->numElementsFilled * sList->entrySize;
		sList->numElementsFilled += count;
		return entry;
	}
}
}
