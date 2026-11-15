// Picks a player's action (+0x14E) from its state. Unless flag 0x8000 of +0x20 is set, a linked
// record (+0x258) in mode 3, or in mode 2 with its byte +0x121 above 1, forces action 0x41. A
// player whose +0x150 is 0x43 gets +0x154 = 0x10 instead. Otherwise, unless the action is one of
// 5-8, 0x10, 0x1B or 0x1C with neither bit 0 nor bit 1 of +0x158 set, the value
// +0x60 + K * +0x34 picks action 8/7/6/5/4 against the thresholds at +0xFC/+0xF4/+0xF0/+0xEC
// (action 0x1A is kept and returns early). Finally +0x40 is reset. The first two arguments are
// unused. HYPOTHESIS: a speed-based run animation choice; field names are UNKNOWN.
#include "types.h"

struct Linked80047384 {
	u8 pad0[0x121];
	s8 unknown121; // 0x121
	u8 pad122[0x140 - 0x122];
	s32 mode; // 0x140
};

struct Player80047384 {
	u8 pad0[0x20];
	s32 flags20; // 0x20
	u8 pad24[0x34 - 0x24];
	f32 unknown34; // 0x34
	u8 pad38[0x40 - 0x38];
	f32 unknown40; // 0x40
	u8 pad44[0x60 - 0x44];
	f32 unknown60; // 0x60
	u8 pad64[0xEC - 0x64];
	f32 thresholdEC; // 0xEC
	f32 thresholdF0; // 0xF0
	f32 thresholdF4; // 0xF4
	u8 padF8[0xFC - 0xF8];
	f32 thresholdFC; // 0xFC
	u8 pad100[0x14E - 0x100];
	s16 action;     // 0x14E
	s16 unknown150; // 0x150
	u8 pad152[2];
	s16 unknown154; // 0x154
	u8 pad156[2];
	s16 flags158; // 0x158
	u8 pad15A[0x258 - 0x15A];
	Linked80047384* linked; // 0x258
};

extern "C" {
extern f32 lbl_8042D248;
extern f32 lbl_8042D208;

void fn_80047384(s32 unused0, s32 unused1, Player80047384* p)
{
	if (!(p->flags20 & 0x8000)) {
		if ((p->linked->mode == 2 && p->linked->unknown121 > 1) || p->linked->mode == 3) {
			p->action = 0x41;
			return;
		}
	}
	switch (p->unknown150) {
		case 0x43:
			p->unknown154 = 0x10;
			return;
	}
	if (!((p->action == 5 || (u16)(p->action - 6) <= 2 || p->action == 0x10 || p->action == 0x1B
	          || p->action == 0x1C)
	        && !(p->flags158 & 2) && !(p->flags158 & 1))) {
		f32 value = p->unknown60 + lbl_8042D248 * p->unknown34;

		if (p->action == 0x1A) {
			return;
		}
		if (value > p->thresholdFC) {
			p->action = 8;
		} else if (value > p->thresholdF4) {
			p->action = 7;
		} else if (value > p->thresholdF0) {
			p->action = 6;
		} else if (value > p->thresholdEC) {
			p->action = 5;
		} else {
			p->action = 4;
		}
	}
	p->unknown40 = lbl_8042D208;
}
}
