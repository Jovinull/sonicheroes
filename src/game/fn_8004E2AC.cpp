#include "types.h"

// Pushes a record of kind `kind` onto the current team's record stack (lbl_802B908C[lbl_8042C1FC]:
// sixteen 0x114-byte records from +0x90, top index at +0x8C): the record above the top is cleared,
// gets the kind's handler from lbl_80239A30 (12-byte entries, handler second) and becomes the top,
// and the saved copy of the old top (the second bank of records at +0x11D0) is copied to it.
// Returns the record, or NULL when the stack is full. The first argument is unused; fn_8004E408 is
// the same for a given index. HYPOTHESIS: the roles are UNKNOWN (see fn_8004DEC0, fn_80051944).

struct Record8004E2AC {
	s32 kind;       // 0x0
	s32 unknown4;   // 0x4
	s32 calls;      // 0x8
	void* handler;  // 0xC
	s32 unknown10;  // 0x10
	u8 work[0x100]; // 0x14
};

struct Team8004E2AC {
	u8 pad0[0x8C];
	s32 top;                    // 0x8C
	Record8004E2AC records[16]; // 0x90
	Record8004E2AC saved[16];   // 0x11D0
	u8 pad2310[0x2324 - 0x2310];
};

struct Kind8004E2AC {
	u32 unknown0;
	void* handler; // 0x4
	u32 unknown8;
};

extern "C" {
extern Team8004E2AC lbl_802B908C[];
extern s32 lbl_8042C1FC;
extern const Kind8004E2AC lbl_80239A30[];
void* memset(void* dst, int c, unsigned long n);
}

static inline void CopySaved(s32 from, s32 to)
{
	if (lbl_802B908C[lbl_8042C1FC].top >= from && lbl_802B908C[lbl_8042C1FC].top >= to) {
		lbl_802B908C[lbl_8042C1FC].saved[to] = lbl_802B908C[lbl_8042C1FC].saved[from];
	}
}

// The body of fn_8004E408 without its index check.
static inline Record8004E2AC* SetRecord(s32 index, s32 kind)
{
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

extern "C" Record8004E2AC* fn_8004E2AC(s32 unused, s32 kind)
{
	s32 index = lbl_802B908C[lbl_8042C1FC].top + 1;
	if (index >= 16) {
		return NULL;
	}
	return SetRecord(index, kind);
}
