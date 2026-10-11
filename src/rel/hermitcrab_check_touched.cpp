#include "types.h"

// TObjHermitCrab's CheckTouchedByLeader (the body of rel/chao_check_touched.cpp,
// TObjChao::CheckTouchedByLeader; hermitcrabCheckTouchedByLeader here): unless
// something of kind 0x13 or 1 hits the crab's collision, it goes through the
// players touching it and answers the team of the first one that is its
// team's leader or partner, or -1.

typedef struct HermitcrabHitter {
	u8 pad000[0x78];
	s32 type; // 0x78
} HermitcrabHitter;

typedef struct HermitcrabHit {
	u8 pad00[0x4];
	HermitcrabHitter* hitter; // 0x04
} HermitcrabHit;

typedef struct HermitcrabPlayer {
	u8 pad000[0x25C];
	s8 team; // 0x25C
} HermitcrabPlayer;

typedef struct HermitcrabTeam {
	u8 pad000[0x3A];
	s8 partner; // 0x3A
	s8 leader;  // 0x3B
	u8 pad03C[0xD4];
	s8 members[1]; // 0x110
} HermitcrabTeam;

typedef struct Hermitcrab {
	u8 base[0x30];  // 0x00
	u8 colli[0x10]; // 0x30
} Hermitcrab;

extern "C" u8 lbl_8042C1A4[];
extern "C" HermitcrabPlayer* lbl_802AD0D0[];
extern "C" HermitcrabTeam* lbl_80303DC8[];
extern "C" void fn_80021824(void* world);
extern "C" HermitcrabHit* fn_80020BD8(void* colli, s32 kind);
extern "C" HermitcrabHit* fn_800211A8(void* colli);

static inline HermitcrabHitter* hermitcrabHitter(HermitcrabHit* hit)
{
	if (hit != NULL) {
		return hit->hitter;
	}
	return NULL;
}

extern "C" s32 hermitcrabCheckTouchedByLeader(Hermitcrab* object)
{
	s32 character = -1;
	HermitcrabHitter* hitter;

	fn_80021824(lbl_8042C1A4);
	if (hermitcrabHitter(fn_80020BD8(object->colli, 0x13)) != NULL) {
		return -1;
	}
	fn_80021824(lbl_8042C1A4);
	if (hermitcrabHitter(fn_80020BD8(object->colli, 1)) != NULL) {
		return -1;
	}
	fn_80021824(object->colli);
	while ((hitter = hermitcrabHitter(fn_800211A8(object->colli))) != NULL) {
		switch (hitter->type) {
			case 1:
				character = 0;
				break;
			case 2:
				character = 1;
				break;
			case 3:
				character = 2;
				break;
			case 4:
				character = 3;
				break;
			case 5:
				character = 4;
				break;
			case 6:
				character = 5;
				break;
		}
		if (character != -1) {
			HermitcrabPlayer* player = lbl_802AD0D0[character];
			s32 team                 = player->team;
			if (player != NULL) {
				HermitcrabTeam* info = lbl_80303DC8[team];
				if (character == info->members[info->leader]
				    || character == info->members[info->partner]) {
					return team;
				}
			}
		}
	}
	return -1;
}
