// Releases the plugin data of object: runs fn_80197384 on its block at +0x14, releases every entry
// of the list at +0x64 that is in use (the body of fn_8015A58C, inlined) and clears the object's
// plugin slot (at the offset lbl_8042C91C). Names are UNKNOWN. Returns result.
#include "game/rw_engine.h"

struct Entry8015BA28 {
	RwLLLink link0; // 0x0
	void* f8;       // 0x8
	RwLLLink link1; // 0xC
	void* f14;      // 0x14
};

struct Object8015BA28 {
	u8 pad0[0x14];
	void* block; // 0x14
	u8 pad18[0x64 - 0x18];
	RwLinkList entries; // 0x64
};

extern "C" {
extern s32 lbl_8042C91C;
extern RwModuleInfo lbl_8042C928;
void fn_80197384(void* block);
}

// Same body as fn_8015A58C.
static inline void EntryReleaseIfUsed(Entry8015BA28* entry)
{
	if (entry->f8 != 0 && entry->f14 != 0) {
		RwLLLinkRemove(&entry->link1);
		RwLLLinkRemove(&entry->link0);
		lbl_8042C9A4->freeListFree(
		    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C928.globalsOffset), entry);
	}
}

extern "C" {
void* fn_8015BA28(void* result, Object8015BA28* object)
{
	s32 offset = lbl_8042C91C;
	RwLLLink* end;
	RwLLLink* cur;
	if (object->block != 0) {
		fn_80197384(object->block);
	}
	cur = object->entries.link.next;
	end = &object->entries.link;
	while (cur != end) {
		Entry8015BA28* entry = (Entry8015BA28*)((u8*)cur - 0xC);
		cur                  = cur->next;
		EntryReleaseIfUsed(entry);
	}
	*(void**)((u8*)object + offset) = 0;
	return result;
}
}
