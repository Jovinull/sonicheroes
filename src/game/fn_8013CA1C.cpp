// Gives the plugin slot of object (at the offset lbl_8042C818) a cleared block for count entries:
// the block header and one allocation holding count 0x40-byte entries followed by count words, both
// from the engine memory function. Names are UNKNOWN. Returns the object, or null when an allocation
// fails.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

struct Entry8013CA1C {
	u8 b[0x40];
};

struct Block8013CA1C {
	u32 count;              // 0x0
	Entry8013CA1C* entries; // 0x4
	u32* words;             // 0x8, follows the entries
};

extern "C" {
extern s32 lbl_8042C818;

void* fn_8013CA1C(void* object, u32 count)
{
	s32 offset;
	Entry8013CA1C* entries;
	u32 size;
	Block8013CA1C* block;
	offset = lbl_8042C818;
	block  = *(Block8013CA1C**)((u8*)object + offset)
	    = (Block8013CA1C*)lbl_8042C9A4->rwmalloc(sizeof(Block8013CA1C));
	if (block == 0) {
		return 0;
	}
	memset(block, 0, sizeof(Block8013CA1C));
	block->count = count;
	size         = count * (sizeof(Entry8013CA1C) + sizeof(u32));
	entries      = (Entry8013CA1C*)lbl_8042C9A4->rwmalloc(size);
	if (entries == 0) {
		lbl_8042C9A4->rwfree(block);
		return 0;
	}
	memset(entries, 0, size);
	block->entries = entries;
	block->words   = (u32*)(entries + count);
	return object;
}
}
