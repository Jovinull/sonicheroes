// Plugin destructor of the atomic extension (offset lbl_8042C91C): releases every entry of the list
// at +0x64 that is in use (the body of fn_8015A58C, inlined) and restores the atomic's callback at
// +0x10 from the copy saved at +0x4 of the extension. Names are UNKNOWN. Returns the atomic.
#include "game/rw_engine.h"

struct Entry8015A928 {
	RwLLLink link0; // 0x0
	void* f8;       // 0x8
	RwLLLink link1; // 0xC
	void* f14;      // 0x14
};

struct Ext8015A928 {
	s32 f0;
	void* savedCallback; // 0x4
};

struct Atomic8015A928 {
	u8 pad0[0x10];
	void* callback; // 0x10
	u8 pad14[0x64 - 0x14];
	RwLinkList entries; // 0x64
};

extern "C" {
extern s32 lbl_8042C91C;
extern RwModuleInfo lbl_8042C928;
}

// Same body as fn_8015A58C.
static inline void EntryReleaseIfUsed(Entry8015A928* entry)
{
	if (entry->f8 != 0 && entry->f14 != 0) {
		RwLLLinkRemove(&entry->link1);
		RwLLLinkRemove(&entry->link0);
		lbl_8042C9A4->freeListFree(
		    *(RwFreeList**)((u8*)lbl_8042C9A4 + lbl_8042C928.globalsOffset), entry);
	}
}

extern "C" {
Atomic8015A928* fn_8015A928(Atomic8015A928* atomic)
{
	RwLLLink* end    = &atomic->entries.link;
	RwLLLink* cur    = atomic->entries.link.next;
	Ext8015A928* ext = (Ext8015A928*)((u8*)atomic + lbl_8042C91C);
	while (cur != end) {
		Entry8015A928* entry = (Entry8015A928*)((u8*)cur - 0xC);
		cur                  = cur->next;
		EntryReleaseIfUsed(entry);
	}
	atomic->callback = ext->savedCallback;
	return atomic;
}
}
