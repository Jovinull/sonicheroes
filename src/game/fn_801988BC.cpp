// Free-list walk callback used by fn_80198920 over the 0x3C-byte entries of the free list
// lbl_8042C988 (fn_80196BCC is the walker; HYPOTHESIS: RwFreeListForAllUsed): when the entry's
// linked record is in use (word 0x10 set), restores its word 0x0 from word 0x4 and clears words
// 0x10 and 0x14, then returns the entry to the free list.
#include "game/rw_engine.h"

// Record linked from an entry (layout inferred from this function only).
struct Record801988BC {
	void* current; // 0x0
	void* saved;   // 0x4
	u8 pad8[0x8];
	void* user;  // 0x10
	void* extra; // 0x14
};

struct Entry801988BC {
	u8 pad0[0x38];
	Record801988BC* record; // 0x38
};

extern "C" {
void fn_801988BC(Entry801988BC* entry, RwFreeList* freeList)
{
	Record801988BC* record = entry->record;

	if (record->user) {
		record->current      = record->saved;
		entry->record->user  = 0;
		entry->record->extra = 0;
	}
	lbl_8042C9A4->freeListFree(freeList, entry);
}
}
