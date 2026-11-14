// Gives the plugin data of geometry (at the offset lbl_8042C86C) a cleared array of count 0x14-byte
// records allocated with the engine memory function, freeing any previous array. Plugin and record
// names are UNKNOWN. Returns the geometry, or null when the allocation fails.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

struct Record8014A3A0 {
	u8 b[0x14];
};

struct Ext8014A3A0 {
	s32 count; // 0x0
	s32 f4;
	Record8014A3A0* records; // 0x8
};

extern "C" {
extern s32 lbl_8042C86C;

void* fn_8014A3A0(void* geometry, s32 count)
{
	Ext8014A3A0* ext = (Ext8014A3A0*)((u8*)geometry + lbl_8042C86C);
	if (ext->records != 0) {
		lbl_8042C9A4->rwfree(ext->records);
		ext->count   = 0;
		ext->records = 0;
	}
	ext->records = (Record8014A3A0*)lbl_8042C9A4->rwmalloc(count * sizeof(Record8014A3A0));
	if (ext->records == 0) {
		return 0;
	}
	ext->count = count;
	memset(ext->records, 0, count * sizeof(Record8014A3A0));
	return geometry;
}
}
