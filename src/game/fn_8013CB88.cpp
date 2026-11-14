// Clears entry index of the block referenced from the plugin slot of object (at the offset
// lbl_8042C818): frees its three buffers (+0x4, +0x10, +0x1C) with the engine memory function and
// zeroes the 0x40-byte entry. Names are UNKNOWN. Returns the object.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

struct Entry8013CB88 {
	s32 f0;
	void* buffer4; // 0x4
	u8 pad8[0x10 - 0x8];
	void* buffer10; // 0x10
	u8 pad14[0x1C - 0x14];
	void* buffer1C; // 0x1C
	u8 pad20[0x40 - 0x20];
};

struct Block8013CB88 {
	u32 count;              // 0x0
	Entry8013CB88* entries; // 0x4
};

extern "C" {
extern s32 lbl_8042C818;

void* fn_8013CB88(void* object, u32 index)
{
	Entry8013CB88* entry = &(*(Block8013CB88**)((u8*)object + lbl_8042C818))->entries[index];
	if (entry->buffer4 != 0) {
		lbl_8042C9A4->rwfree(entry->buffer4);
	}
	if (entry->buffer10 != 0) {
		lbl_8042C9A4->rwfree(entry->buffer10);
	}
	if (entry->buffer1C != 0) {
		lbl_8042C9A4->rwfree(entry->buffer1C);
	}
	memset(entry, 0, sizeof(Entry8013CB88));
	return object;
}
}
