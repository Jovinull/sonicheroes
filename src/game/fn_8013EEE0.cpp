// Releases an entry of the frame plugin with ID 0x11E: unless flag bit 0 says the buffers are
// borrowed it frees the buffer at +0x10 and, unless flag bit 1 is set, the one at +0xC; clears both
// and the word at +0x8, frees the block at +0x20 through fn_8020C700, returns the entry to the
// plugin free list (second word of lbl_8042C828) and clears the back-pointer in its owner's plugin
// data (+0x4 at the offset lbl_8042C828). Names are UNKNOWN. Always returns 0.
#include "game/rw_engine.h"

struct Entry8013EEE0 {
	u32 flags; // 0x0
	s32 f4;
	void* f8;       // 0x8
	void* bufferC;  // 0xC
	void* buffer10; // 0x10
	u8* owner;      // 0x14
	u8 pad18[0x20 - 0x18];
	void* block20; // 0x20
};

// Frame plugin bookkeeping: extension offset, then the entry free list.
struct Plugin8013EEE0 {
	s32 offset;
	RwFreeList* freeList;
};

extern "C" {
extern Plugin8013EEE0 lbl_8042C828;
void fn_8020C700(void* block);

s32 fn_8013EEE0(Entry8013EEE0* entry)
{
	u8* owner = entry->owner;
	if (!(entry->flags & 1)) {
		if (!(entry->flags & 2)) {
			lbl_8042C9A4->rwfree(entry->bufferC);
		}
		lbl_8042C9A4->rwfree(entry->buffer10);
	}
	entry->bufferC  = 0;
	entry->f8       = 0;
	entry->buffer10 = 0;
	fn_8020C700(entry->block20);
	lbl_8042C9A4->freeListFree(lbl_8042C828.freeList, entry);
	if (owner != 0) {
		*(Entry8013EEE0**)(owner + lbl_8042C828.offset + 4) = 0;
	}
	return 0;
}
}
