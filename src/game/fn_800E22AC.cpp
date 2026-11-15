#include "types.h"

// Whether a player's action may attack (returns 1 or 0): never with action flag 0x4000, while the
// team leader (team +0x258 of the record, +0x114 by +0x3A; a different player) is in character
// state 9 with fn_800AB32C set, or while the slot's player object (lbl_802AD070 by the record's
// +0x0) is in mode 0x11. A player fn_8008915C accepts may in team state 2 be refused while the
// leader is flying low (flags 0x2001, not mode 0x1D, +0x7DC below lbl_8042E230) unless it has
// flag 0x80000000 (+0x7F0) on stages 0xC/0xD; it then needs bit 0x4 of its slot entry
// (lbl_802B0310 +0x9). Others need that bit in the team entry fn_8009262C picks for team state 0
// (by the record's +0x250: lbl_8042B6A8 or lbl_8042B6AC) or 1. HYPOTHESIS: names UNKNOWN.

struct Action800E22AC {
	u8 pad0[0x6];
	s16 flags; // 0x6
};

struct Player800E22AC {
	u8 pad0[0x628];
	s32 mode628; // 0x628
	u8 pad62C[0x6F0 - 0x62C];
	Action800E22AC action; // 0x6F0 (mode at +0x0)
	u8 pad6F8[0x761 - 0x6F8];
	s8 character; // 0x761
	u8 pad762[0x7DC - 0x762];
	f32 height; // 0x7DC
	u8 pad7E0[0x7F0 - 0x7E0];
	u32 flags7F0; // 0x7F0
};

struct Team800E22AC {
	u8 pad0[0x3A];
	s8 member; // 0x3A
	u8 pad3B[0x114 - 0x3B];
	Player800E22AC* members[3]; // 0x114
	u8 pad120[0x140 - 0x120];
	s32 state; // 0x140
};

struct Record800E22AC {
	s8 number; // 0x0
	u8 pad1[0x250 - 0x1];
	s32 unknown250; // 0x250
	u8 pad254[0x258 - 0x254];
	Team800E22AC* team; // 0x258
};

struct Entry800E22AC {
	u8 pad0[0x9];
	s8 flags; // 0x9
	u8 padA[0x10 - 0xA];
};

struct Stage800E22AC {
	u8 pad0[0x2C];
	s32 stage; // 0x2C
};

extern "C" {
extern Player800E22AC* lbl_802AD070[];
extern Entry800E22AC lbl_802B0310[];
extern Stage800E22AC lbl_8029C310;
extern s32 lbl_8042B6A8;
extern s32 lbl_8042B6AC;
extern const f32 lbl_8042E230;
s32 fn_800AB32C(Player800E22AC* player);
s32 fn_8008915C(Player800E22AC* player);
Entry800E22AC* fn_8009262C(Team800E22AC* team, s32 kind);
}

extern "C" s32 fn_800E22AC(Action800E22AC* action, Record800E22AC* record)
{
	Player800E22AC* leader;
	Team800E22AC* team;
	Player800E22AC* player;

	if (action->flags & 0x4000) {
		return 0;
	}
	team   = record->team;
	leader = team->members[team->member];
	if (&leader->action != action && fn_800AB32C(leader) == 1 && leader->character == 9) {
		return 0;
	}
	player = lbl_802AD070[record->number];
	if (player->mode628 == 0x11) {
		return 0;
	}
	if (fn_8008915C(player)) {
		if (team->state == 2 && (leader->action.flags & 0x2001) == 0x2001
		    && *(s16*)&leader->action != 0x1D && leader->height < lbl_8042E230) {
			if (!((leader->flags7F0 & 0x80000000)
			        && (lbl_8029C310.stage == 0xC || lbl_8029C310.stage == 0xD))) {
				return 0;
			}
		}
		if (lbl_802B0310[record->number].flags & 0x4) {
			return 1;
		}
	} else {
		switch (team->state) {
			case 0:
				switch (record->unknown250) {
					case 1:
						if (fn_8009262C(team, lbl_8042B6A8)->flags & 0x4) {
							return 1;
						}
						break;
					case 2:
						if (fn_8009262C(team, lbl_8042B6AC)->flags & 0x4) {
							return 1;
						}
						break;
				}
				break;
			case 1:
				if (fn_8009262C(team, lbl_8042B6A8)->flags & 0x4) {
					return 1;
				}
				break;
		}
	}
	return 0;
}
