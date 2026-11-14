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

// 16-byte command stored in a buffer (only the type and the word at 0x4 are interpreted).
struct BufferCommand8040EB50 {
	s32 type;  // 0x0
	s32 value; // 0x4
	u32 word8; // 0x8
	u32 wordC; // 0xC
};

// 0x408-byte buffer of free list 5 holding up to 64 commands, and the object that owns one at
// 0x20 (fields inferred from fn_802037C0, fn_80203844 and fn_8020366C).
struct Buffer8040EB50 {
	BufferCommand8040EB50 commands[64]; // 0x0
	u32 word400;                        // 0x400 (role UNKNOWN)
	s32 count;                          // 0x404: commands in use
};

struct BufferOwner8040EB50 {
	u8 pad0[0x20];
	Buffer8040EB50* buffer; // 0x20
};

#endif
