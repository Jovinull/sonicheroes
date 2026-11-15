// Sets up record `index` of the current team (lbl_802B908C[lbl_8042C1FC]; 0x114-byte records from
// +0x11D0, valid up to the count at +0x8C) for handler kind `kind`: stores the kind, clears the two
// following words and the 0x100-byte work area, and installs the kind's handler from the table
// lbl_80239B74 (8-byte entries, handler second). Returns 0 when the index is past the count, else
// 1. The first argument is unused; the roles are UNKNOWN (see fn_80051944, which calls the
// handler).
#include "types.h"

struct Record8004DEC0 {
	s32 kind;      // 0x0
	s32 unknown4;  // 0x4
	s32 calls;     // 0x8
	void* handler; // 0xC
	u8 pad10[4];
	u8 work[0x100]; // 0x14
};

struct Team8004DEC0 {
	u8 pad0[0x8C];
	s32 count; // 0x8C
	u8 pad90[0x11D0 - 0x90];
	Record8004DEC0 records[8]; // 0x11D0 (extent UNKNOWN)
	u8 pad1A70[0x2324 - 0x1A70];
};

struct Kind8004DEC0 {
	u32 unknown0;
	void* handler; // 0x4
};

extern "C" {
extern Team8004DEC0 lbl_802B908C[];
extern s32 lbl_8042C1FC;
extern const Kind8004DEC0 lbl_80239B74[];
void* memset(void* dst, int c, unsigned long n);

s32 fn_8004DEC0(s32 unused, s32 index, s32 kind)
{
	if (index > lbl_802B908C[lbl_8042C1FC].count) {
		return 0;
	}
	lbl_802B908C[lbl_8042C1FC].records[index].kind     = kind;
	lbl_802B908C[lbl_8042C1FC].records[index].unknown4 = 0;
	lbl_802B908C[lbl_8042C1FC].records[index].calls    = 0;
	memset(lbl_802B908C[lbl_8042C1FC].records[index].work, 0,
	    sizeof(lbl_802B908C[lbl_8042C1FC].records[index].work));
	lbl_802B908C[lbl_8042C1FC].records[index].handler = lbl_80239B74[kind].handler;
	return 1;
}
}
