// Closes the resource arena (HYPOTHESIS: the RenderWare resources "Close" routine): when the
// 0x3C-byte entry free list lbl_8042C988 exists, restores every used entry through fn_801988BC;
// with a custom free-list allocator installed (not fn_80196878) it also releases the entry chain
// of every arena in lbl_8042C980 (count lbl_8042C984), restoring the record of each chain's head,
// and frees the arena table. Then destroys the free list. Always returns 1. Field names are
// inferred from these functions only.
#include "game/rw_engine.h"

// Record linked from an entry (same layout as in fn_801988BC).
struct Record80198920 {
	void* current; // 0x0
	void* saved;   // 0x4
	u8 pad8[0x8];
	void* user;  // 0x10
	void* extra; // 0x14
};

struct Entry80198920 {
	u8 pad0[0x30];
	Entry80198920* next; // 0x30
	u8 pad34[0x4];
	Record80198920* record; // 0x38
};

struct Arena80198920 {
	u8 pad0[0x10];
	Entry80198920* entries; // 0x10
};

extern "C" {
extern RwFreeList* lbl_8042C988;
extern Arena80198920** lbl_8042C980;
extern u32 lbl_8042C984;

void fn_801988BC(void* entry, void* data);
void* fn_80196878(RwFreeList* freeList);
void* fn_80196BCC(RwFreeList* freeList, void (*callback)(void*, void*), void* data);

s32 fn_80198920(void)
{
	if (lbl_8042C988) {
		fn_80196BCC(lbl_8042C988, fn_801988BC, lbl_8042C988);
		if (lbl_8042C9A4->freeListAlloc != fn_80196878) {
			u32 i;
			for (i = 0; i < lbl_8042C984; i++) {
				Entry80198920* entry   = lbl_8042C980[i]->entries;
				Record80198920* record = 0;
				if (entry) {
					record = entry->record;
				}
				while (entry) {
					Entry80198920* next = entry->next;
					lbl_8042C9A4->freeListFree(0, entry);
					entry = next;
				}
				if (record && record->user) {
					record->current = record->saved;
					record->user    = 0;
					record->extra   = 0;
				}
			}
			if (lbl_8042C980) {
				lbl_8042C9A4->rwfree(lbl_8042C980);
				lbl_8042C980 = 0;
			}
		}
		RwFreeListDestroy(lbl_8042C988);
		lbl_8042C988 = 0;
	}
	return 1;
}
}
