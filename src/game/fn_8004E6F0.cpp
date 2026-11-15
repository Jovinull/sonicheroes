// Runs one frame of team `team`'s scripted state (HYPOTHESIS: the team "action record" machine):
// selects the team (lbl_8042C1FC) and its block (lbl_8042C208 = +0x40 of its record) and, while
// lbl_8042C200 is set, runs fn_80051A68, the current record's handler (fn_800519B8), fn_800516E4,
// then either the team handler fn_800518AC (when lbl_802C1D1C has one for the team) or, once the
// wait counter +0x2320 is used up, the record callback fn_80051944; then fn_800516E4 and
// fn_80051614 again, and counts the timer +0x80 down. The roles are UNKNOWN.
// NonMatching (5 words): the retail code puts team * 0x2324 in r5 and reuses r4 for the record
// base; MWCC multiplies in place (r4). Tried: struct indexing, byte arithmetic as in fn_8004EC9C,
// a local record pointer, an inline selector, the global as index.
#include "types.h"

struct Team8004E6F0 {
	u8 pad0[0x40];
	u8 block[0x40]; // 0x40
	s32 timer;      // 0x80
	u8 pad84[0x2320 - 0x84];
	s32 wait; // 0x2320
};

struct Handler8004E6F0 {
	s32 active; // 0x0
	u8 pad4[0x114 - 0x4];
};

extern "C" {
extern Team8004E6F0 lbl_802B908C[];
extern s32 lbl_8042C1FC;
extern void* lbl_8042C208;
extern s32 lbl_8042C200;
extern Handler8004E6F0 lbl_802C1D1C[];
void fn_80051A68(void);
void fn_800519B8(void* arg);
void fn_800516E4(void* arg);
void fn_800518AC(void* arg);
void fn_80051944(void* arg);
void fn_80051614(void* arg);

void fn_8004E6F0(void* arg, s32 team)
{
	lbl_8042C1FC = team;
	lbl_8042C208 = lbl_802B908C[team].block;
	if (lbl_8042C200 != 0) {
		fn_80051A68();
		fn_800519B8(arg);
		fn_800516E4(arg);
		if (lbl_802C1D1C[lbl_8042C1FC].active != 0) {
			fn_800518AC(arg);
		} else {
			if (lbl_802B908C[lbl_8042C1FC].wait != 0) {
				lbl_802B908C[lbl_8042C1FC].wait--;
			} else {
				fn_80051944(arg);
			}
		}
		fn_800516E4(arg);
		fn_80051614(arg);
		if (lbl_802B908C[lbl_8042C1FC].timer != 0) {
			lbl_802B908C[lbl_8042C1FC].timer--;
		}
	}
}
}
