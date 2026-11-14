// Frees the record with the engine memory function unless all of its fields (+0x0, the halfwords
// at +0x4 and +0x6, +0x8 and +0xC) are zero. Always returns 1. Names are UNKNOWN.
#include "game/rw_engine.h"

struct Record801559E4 {
	void* f0; // 0x0
	u16 f4;   // 0x4
	u16 f6;   // 0x6
	void* f8; // 0x8
	void* fC; // 0xC
};

extern "C" {
s32 fn_801559E4(Record801559E4* record)
{
	if (record->f0 != 0 || record->f4 != 0 || record->f6 != 0 || record->f8 != 0
	    || record->fC != 0) {
		lbl_8042C9A4->rwfree(record);
	}
	return 1;
}
}
