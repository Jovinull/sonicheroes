// Resets a team's round state: clears the counters +0x1FC..+0x204 and flags +0x20B/+0x20C/+0x266/
// +0x21C..+0x21E, runs fn_8009CFC0, banks the eight pending score entries (kind +0x24C, player
// +0x25C; the points come from lbl_8024EF18 by kind) into the team's PARAM_SCORE (+0x29, team
// +0x38) and clears them, clears the 0xC0 bytes from +0x4C and +0x3E, and sets +0x150 to 10.
// HYPOTHESIS: the end-of-section score settlement; the roles are UNKNOWN.
#include "game/gparam.h"

struct Team8009D1F8 {
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
void fn_8009CFC0(Team8009D1F8* team);
void* memset(void* dst, int c, unsigned long n);
}

// Banks the eight pending score entries into the team's PARAM_SCORE and clears them. Inlined, the
// loop keeps a copy of its initial 0 per clearing store, as the retail code does.
static inline void BankScores(Team8009D1F8* team)
{
	int i;

	for (i = 0; i < 8; i++) {
		if (team->pendingKind[i] != 0) {
			((PARAM_SCORE*)team->score)
			    ->addScore(
			        team->number, team->pendingPlayer[i], lbl_8024EF18[team->pendingKind[i]]);
			team->pendingKind[i]    = 0;
			team->pendingUnknown[i] = 0;
			team->pendingPlayer[i]  = 0;
		}
	}
}

extern "C" {
void fn_8009D1F8(Team8009D1F8* team)
{
	team->unknown1FC = 0;
	team->unknown1FE = 0;
	team->unknown200 = 0;
	team->unknown202 = 0;
	team->unknown204 = 0;
	team->unknown20B = 0;
	team->unknown20C = 0;
	team->unknown266 = 0;
	team->unknown21C = 0;
	team->unknown21E = 0;
	team->unknown21D = 0;
	fn_8009CFC0(team);
	BankScores(team);
	memset(team->unknown4C, 0, sizeof(team->unknown4C));
	team->unknown3E  = 0;
	team->unknown150 = 10;
}
}
