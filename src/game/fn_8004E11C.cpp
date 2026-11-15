#include "types.h"

// fn_8004E408 followed by storing `value` in the new record's +0x4: sets record `index` (0..15)
// of the current team's record stack to kind `kind` (see fn_8004E408) and, when that worked,
// gives it the value. Returns the record, or NULL. The first argument is unused. HYPOTHESIS: the
// roles are UNKNOWN.

struct Record8004E11C {
	s32 kind;       // 0x0
	s32 unknown4;   // 0x4
	s32 calls;      // 0x8
	void* handler;  // 0xC
	s32 unknown10;  // 0x10
	u8 work[0x100]; // 0x14
};

struct Team8004E11C {
	u8 pad0[0x8C];
	s32 top;                    // 0x8C
	Record8004E11C records[16]; // 0x90
	Record8004E11C saved[16];   // 0x11D0
	u8 pad2310[0x2324 - 0x2310];
};

struct Kind8004E11C {
	u32 unknown0;
	void* handler; // 0x4
	u32 unknown8;
};

extern "C" {
extern Team8004E11C lbl_802B908C[];
extern s32 lbl_8042C1FC;
extern const Kind8004E11C lbl_80239A30[];
void* memset(void* dst, int c, unsigned long n);
}

static inline void CopySaved(s32 from, s32 to)
{
	if (lbl_802B908C[lbl_8042C1FC].top >= from && lbl_802B908C[lbl_8042C1FC].top >= to) {
		lbl_802B908C[lbl_8042C1FC].saved[to] = lbl_802B908C[lbl_8042C1FC].saved[from];
	}
}

// The body is an inline: called directly, its parameter copies give the retail register coloring.
static inline Record8004E11C* SetRecord(s32 index, s32 kind)
{
	if (index >= 16) {
		return NULL;
	}
	s32 top                                            = lbl_802B908C[lbl_8042C1FC].top;
	lbl_802B908C[lbl_8042C1FC].records[index].unknown4 = 0;
	lbl_802B908C[lbl_8042C1FC].records[index].kind     = kind;
	lbl_802B908C[lbl_8042C1FC].records[index].calls    = 0;
	memset(lbl_802B908C[lbl_8042C1FC].records[index].work, 0,
	    sizeof(lbl_802B908C[lbl_8042C1FC].records[index].work));
	lbl_802B908C[lbl_8042C1FC].records[index].handler   = lbl_80239A30[kind].handler;
	lbl_802B908C[lbl_8042C1FC].records[index].unknown10 = 0;
	if (top < index) {
		lbl_802B908C[lbl_8042C1FC].top = index;
		CopySaved(top, index);
	}
	return &lbl_802B908C[lbl_8042C1FC].records[index];
}

extern "C" Record8004E11C* fn_8004E11C(s32 unused, s32 index, s32 kind, s32 value)
{
	Record8004E11C* record = SetRecord(index, kind);
	if (record != NULL) {
		lbl_802B908C[lbl_8042C1FC].records[index].unknown4 = value;
		return record;
	}
	return NULL;
}
