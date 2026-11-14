// Frees the buffer at +0x8 of the entry with the engine memory function and returns the entry to
// the free list lbl_8042BD10. Always returns 1. Names are UNKNOWN.
#include "game/rw_engine.h"

struct Entry8015597C {
	u8 pad0[0x8];
	void* buffer; // 0x8
};

extern "C" {
extern RwFreeList* lbl_8042BD10;

s32 fn_8015597C(Entry8015597C* entry)
{
	if (entry->buffer != 0) {
		lbl_8042C9A4->rwfree(entry->buffer);
		entry->buffer = 0;
	}
	lbl_8042C9A4->freeListFree(lbl_8042BD10, entry);
	return 1;
}
}
