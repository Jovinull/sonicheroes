#ifndef GAME_FREE_LISTS_8040EB50_H
#define GAME_FREE_LISTS_8040EB50_H

#include "game/rw_engine.h"

// Free lists of the module around 0x80201000-0x80206000 (.bss lbl_8040EB50, 0x30 bytes);
// fn_8020577C destroys the eleven lists. What each list holds is inferred from its users only.
struct FreeLists8040EB50 {
	RwFreeList* lists[11]; // 0x0
	u32 word2C;            // 0x2C (role UNKNOWN)
};

// Indices used by the reconstructed units.
#define FREE_LIST_8040EB50_BUFFER 5 // 0x14: 0x408-byte buffers (fn_802037C0, fn_80203844)
#define FREE_LIST_8040EB50_OBJECT 7 // 0x1C: objects of fn_80201498

extern "C" {
extern FreeLists8040EB50 lbl_8040EB50;
}

// 0x408-byte buffer of free list 5 and the object that owns one at 0x20 (fields inferred from
// fn_802037C0 and fn_80203844).
struct Buffer8040EB50 {
	u8 data[0x400];
	u32 used;  // 0x400
	u32 extra; // 0x404
};

struct BufferOwner8040EB50 {
	u8 pad0[0x20];
	Buffer8040EB50* buffer; // 0x20
};

#endif
