// Releases the entries linked into the list at +0x2C of object: clears the object's plugin slot
// (at the offset lbl_8042C924), unlinks every entry from both its lists and returns it to the free
// list at +0x4 of the module globals tracked by lbl_8042C928 (the body of fn_8015A51C, inlined), then
// unlinks the object's own link at +0x34. Names are UNKNOWN. Returns result.
#include "game/rw_engine.h"

struct Entry8015BE24 {
	RwLLLink link0; // 0x0
	u8 pad8[0xC - 0x8];
	RwLLLink link1; // 0xC
};

struct Object8015BE24 {
	u8 pad0[0x2C];
	RwLinkList entries; // 0x2C
	RwLLLink link;      // 0x34
};

extern "C" {
extern s32 lbl_8042C924;
extern RwModuleInfo lbl_8042C928;
}

// Same body as fn_8015A51C.
static inline void EntryRelease(Entry8015BE24* entry)
{
	RwLLLinkRemove(&entry->link1);
	RwLLLinkRemove(&entry->link0);
	lbl_8042C9A4->freeListFree(
	    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C928.globalsOffset + 4), entry);
}

extern "C" {
void* fn_8015BE24(void* result, Object8015BE24* object)
{
	RwLLLink* end = &object->entries.link;
	RwLLLink* cur;
	*(void**)((u8*)object + lbl_8042C924) = 0;
	cur                                   = object->entries.link.next;
	while (cur != end) {
		Entry8015BE24* entry = (Entry8015BE24*)((u8*)cur - 0xC);
		cur                  = cur->next;
		EntryRelease(entry);
	}
	RwLLLinkRemove(&object->link);
	return result;
}
}
