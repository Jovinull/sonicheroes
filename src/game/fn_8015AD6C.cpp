// Releases every entry linked into the list at +0x2C of the object (entries linked at +0xC) by
// unlinking it from both its lists and returning it to the free list at +0x4 of the module globals
// tracked by lbl_8042C928 (the body of fn_8015A51C, inlined). Names are UNKNOWN. Returns the
// object.
#include "game/rw_engine.h"

struct Entry8015AD6C {
	RwLLLink link0; // 0x0
	u8 pad8[0xC - 0x8];
	RwLLLink link1; // 0xC
};

struct Object8015AD6C {
	u8 pad0[0x2C];
	RwLinkList entries; // 0x2C
};

extern "C" {
extern RwModuleInfo lbl_8042C928;
}

// Same body as fn_8015A51C.
static inline void EntryRelease(Entry8015AD6C* entry)
{
	RwLLLinkRemove(&entry->link1);
	RwLLLinkRemove(&entry->link0);
	lbl_8042C9A4->freeListFree(
	    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C928.globalsOffset + 4), entry);
}

extern "C" {
Object8015AD6C* fn_8015AD6C(Object8015AD6C* object)
{
	RwLLLink* end = &object->entries.link;
	RwLLLink* cur = object->entries.link.next;
	while (cur != end) {
		Entry8015AD6C* entry = (Entry8015AD6C*)((u8*)cur - 0xC);
		cur                  = cur->next;
		EntryRelease(entry);
	}
	return object;
}
}
