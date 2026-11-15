// Whether every member of enemy group `group` that needs a target (kind 5, 6, 7 or 0x1104) has
// one in state 2; 0 for an empty group. This is the out-of-line copy of the check that
// TObjEnemy::IsSleep inlines (see IsSleep__9TObjEnemyFv.cpp). The first argument is unused
// (HYPOTHESIS: the enemy, as `this` of a TObjEnemy member). Field roles are inferred from these
// two functions only.
#include "types.h"

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

extern "C" {
extern Groups800A2BE0* lbl_8042C298;

s32 fn_800A2BE0(void* unused, u8 group)
{
	Member800A2BE0* head   = lbl_8042C298->groups[group];
	Member800A2BE0* member = head;

	if (!head) {
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
}
