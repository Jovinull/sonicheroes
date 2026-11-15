#include "types.h"

// Turns the current team's handler (lbl_802C1D1C[lbl_8042C1FC]) on or off. A negative request
// toggles it. Turning it on, when it is off and the team's lbl_802D5AF0 entry is clear, sets the
// handler to 8 and clears its word at +0x8; turning it off, when it is on, clears it, calls
// fn_80134800 and sets up the team's record at its count (+0x8C) for kind 12, as fn_8004DEC0 does.
// The first argument is unused; the roles are UNKNOWN (see fn_8004E6F0 and fn_800518AC). The unit
// is built with -bool off: the toggle's (active == 0) is stored without a byte clip.

struct Handler8004DB3C {
	s32 active;   // 0x0
	s32 unknown4; // 0x4
	s32 unknown8; // 0x8
	u8 padC[0x114 - 0xC];
};

struct Entry8004DB3C {
	s32 value; // 0x0
	u8 pad4[0x8];
};

struct Record8004DB3C {
	s32 kind;      // 0x0
	s32 unknown4;  // 0x4
	s32 calls;     // 0x8
	void* handler; // 0xC
	u8 pad10[4];
	u8 work[0x100]; // 0x14
};

struct Team8004DB3C {
	u8 pad0[0x8C];
	s32 count; // 0x8C
	u8 pad90[0x11D0 - 0x90];
	Record8004DB3C records[8]; // 0x11D0 (extent UNKNOWN)
	u8 pad1A70[0x2324 - 0x1A70];
};

struct Kind8004DB3C {
	u32 unknown0;
	void* handler; // 0x4
};

extern "C" {
extern Team8004DB3C lbl_802B908C[];
extern Handler8004DB3C lbl_802C1D1C[];
extern Entry8004DB3C lbl_802D5AF0[];
extern s32 lbl_8042C1FC;
extern const Kind8004DB3C lbl_80239B74[];
void* memset(void* dst, int c, unsigned long n);
void fn_80134800(void);
}

static inline s32 HandlerActive()
{
	s32 active = lbl_802C1D1C[lbl_8042C1FC].active;
	return active != 0;
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

extern "C" void fn_8004DB3C(s32 unused, s32 on)
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
