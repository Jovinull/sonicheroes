// When the entry is in use (+0x8 and +0x14 set), unlinks it from both lists it belongs to (links at
// +0xC and +0x0) and returns it to the free list at the start of the module globals tracked by
// lbl_8042C928. Always returns 1. Names are UNKNOWN.
#include "game/rw_engine.h"

struct Entry8015A58C {
	RwLLLink link0; // 0x0
	void* f8;       // 0x8
	RwLLLink link1; // 0xC
	void* f14;      // 0x14
};

extern "C" {
extern RwModuleInfo lbl_8042C928;

s32 fn_8015A58C(Entry8015A58C* entry)
{
	if (entry->f8 != 0 && entry->f14 != 0) {
		RwLLLinkRemove(&entry->link1);
		RwLLLinkRemove(&entry->link0);
		lbl_8042C9A4->freeListFree(
		    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C928.globalsOffset), entry);
	}
	return 1;
}
}
