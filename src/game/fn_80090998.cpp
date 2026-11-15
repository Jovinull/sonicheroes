// Ages a team's eight pending score entries (+0x24C kind, +0x254 age, +0x25C player) and packs
// them to the front: an entry that reaches age 0x7F is banked into the team's PARAM_SCORE (+0x29,
// team +0x38; points from lbl_8024EF18 by kind) and cleared; empty entries have their age and
// player cleared. HYPOTHESIS: the score pop-up queue; see fn_8009D1F8 for the final banking.
#include "game/gparam.h"

struct Team80090998 {
	u8 pad0[0x29];
	u8 score[1]; // 0x29 (PARAM_SCORE base)
	u8 pad2A[0x38 - 0x2A];
	s8 number; // 0x38
	u8 pad39[0x3E - 0x39];
	s16 unknown3E; // 0x3E
	u8 pad40[0x4C - 0x40];
	u8 unknown4C[0xC0]; // 0x4C
	u8 pad10C[0x150 - 0x10C];
	s32 unknown150; // 0x150
	u8 pad154[0x1FC - 0x154];
	s16 unknown1FC; // 0x1FC
	s16 unknown1FE; // 0x1FE
	s16 unknown200; // 0x200
	s16 unknown202; // 0x202
	s16 unknown204; // 0x204
	u8 pad206[0x20B - 0x206];
	s8 unknown20B; // 0x20B
	s8 unknown20C; // 0x20C
	u8 pad20D[0x21C - 0x20D];
	s8 unknown21C; // 0x21C
	s8 unknown21D; // 0x21D
	s8 unknown21E; // 0x21E
	u8 pad21F[0x24C - 0x21F];
	s8 pendingKind[8];    // 0x24C
	s8 pendingUnknown[8]; // 0x254
	s8 pendingPlayer[8];  // 0x25C
	u8 pad264[2];
	s8 unknown266; // 0x266
};

extern "C" {
extern const s16 lbl_8024EF18[];

void fn_80090998(Team80090998* team)
{
	int i;
	int count;

	for (i = 0, count = 0; i < 8; i++) {
		s8 kind = team->pendingKind[i];

		if (kind != 0) {
			s32 age = team->pendingUnknown[i] + 1;

			if (age >= 0x7F) {
				((PARAM_SCORE*)team->score)
				    ->addScore(team->number, team->pendingPlayer[i], lbl_8024EF18[kind]);
				team->pendingKind[i]    = 0;
				team->pendingUnknown[i] = 0;
				team->pendingPlayer[i]  = 0;
			} else {
				if (i != count) {
					team->pendingKind[count]   = kind;
					team->pendingPlayer[count] = team->pendingPlayer[i];
					team->pendingKind[i]       = 0;
					team->pendingUnknown[i]    = 0;
					team->pendingPlayer[i]     = 0;
				}
				team->pendingUnknown[count] = age;
				count++;
			}
		} else {
			team->pendingUnknown[i] = 0;
			team->pendingPlayer[i]  = 0;
		}
	}
}
}
