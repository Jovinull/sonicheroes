// TObjS06Chip::CheckTouchedByLeader (the PS2 build's name): the body of
// rel/chao_check_touched.cpp (TObjChao's). Unless something of kind 0x13 or 1
// hits its collision, it goes through the players touching it and answers the
// team of the first one that is its team's leader or partner, or -1.

#define S06_CHIP_CTOR inline
#include "src/rel/s06_chip_class.inc"

struct ChaoHitter {
	u8 pad000[0x78];
	s32 type; // 0x78
};

struct ChaoHit {
	u8 pad00[0x4];
	ChaoHitter* hitter; // 0x04
};

struct ChaoPlayer {
	u8 pad000[0x25C];
	s8 team; // 0x25C
};

struct ChaoTeam {
	u8 pad000[0x3A];
	s8 partner; // 0x3A
	s8 leader;  // 0x3B
	u8 pad03C[0xD4];
	s8 members[1]; // 0x110
};

extern "C" u8 lbl_8042C1A4[];
extern "C" ChaoPlayer* lbl_802AD0D0[];
extern "C" ChaoTeam* lbl_80303DC8[];
extern "C" void fn_80021824(void* world);
extern "C" ChaoHit* fn_80020BD8(C_COLLI& colli, s32 kind);
extern "C" ChaoHit* fn_800211A8(C_COLLI& colli);

static inline ChaoHitter* chaoHitter(ChaoHit* hit)
{
	if (hit != NULL) {
		return hit->hitter;
	}
	return NULL;
}

s32 TObjS06Chip::CheckTouchedByLeader()
{
	s32 character = -1;
	ChaoHitter* hitter;

	fn_80021824(lbl_8042C1A4);
	if (chaoHitter(fn_80020BD8(*this, 0x13)) != NULL) {
		return -1;
	}
	fn_80021824(lbl_8042C1A4);
	if (chaoHitter(fn_80020BD8(*this, 1)) != NULL) {
		return -1;
	}
	fn_80021824(&static_cast<C_COLLI&>(*this));
	while ((hitter = chaoHitter(fn_800211A8(*this))) != NULL) {
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
			ChaoPlayer* player = lbl_802AD0D0[character];
			s32 team           = player->team;
			if (player != NULL) {
				ChaoTeam* info = lbl_80303DC8[team];
				if (character == info->members[info->leader]
				    || character == info->members[info->partner]) {
					return team;
				}
			}
		}
	}
	return -1;
}
