// TObjEnemy::IsSleep (symbol name from the retail map): whether the enemy stays asleep
// (HYPOTHESIS for the field roles). An enemy whose set object (0xB0) carries the sleep flag
// 0x04000000 wakes up (the flag is cleared) once every member of its group that has kind 5, 6, 7
// or 0x1104 has a target in state 2; the enemy also counts as asleep while the global word 0x40
// of lbl_8042C180 is not -1. Field names are inferred from this function only.
// NonMatching: the group walk keeps the member in r3 where the retail code uses r4 (11 words).
#include "types.h"

#define ENEMY_SET_SLEEP 0x04000000

struct Target800A2BE0 {
	u8 pad0[0x10];
	s32 state; // 0x10
};

// Member of an enemy group list.
struct Member800A2BE0 {
	u8 pad0[0x28];
	u16 kind; // 0x28
	u8 pad2A[0x6];
	Target800A2BE0* target; // 0x30
	u8 pad34[0x4];
	Member800A2BE0* next; // 0x38
};

struct Groups800A2BE0 {
	u8 pad0[0x30];
	Member800A2BE0* groups[1]; // 0x30 (extent UNKNOWN)
};

struct SetObject800A2BE0 {
	u8 pad0[0x18];
	u32 flags; // 0x18
	u8 pad1C[0xE];
	u8 group; // 0x2A
};

struct Enemy800A2BE0 {
	u8 pad0[0xB0];
	SetObject800A2BE0* set; // 0xB0
};

struct Global800A2BE0 {
	u8 pad0[0x40];
	s32 word40; // 0x40
};

extern "C" {
extern Groups800A2BE0* lbl_8042C298;
extern Global800A2BE0* lbl_8042C180;
}

static inline bool IsSetFlagged(SetObject800A2BE0* set, u32 flag)
{
	return (set->flags & flag) != 0;
}

// Whether every member of the set object's group that needs a target has one in state 2.
static inline s32 IsGroupReady(SetObject800A2BE0* set)
{
	Member800A2BE0* member = lbl_8042C298->groups[set->group];

	if (!member) {
		return 0;
	}
	for (; member; member = member->next) {
		if (member->kind == 5 || (u16)(member->kind - 6) <= 1 || member->kind == 0x1104) {
			if (!member->target) {
				return 0;
			}
			if (member->target->state != 2) {
				return 0;
			}
		}
	}
	return 1;
}

extern "C" s32 IsSleep__9TObjEnemyFv(Enemy800A2BE0* enemy)
{
	s32 sleep              = 0;
	SetObject800A2BE0* set = enemy->set;

	if ((s32)IsSetFlagged(set, ENEMY_SET_SLEEP) == 1) {
		if (IsGroupReady(set)) {
			set->flags &= ~ENEMY_SET_SLEEP;
			sleep = 0;
		} else {
			sleep = 1;
		}
	}
	if (lbl_8042C180->word40 != -1) {
		sleep = 1;
	}
	return sleep;
}
