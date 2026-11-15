#include "game/scanpath.h"

// Moves player slot idx onto a path (returns 1, or 0 when refused): refused for an empty slot
// (lbl_802AD090) or an action state with flag 0x2000. A slot already on a path (action 0x11 with
// flag 0x1000) only switches when the new path is not nearer than its current one
// (SCPathPntNearToOnpos from the action's position +0x18); the new path counts as lbl_8042E1F4
// away when the team leader (a different player; its record at +0x760) rides the same path in a
// path action. Otherwise the slot enters action 0x11. The record (lbl_802AD0D0) keeps the path
// (+0xC4) and the position on it (+0x2C). HYPOTHESIS: grind rails; the roles are UNKNOWN.
// NonMatching (8 words, r3/r4 swapped): retail keeps the leader in r3 and its record in r4; MWCC
// loads the leader into r4. Tried: a record local, operand order, a team local, an inline check
// and all declaration orders (perm.py).

struct Action800DFB88 {
	u8 pad0[0x4];
	s16 action; // 0x4
	s16 flags;  // 0x6
	u8 pad8[0x18 - 0x8];
	RwV3d position; // 0x18
};

struct Team800DFB88;

// The record block of a player, at +0x760 of the player object.
struct Record800DFB88 {
	u8 pad0[0x2C];
	f32 onPath; // 0x2C
	u8 pad30[0xC4 - 0x30];
	PATHTAG* path; // 0xC4
	u8 padC8[0x258 - 0xC8];
	Team800DFB88* team; // 0x258
};

struct Player800DFB88 {
	u8 pad0[0x6F0];
	s16 unknown6F0; // 0x6F0
	u8 pad6F2[0x6F4 - 0x6F2];
	s16 action; // 0x6F4
	s16 flags;  // 0x6F6
	u8 pad6F8[0x760 - 0x6F8];
	Record800DFB88 record; // 0x760
};

struct Team800DFB88 {
	u8 pad0[0x3A];
	s8 current; // 0x3A
	u8 pad3B[0x114 - 0x3B];
	Player800DFB88* members[3]; // 0x114
};

extern "C" {
extern Action800DFB88* lbl_802AD090[];
extern Record800DFB88* lbl_802AD0D0[];
extern const f32 lbl_8042E1F0;
extern const f32 lbl_8042E1F4;
}

extern "C" s32 fn_800DFB88(s32 idx, PATHTAG* path)
{
	Action800DFB88* action = lbl_802AD090[idx];
	Record800DFB88* record = lbl_802AD0D0[idx];

	if (action == NULL) {
		return 0;
	}
	if (action->flags & 0x2000) {
		return 0;
	}
	if ((action->flags & 0x1000) && action->action == 0x11) {
		f32 current
		    = SCPathPntNearToOnpos(record->path, &action->position, NULL, NULL, lbl_8042E1F0);
		f32 next = SCPathPntNearToOnpos(path, &action->position, NULL, NULL, lbl_8042E1F0);
		Player800DFB88* leader       = record->team->members[record->team->current];
		Record800DFB88* leaderRecord = &leader->record;
		if (leaderRecord != record) {
			PATHTAG* leaderPath = leaderRecord->path;
			if (((leader->flags & 0x2000) || ((leader->flags & 0x1000) && leader->action == 0x11))
			    && leaderPath == record->path) {
				next = lbl_8042E1F4;
			}
		}
		if (current < next) {
			return 0;
		}
	} else {
		action->flags |= 0x1000;
		action->action = 0x11;
	}
	record->path = path;
	SCPathPntNearToOnpos(path, &action->position, NULL, &record->onPath, lbl_8042E1F0);
	return 1;
}
