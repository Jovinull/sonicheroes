// Resets the AI rival state of a player (+0x63A/+0x63C/+0x640): when the player's slot record
// (lbl_8029EBC0, 0x1488 bytes per player number +0x760) is empty and no rival player is found
// (SearchTheNearestRivalPlayer), it picks the speed +0x7C0 (lbl_8042E454 with flag 0x8000 of
// +0x780, else lbl_8042E3E4) and sets +0x63C to 1; otherwise it runs fn_800F0180 and, when +0x63C
// is then positive, sets the speed to lbl_8042E3E4. HYPOTHESIS: AI rival selection; the names are
// UNKNOWN.
#include "types.h"

struct Slot800F0838 {
	void* unknown0; // 0x0
	u8 pad4[0x1488 - 0x4];
};

struct Player800F0838 {
	u8 pad0[0x63A];
	s16 unknown63A; // 0x63A
	s16 unknown63C; // 0x63C
	u8 pad63E[2];
	s32 unknown640; // 0x640
	u8 pad644[0x760 - 0x644];
	s8 number; // 0x760
	u8 pad761[0x780 - 0x761];
	s32 flags780; // 0x780
	u8 pad784[0x7C0 - 0x784];
	f32 speed; // 0x7C0
};

int SearchTheNearestRivalPlayer(int number);

extern "C" {
extern Slot800F0838 lbl_8029EBC0[];
extern f32 lbl_8042E454;
extern f32 lbl_8042E3E4;
void fn_800F0180(Player800F0838* p);

void fn_800F0838(Player800F0838* p)
{
	p->unknown63A = 0;
	p->unknown63C = -1;
	p->unknown640 = 0;
	if (lbl_8029EBC0[p->number].unknown0 == NULL && SearchTheNearestRivalPlayer(p->number) == -1) {
		if (p->flags780 & 0x8000) {
			p->speed = lbl_8042E454;
		} else {
			p->speed = lbl_8042E3E4;
		}
		p->unknown63C = 1;
	} else {
		fn_800F0180(p);
		if (p->unknown63C > 0) {
			p->speed = lbl_8042E3E4;
		}
	}
}
}
