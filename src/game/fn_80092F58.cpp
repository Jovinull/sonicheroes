#include "types.h"

// Ends a team's special state (HYPOTHESIS: run when a team formation move finishes): picks the
// member that leads next (from the current one +0x3B: the next members in turn unless the team
// state +0x154 is 5 or 8, skipping members whose action +0x628 is 0x12, or out of 0..0x11 with
// +0x9B0 set), then for every member (+0x114, count +0x39) clears action timer 0xA (+0x6F4,
// with flag 0x1000 of +0x6F6) and, by action (+0x6F0), returns it to the normal state
// (fn_80044A94), or for actions 0x1B/0x3B and 0x3E (the new leader only) picks between
// fn_80044A94 and fn_80044844 (stage fn_80018C98 = 0xC). Finally a team below lbl_8042C204 with
// mode switch +0x21 clear raises its type-0x11 event 0xE in lbl_8042C1F8 (fn_80130F78 then
// fn_8004D99C). The roles are UNKNOWN.

struct Player80092F58 {
	u8 pad0[0x628];
	s32 action; // 0x628
	u8 pad62C[0x6F0 - 0x62C];
	s16 mode; // 0x6F0
	u8 pad6F2[0x6F4 - 0x6F2];
	s16 timer; // 0x6F4
	s16 flags; // 0x6F6
	u8 pad6F8[0x9B0 - 0x6F8];
	s32 unknown9B0; // 0x9B0
};

struct Team80092F58 {
	u8 pad0[0x38];
	s8 index; // 0x38
	s8 count; // 0x39
	u8 pad3A[0x3B - 0x3A];
	s8 current; // 0x3B
	u8 pad3C[0x114 - 0x3C];
	Player80092F58* members[0x10]; // 0x114
	s32 state;                     // 0x154
};

struct ModeSwitch80092F58 {
	u8 pad0[0x21];
	s8 unknown21; // 0x21
};

extern "C" {
extern s32 lbl_8042C204;
extern ModeSwitch80092F58* lbl_8042C180;
extern int lbl_8042C1F8;
void fn_80044A94(Player80092F58* player);
void fn_80044844(Player80092F58* player);
s32 fn_80018C98(void);
s32 fn_8004E588(int manager, s32 kind);
void fn_8004CC7C(int manager, s32 team);
s32 fn_80130F78(s32 kind, void* object);
void fn_8004D99C(int manager);
void fn_8004CC3C(int manager);
}

extern "C" void fn_80092F58(Team80092F58* team)
{
	s32 count;
	s32 n;
	s32 i;
	s32 leader;

	leader = team->current;
	count  = team->count;

	for (n = count; n > 0; n--) {
		s32 busy = 1;
		switch (team->state) {
			case 5:
			case 8:
				busy = 0;
				break;
			default:
				leader++;
				if (leader >= count) {
					leader = 0;
				}
				break;
		}
		Player80092F58* player = team->members[leader];
		switch (player->action) {
			default:
				if (player->unknown9B0 != 0) {
					break;
				}
			case 0x0:
			case 0x1:
			case 0x2:
			case 0x3:
			case 0x4:
			case 0x5:
			case 0x6:
			case 0x7:
			case 0x8:
			case 0x9:
			case 0xA:
			case 0xB:
			case 0xC:
			case 0xD:
			case 0xE:
			case 0xF:
			case 0x10:
			case 0x11:
				busy = 0;
				break;
			case 0x12:
				busy = 1;
				break;
		}
		if (busy == 0) {
			break;
		}
	}
	for (i = 0; i < team->count; i++) {
		Player80092F58* player = team->members[i];
		switch (player->timer) {
			case 0xA:
				player->timer = 0;
				player->flags &= ~0x1000;
				break;
		}
		switch (player->mode) {
			case 0x13:
			case 0x14:
			case 0x15:
			case 0x16:
			case 0x17:
			case 0x18:
			case 0x19:
			case 0x1A:
			case 0x21:
			case 0x29:
			case 0x2B:
			case 0x34:
			case 0x55:
				fn_80044A94(player);
				break;
			case 0x1B:
			case 0x3B:
				if (i == leader || fn_80018C98() == 0xC) {
					fn_80044A94(player);
				} else {
					fn_80044844(player);
				}
				break;
			case 0x3E:
				if (i == leader) {
					fn_80044A94(player);
				}
				break;
		}
	}
	if (team->index < lbl_8042C204 && lbl_8042C180->unknown21 == 0
	    && fn_8004E588(lbl_8042C1F8, 0xE) == 0x11) {
		fn_8004CC7C(lbl_8042C1F8, team->index);
		if (fn_80130F78(0xE, team) != 0) {
			fn_8004D99C(lbl_8042C1F8);
		}
		fn_8004CC3C(lbl_8042C1F8);
	}
}
