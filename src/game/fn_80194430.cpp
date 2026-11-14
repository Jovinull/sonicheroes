// Appends an entry to a growable array (HYPOTHESIS: _rwSListGetNewEntry): when it is full the
// storage grows by a quarter through the engine realloc function (on failure core error
// 0x80000013, out of memory, with the requested size, and null). Returns the new entry.
#include "game/rw_engine.h"

extern "C" {
void* fn_80194430(RwSList* sList)
{
	if (sList->numElementsFilled >= sList->numElementsAlloced) {
		u8* elements = (u8*)lbl_8042C9A4->rwrealloc(sList->listElements,
		    sList->entrySize * (sList->numElementsAlloced + sList->numElementsAlloced / 4));
		if (elements == 0) {
			RwError error;
			error.pluginID  = RW_ID_CORE_PLUGIN;
			error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY,
			    sList->entrySize * (sList->numElementsAlloced + sList->numElementsAlloced / 4));
			fn_80193FE8(&error);
			return 0;
		}
		sList->listElements = elements;
		sList->numElementsAlloced += sList->numElementsAlloced / 4;
	}
	{
		u8* entry = sList->listElements + sList->numElementsFilled * sList->entrySize;
		sList->numElementsFilled++;
		return entry;
	}
}
}
