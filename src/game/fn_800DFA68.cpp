// Puts player `index` on a path like fn_800DF9F0 (state 0x20 instead of 0x21), but only when
// allowed: not while the state record is locked in kind 0x1D with flag 0x2000, nor while either
// pause byte (+0x21, +0x22) of lbl_8042C180 is set, nor in team mode 2 with more than one member
// (+0x121) for a player other than the team's followed one (+0x134), nor in team phase 0x17
// (+0x154). Returns 1 when done. HYPOTHESIS: the roles of the checks are UNKNOWN.
#include "game/scanpath.h"

struct State800DFA68 {
	s16 kind;  // 0x0
	s16 pad2;  // 0x2
	s16 state; // 0x4
	s16 flags; // 0x6
};

struct Team800DFA68 {
	u8 pad0[0x121];
	s8 members; // 0x121
	u8 pad122[0x134 - 0x122];
	void* followed; // 0x134
	u8 pad138[0x140 - 0x138];
	s32 mode; // 0x140
	u8 pad144[0x154 - 0x144];
	s32 phase; // 0x154
};

struct PathCtrl800DFA68 {
	u8 pad0[0x1E];
	s16 point; // 0x1E
	u8 pad20[0x2C - 0x20];
	f32 position; // 0x2C
	u8 pad30[0xC4 - 0x30];
	PATHTAG* path; // 0xC4
	u8 padC8[0x258 - 0xC8];
	Team800DFA68* team; // 0x258
};

struct Pause800DFA68 {
	u8 pad0[0x21];
	s8 pause21; // 0x21
	s8 pause22; // 0x22
};

extern "C" {
extern State800DFA68* lbl_802AD090[8];
extern PathCtrl800DFA68* lbl_802AD0D0[8];
extern void* lbl_802AD070[8];
extern Pause800DFA68* lbl_8042C180;
}

extern "C" s32 fn_800DFA68(s32 index, PATHTAG* path, f32 position)
{
	State800DFA68* state   = lbl_802AD090[index];
	PathCtrl800DFA68* ctrl = lbl_802AD0D0[index];
	Team800DFA68* team;
	u32 point;

	if ((state->flags & 0x2000) && state->kind == 0x1D) {
		return 0;
	}
	if (lbl_8042C180->pause22 || lbl_8042C180->pause21) {
		return 0;
	}
	team = ctrl->team;
	if (team->mode == 2) {
		void* player = lbl_802AD070[index];

		if (team->members > 1 && team->followed != player) {
			return 0;
		}
	}
	if (team->phase == 0x17) {
		return 0;
	}
	state->flags |= 0x1000;
	state->state   = 0x20;
	ctrl->path     = path;
	ctrl->position = position;
	SCPathOnposToPntnmb(path, position, &point);
	ctrl->point = point;
	return 1;
}
