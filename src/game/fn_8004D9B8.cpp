// Turns the current team's handler off as fn_8004DB3C(0) does, then sets the team's lbl_802D5AF0
// entry (which keeps fn_8004DB3C from turning the handler back on). Built with -bool off like
// fn_8004DB3C. HYPOTHESIS: the roles are UNKNOWN.
#include "types.h"

// The toggle of fn_8004DB3C (see there): a negative request toggles the handler; on, when off and
// the lbl_802D5AF0 entry is clear, sets it to 8; off, when on, clears it, calls fn_80134800 and
// sets up the team's record at its count (+0x8C) for kind 12, as fn_8004DEC0 does.

struct Handler8004D9B8 {
	s32 active;   // 0x0
	s32 unknown4; // 0x4
	s32 unknown8; // 0x8
	u8 padC[0x114 - 0xC];
};

struct Entry8004D9B8 {
	s32 value; // 0x0
	u8 pad4[0x8];
};

struct Record8004D9B8 {
	s32 kind;      // 0x0
	s32 unknown4;  // 0x4
	s32 calls;     // 0x8
	void* handler; // 0xC
	u8 pad10[4];
	u8 work[0x100]; // 0x14
};

struct Team8004D9B8 {
	u8 pad0[0x8C];
	s32 count; // 0x8C
	u8 pad90[0x11D0 - 0x90];
	Record8004D9B8 records[8]; // 0x11D0 (extent UNKNOWN)
	u8 pad1A70[0x2324 - 0x1A70];
};

struct Kind8004D9B8 {
	u32 unknown0;
	void* handler; // 0x4
};

extern "C" {
extern Team8004D9B8 lbl_802B908C[];
extern Handler8004D9B8 lbl_802C1D1C[];
extern Entry8004D9B8 lbl_802D5AF0[];
extern s32 lbl_8042C1FC;
extern const Kind8004D9B8 lbl_80239B74[];
void* memset(void* dst, int c, unsigned long n);
void fn_80134800(void);
}

static inline s32 HandlerActive()
{
	return lbl_802C1D1C[lbl_8042C1FC].active != 0;
}

// fn_8004DEC0.
static inline s32 SetRecord(s32 index, s32 kind)
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

// fn_8004DB3C.
static inline void SetHandler(s32 on)
{
	if (on < 0) {
		on = lbl_802C1D1C[lbl_8042C1FC].active == 0;
	}
	if (on) {
		if (lbl_802C1D1C[lbl_8042C1FC].active == 0 && lbl_802D5AF0[lbl_8042C1FC].value == 0) {
			lbl_802C1D1C[lbl_8042C1FC].unknown8 = 0;
			lbl_802C1D1C[lbl_8042C1FC].active   = 8;
		}
	} else if (HandlerActive() == 1) {
		lbl_802C1D1C[lbl_8042C1FC].active = 0;
		fn_80134800();
		SetRecord(lbl_802B908C[lbl_8042C1FC].count, 12);
	}
}

// The retail code still tests the constant request (0) inside the inlined toggle: no constant
// propagation into it.
#pragma opt_propagation off
extern "C" void fn_8004D9B8(void)
{
	SetHandler(0);
	lbl_802D5AF0[lbl_8042C1FC].value = 1;
}
#pragma opt_propagation reset
