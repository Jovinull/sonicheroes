#include "game/gparam.h"

// Starts action 0x38 for a player hit by an object: the object's state (+0x14E) becomes 0x5B, the
// hit record gets kind 0xE (+0x1) and its +0x6 cleared, and the action gains flag 0x400. Objects of
// kind 1 or 4 (+0x1) get at least lbl_8042D53C of speed (+0x60) and play sound 0x2075 at the
// action's position (fn_800B5118 on lbl_8042C388). The player then runs fn_800469CC(1) and
// releases its task +0xBC8 (flag 0x1). For a kind-7 object, the first other team member (team
// +0x258: count +0x121, members +0x134) in mode 0xA or 0xB is reset (fn_800898F0(4),
// fn_80044110) and the object's team (+0x25C) gains lbl_8042D51C of team blast gauge (addSFA).
// HYPOTHESIS: the roles are UNKNOWN.
// NonMatching (4 words, float register numbering): retail loads the speed into f1 and the minimum
// into f0; MWCC swaps them (same instructions otherwise). Tried: locals for either value, a clamp
// inline, an empty else, a non-const or array declaration of the constant. See fn_800EE69C.

struct Task80067664 {
	u8 pad0[0x4];
	u16 flags; // 0x4
};

struct Member80067664 {
	u8 pad0[0x628];
	s32 mode; // 0x628
};

struct Team80067664 {
	u8 pad0[0x121];
	s8 count; // 0x121
	u8 pad122[0x134 - 0x122];
	Member80067664* members[4]; // 0x134
};

struct Object80067664 {
	u8 pad0[0x1];
	s8 kind; // 0x1
	u8 pad2[0x60 - 0x2];
	f32 speed; // 0x60
	u8 pad64[0x14E - 0x64];
	s16 state; // 0x14E
	u8 pad150[0x258 - 0x150];
	Team80067664* team; // 0x258
	s8 teamNumber;      // 0x25C
};

struct Action80067664 {
	s16 action; // 0x0
	u8 pad2[0x6 - 0x2];
	s16 flags; // 0x6
	u8 pad8[0x18 - 0x8];
	RwV3d position; // 0x18
};

struct Hit80067664 {
	u8 pad0[0x1];
	u8 kind; // 0x1
	u8 pad2[0x6 - 0x2];
	s16 unknown6; // 0x6
};

struct Player80067664 {
	u8 pad0[0xB4];
	PARAM_SFA* sfa; // 0xB4
	u8 padB8[0xBC8 - 0xB8];
	Task80067664* task; // 0xBC8
};

extern "C" {
extern void* lbl_8042C388;
extern const f32 lbl_8042D51C;
extern const f32 lbl_8042D53C;
void fn_800B5118(void* sound, s32 id, RwV3d* position, s32 unknown1, s32 unknown2);
void fn_800469CC(Player80067664* player, s32 unknown);
void fn_800898F0(Member80067664* member, s32 unknown);
void fn_80044110(Member80067664* member);
}

extern "C" void fn_80067664(
    Player80067664* player, Action80067664* action, Object80067664* object, Hit80067664* hit)
{
	action->action = 0x38;
	object->state  = 0x5B;
	hit->unknown6  = 0;
	hit->kind      = 0xE;
	action->flags |= 0x400;
	switch (object->kind) {
		case 1:
		case 4:
			if (object->speed < lbl_8042D53C) {
				object->speed = lbl_8042D53C;
			}
			if (lbl_8042C388 != NULL) {
				fn_800B5118(lbl_8042C388, 0x2075, &action->position, 0, 0);
			}
			break;
	}
	fn_800469CC(player, 1);
	if (player->task != NULL) {
		player->task->flags |= 1;
		player->task = NULL;
	}
	if (object->kind == 7) {
		Team80067664* team = object->team;
		s32 count          = team->count;
		// The explicit guard is in the retail code (a test before the loop's own).
		if (count > 1) {
			for (s32 i = 1; i < count; i++) {
				Member80067664* member = team->members[i];
				if (member->mode == 0xB || member->mode == 0xA) {
					fn_800898F0(member, 4);
					fn_80044110(member);
					player->sfa->addSFA(object->teamNumber, lbl_8042D51C);
					break;
				}
			}
		}
	}
}
