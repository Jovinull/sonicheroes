// Resets the per-player objects of a player slot (HYPOTHESIS): when the slot lbl_802AD070[index]
// is in use, sets flag 0x1000 and mode 0x3F on the object lbl_802AD090[index] (clearing word 0x24
// of lbl_802AD0D0[index]), then clears its flags 0x203C and halfword 0x8 together with three
// fields of lbl_802AD0D0[index], whose flags 0xC003 at 0x10 are cleared as well. Field names are
// inferred from this function only.
#include "types.h"

struct ObjectA800E124C {
	u8 pad0[0x4];
	s16 mode;  // 0x4
	s16 flags; // 0x6
	s16 half8; // 0x8
};

struct ObjectB800E124C {
	u8 pad0[0x10];
	s16 flags; // 0x10
	u8 pad12[0x4];
	s16 half16; // 0x16
	u8 pad18[0xC];
	s32 word24; // 0x24
	u8 pad28[0x90 - 0x28];
	s32 word90; // 0x90
	u8 pad94[0xC4 - 0x94];
	s32 wordC4; // 0xC4
};

extern "C" {
extern void* lbl_802AD070[8];
extern ObjectA800E124C* lbl_802AD090[8];
extern ObjectB800E124C* lbl_802AD0D0[8];

void fn_800E124C(s32 index)
{
	ObjectA800E124C* a;
	ObjectB800E124C* b;

	if (!lbl_802AD070[index]) {
		return;
	}
	a = lbl_802AD090[index];
	b = lbl_802AD0D0[index];
	if (a) {
		a->flags |= 0x1000;
		a->mode                     = 0x3F;
		lbl_802AD0D0[index]->word24 = 0;
	}
	if (a) {
		a->flags &= ~0x203C;
		a->half8  = 0;
		b->word90 = 0;
		b->half16 = 0;
		b->wordC4 = 0;
	}
	if (b) {
		b->flags &= ~0xC003;
	}
}
}
