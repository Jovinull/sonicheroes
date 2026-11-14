// Unlinks an entry from both lists it belongs to (links at +0xC and +0x0) and returns it to the
// free list at +0x4 of the module globals tracked by lbl_8042C928. Always returns 1. Names are
// UNKNOWN.
#include "game/rw_engine.h"

struct Entry8015A51C {
	RwLLLink link0; // 0x0
	u8 pad8[0xC - 0x8];
	RwLLLink link1; // 0xC
};

extern "C" {
extern RwModuleInfo lbl_8042C928;

s32 fn_8015A51C(Entry8015A51C* entry)
{
	RwLLLinkRemove(&entry->link1);
	RwLLLinkRemove(&entry->link0);
	lbl_8042C9A4->freeListFree(
	    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C928.globalsOffset + 4), entry);
	return 1;
}
}
