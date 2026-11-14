// Tears down the named-entry list of the record lbl_803EC968: for every entry (list head +0x1D0,
// linked through +0x8) frees its name (+0x0) with the engine memory function, releases its value
// (+0x4) through fn_8016E230 and returns it to the entry free list (+0x1CC); then destroys that free
// list and the one at +0x148 and frees the buffer at +0xA0C. Names are UNKNOWN.
#include "game/rw_engine.h"

struct Entry8016DE10 {
	char* name;          // 0x0
	void* value;         // 0x4
	Entry8016DE10* next; // 0x8
};

struct Rec8016DE10 {
	u8 pad0[0x148];
	RwFreeList* freeList148; // 0x148
	u8 pad14C[0x1CC - 0x14C];
	RwFreeList* entryFreeList; // 0x1CC
	Entry8016DE10* entries;    // 0x1D0
	u8 pad1D4[0xA0C - 0x1D4];
	void* buffer; // 0xA0C
};

extern "C" {
extern Rec8016DE10 lbl_803EC968;
void fn_8016E230(void* value);

void fn_8016DE10(void)
{
	Rec8016DE10* rec     = &lbl_803EC968;
	Entry8016DE10* entry = rec->entries;
	while (entry != 0) {
		Entry8016DE10* next;
		lbl_8042C9A4->rwfree(entry->name);
		fn_8016E230(entry->value);
		next = entry->next;
		lbl_8042C9A4->freeListFree(rec->entryFreeList, entry);
		entry = next;
	}
	rec->entries = 0;
	RwFreeListDestroy(rec->entryFreeList);
	rec->entryFreeList = 0;
	RwFreeListDestroy(lbl_803EC968.freeList148);
	lbl_803EC968.freeList148 = 0;
	if (lbl_803EC968.buffer != 0) {
		lbl_8042C9A4->rwfree(lbl_803EC968.buffer);
	}
	lbl_803EC968.buffer = 0;
}
}
