// Returns 1 when every other member of a team is in a state its table entry allows, otherwise 0
// (HYPOTHESIS): for each member except the team's own index (0x3A), the entry
// lbl_8024E440[team 0x140][0x34][member level - 1] (level at 0x250 of the member's
// lbl_802AD0D0 object, slot from the byte table at 0x110) decides: members in states 0x10..0x12
// always pass, otherwise the state must be 2 for an entry of kind 3 and 1 for any other kind
// (state at 0x628 of the member object at 0x114). Field names are inferred from this function
// only.
#include "types.h"

struct Entry80096A98 {
	u8 pad0[0xC];
	s32 kind; // 0xC
};

struct MemberData80096A98 {
	u8 pad0[0x250];
	s32 level; // 0x250
};

struct Member80096A98 {
	u8 pad0[0x628];
	s32 state; // 0x628
};

struct Team80096A98 {
	u8 pad0[0x34];
	s32 variant; // 0x34
	u8 pad38[0x1];
	s8 count; // 0x39
	s8 self;  // 0x3A
	u8 pad3B[0x110 - 0x3B];
	s8 slots[4];                // 0x110
	Member80096A98* members[4]; // 0x114
	u8 pad124[0x140 - 0x124];
	s32 group; // 0x140
};

extern "C" {
extern Entry80096A98 lbl_8024E440[][4][2];
extern MemberData80096A98* lbl_802AD0D0[8];

s32 fn_80096A98(Team80096A98* team)
{
	s32 i;

	for (i = 0; i < team->count; i++) {
		if (i != team->self) {
			Entry80096A98* entry = &lbl_8024E440[team->group][team->variant]
			                                    [lbl_802AD0D0[team->slots[i]]->level - 1];
			s32 state            = team->members[i]->state;
			if (state >= 0x13 || state < 0x10) {
				if (entry->kind == 3) {
					if (state != 2) {
						return 0;
					}
				} else if (state != 1) {
					return 0;
				}
			}
		}
	}
	return 1;
}
}
