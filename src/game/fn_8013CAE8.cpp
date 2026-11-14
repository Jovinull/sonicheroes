// Releases the block referenced from the plugin slot of object (at the offset lbl_8042C818): runs
// fn_8013CB88 for each of its entries (count at +0x0), frees its entry array (+0x4) and the block
// itself with the engine memory function and clears the slot. Names are UNKNOWN. Returns the
// object.
#include "game/rw_engine.h"

struct Block8013CAE8 {
	u32 count;     // 0x0
	void* entries; // 0x4
};

extern "C" {
extern s32 lbl_8042C818;
void fn_8013CB88(void* object, u32 index);

void* fn_8013CAE8(void* object)
{
	s32 offset           = lbl_8042C818;
	Block8013CAE8* block = *(Block8013CAE8**)((u8*)object + offset);
	u32 i;
	for (i = 0; i < block->count; i++) {
		fn_8013CB88(object, i);
	}
	lbl_8042C9A4->rwfree(block->entries);
	lbl_8042C9A4->rwfree(block);
	*(Block8013CAE8**)((u8*)object + offset) = 0;
	return object;
}
}
