// Clears the plugin data of object (at the offset lbl_8042C86C): frees its buffer (+0x8) with the
// engine memory function and zeroes the buffer pointer and the word at +0x0. Plugin and field names
// are UNKNOWN. Returns the object.
#include "game/rw_engine.h"

struct Ext80149FD8 {
	s32 f0; // 0x0
	s32 f4;
	void* buffer; // 0x8
};

extern "C" {
extern s32 lbl_8042C86C;

void* fn_80149FD8(void* object)
{
	Ext80149FD8* ext = (Ext80149FD8*)((u8*)object + lbl_8042C86C);
	if (ext->buffer != 0) {
		lbl_8042C9A4->rwfree(ext->buffer);
	}
	ext->buffer = 0;
	ext->f0     = 0;
	return object;
}
}
