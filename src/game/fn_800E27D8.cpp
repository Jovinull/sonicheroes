#include "types.h"

// Gives the wall direction for a player's action state (returns 1, or 0 when there is none): with
// action flag 0x4000 the action's own angle (+0x10) and lbl_8042E24C. Otherwise refused while the
// team leader (a different player; team +0x258, members +0x114, current +0x3A) is in character
// state 9 with fn_800AB32C set or in mode 0x4C as character 6, while the slot's player object
// (lbl_802AD070 by the record's +0x0) is in mode 0x11, when the slot's wall entry (lbl_802B0310,
// 16 bytes) has a zero strength, or without action flag 0x2000 while the record's +0x14 is set.
// The angle is the entry's (mirrored around 0x8000 when lbl_80242B38 +0x4 is above lbl_8042E240)
// and the strength the entry's first value. HYPOTHESIS: the roles are UNKNOWN (see fn_80044FA4).

struct Action800E27D8 {
	u8 pad0[0x6];
	s16 flags; // 0x6
	u8 pad8[0x10 - 0x8];
	s32 angle; // 0x10
};

struct Player800E27D8 {
	u8 pad0[0x628];
	s32 mode628; // 0x628
	u8 pad62C[0x6F0 - 0x62C];
	s16 mode; // 0x6F0
	u8 pad6F2[0x761 - 0x6F2];
	s8 character; // 0x761
};

struct Team800E27D8 {
	u8 pad0[0x3A];
	s8 current; // 0x3A
	u8 pad3B[0x114 - 0x3B];
	Player800E27D8* members[3]; // 0x114
};

struct Record800E27D8 {
	s8 number; // 0x0
	u8 pad1[0x14 - 0x1];
	s16 unknown14; // 0x14
	u8 pad16[0x258 - 0x16];
	Team800E27D8* team; // 0x258
};

struct Wall800E27D8 {
	f32 strength; // 0x0
	s32 angle;    // 0x4
	u8 pad8[0x10 - 0x8];
};

struct Mirror800E27D8 {
	u8 pad0[0x4];
	f32 value; // 0x4
	u8 pad8[0x10 - 0x8];
};

extern "C" {
extern Player800E27D8* lbl_802AD070[];
extern Wall800E27D8 lbl_802B0310[];
extern Mirror800E27D8 lbl_80242B38;
extern const f32 lbl_8042E1F0; // 0.0f
extern const f32 lbl_8042E240;
extern const f32 lbl_8042E24C;
s32 fn_800AB32C(Player800E27D8* player);
}

extern "C" s32 fn_800E27D8(
    Action800E27D8* action, Record800E27D8* record, s32* angle, f32* strength)
{
	if (action->flags & 0x4000) {
		if (angle != NULL) {
			*angle = action->angle;
		}
		if (strength != NULL) {
			*strength = lbl_8042E24C;
		}
		return 1;
	}
	Player800E27D8* leader = record->team->members[record->team->current];
	if ((Action800E27D8*)((u8*)leader + 0x6F0) != action) {
		if ((fn_800AB32C(leader) == 1 && leader->character == 9)
		    || (leader->mode == 0x4C && leader->character == 6)) {
			return 0;
		}
	}
	s32 number = record->number;
	if (lbl_802AD070[number]->mode628 == 0x11) {
		return 0;
	}
	if (lbl_8042E1F0 != lbl_802B0310[number].strength) {
		if ((action->flags & 0x2000) || record->unknown14 == 0) {
			if (angle != NULL) {
				*angle = lbl_802B0310[number].angle;
				if (lbl_80242B38.value > lbl_8042E240) {
					*angle = 0x8000 - *angle;
				}
			}
			if (strength != NULL) {
				*strength = lbl_802B0310[record->number].strength;
			}
		} else {
			return 0;
		}
		return 1;
	}
	return 0;
}
