// Releases an entry of the record lbl_803EC968's free list (+0x1D4): its payload (+0x0) is
// destroyed as a growable array through fn_80194628 (_rwSListDestroy) when the entry's count (+0x4)
// is -1 and freed with the engine memory function otherwise; then the entry goes back to the free
// list. Names are UNKNOWN. Returns the next entry (+0x14).
#include "game/rw_engine.h"

struct Entry8016FBA0 {
	void* payload; // 0x0
	s32 count;     // 0x4
	u8 pad8[0x14 - 0x8];
	Entry8016FBA0* next; // 0x14
};

struct Rec8016FBA0 {
	u8 pad0[0x1D4];
	RwFreeList* freeList; // 0x1D4
};

extern "C" {
extern Rec8016FBA0 lbl_803EC968;
s32 fn_80194628(RwSList* sList);

Entry8016FBA0* fn_8016FBA0(Entry8016FBA0* entry)
{
	Entry8016FBA0* next = entry->next;
	if (entry->payload != 0) {
		if (entry->count == -1) {
			fn_80194628((RwSList*)entry->payload);
		} else {
			lbl_8042C9A4->rwfree(entry->payload);
		}
	}
	entry->payload = 0;
	lbl_8042C9A4->freeListFree(lbl_803EC968.freeList, entry);
	return next;
}
}
