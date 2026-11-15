// Draws the two clumps of lbl_8042B708 (fn_8014FF2C) for an object and records at +0xEB whether
// any was drawn. When the object follows a player (+0xE8, -1: none), nothing is drawn while that
// player's state (lbl_802AD090) is 0x27, nor while its path record's clump (+0x180 of
// lbl_802AD0D0) is hidden (fn_8015BD78) and the current team record of lbl_8042C1F8 is not of kind
// 0xD. HYPOTHESIS: a goal/marker model visible only in some situations; the roles are UNKNOWN.
#include "types.h"

struct State800FB028 {
	s16 kind; // 0x0
};

struct Ctrl800FB028 {
	u8 pad0[0x180];
	void* clump; // 0x180
};

struct Obj800FB028 {
	u8 pad0[0xE8];
	s8 player; // 0xE8
	u8 padE9[2];
	s8 drawn; // 0xEB
};

extern "C" {
extern State800FB028* lbl_802AD090[8];
extern Ctrl800FB028* lbl_802AD0D0[8];
extern void* lbl_8042B708[2];
extern void* lbl_8042C1F8;
void* fn_8015BD78(void* clump);
s32 fn_8004E608(void* records);
s32 fn_8004E588(void* records, s32 index);
void fn_8014FF2C(void* clump);
}

extern "C" void fn_800FB028(Obj800FB028* o)
{
	int i;

	o->drawn = 0;
	if (o->player != -1) {
		switch (lbl_802AD090[o->player]->kind) {
			case 0x27:
				return;
		}
		if (lbl_802AD0D0[o->player]->clump != NULL
		    && fn_8015BD78(lbl_802AD0D0[o->player]->clump) == NULL
		    && fn_8004E588(lbl_8042C1F8, fn_8004E608(lbl_8042C1F8)) != 0xD) {
			return;
		}
	}
	for (i = 0; i < 2; i++) {
		if (lbl_8042B708[i] != NULL) {
			fn_8014FF2C(lbl_8042B708[i]);
			o->drawn = 1;
		}
	}
}
