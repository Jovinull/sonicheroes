#include "types.h"

// TObjFlowerCommon's CheckLeader, CheckCharmy and CheckSomebody (the PS2
// build's names, in its order). Each refuses while a kind 0x13 hit is on the
// flower's collision; otherwise it goes through the players touching the flower
// (characters 1-6 are players 0-5): CheckSomebody answers the last of them,
// CheckLeader the first who leads its team (or is its second member at 0x3A),
// CheckCharmy (which also needs a kind 0x11 hit) the first who is Charmy
// (character 0xB); -1 for none.

#include "game/effect/eff_bomb.h"

typedef struct FlowerHit {
	u8 unk0[0x4];
	C_COLLI* hitter; // 0x04
} FlowerHit;

typedef struct FlowerPlayer {
	u8 unk000[0x1];
	s8 character; // 0x001
	u8 unk002[0x25A];
	s8 team; // 0x25C
} FlowerPlayer;

typedef struct FlowerTeam {
	u8 unk000[0x3A];
	s8 second; // 0x3A
	s8 leader; // 0x3B
	u8 unk03C[0xD4];
	s8 members[4]; // 0x110
} FlowerTeam;

typedef struct FlowerCommon {
	u8 unk00[0x30];
	C_COLLI colli; // 0x30
} FlowerCommon;

extern "C" u8 lbl_8042C1A4[];
extern "C" FlowerPlayer* lbl_802AD0D0[];
extern "C" FlowerTeam* lbl_80303DC8[];

extern "C" void fn_80021824(void* colli);
extern "C" FlowerHit* fn_80020BD8(C_COLLI* colli, s32 kind);
extern "C" FlowerHit* fn_800211A8(C_COLLI& colli);

static inline C_COLLI* flowerHitter(FlowerHit* hit)
{
	if (hit != NULL) {
		return hit->hitter;
	}
	return NULL;
}

extern "C" s32 CheckLeader__16TObjFlowerCommonFv(FlowerCommon* flower)
{
	s32 no = -1;
	C_COLLI* hitter;

	fn_80021824(lbl_8042C1A4);
	if (flowerHitter(fn_80020BD8(&flower->colli, 0x13)) != NULL) {
		return -1;
	}
	fn_80021824(&flower->colli);
	while ((hitter = flowerHitter(fn_800211A8(flower->colli))) != NULL) {
		switch (hitter->character_id) {
			case PLAYER_0:
				no = 0;
				break;
			case PLAYER_1:
				no = 1;
				break;
			case PLAYER_2:
				no = 2;
				break;
			case PLAYER_3:
				no = 3;
				break;
			case PLAYER_4:
				no = 4;
				break;
			case PLAYER_5:
				no = 5;
				break;
		}
		if (no != -1 && lbl_802AD0D0[no] != NULL) {
			FlowerTeam* team = lbl_80303DC8[lbl_802AD0D0[no]->team];

			if (no == team->members[team->leader] || no == team->members[team->second]) {
				return no;
			}
		}
	}
	return -1;
}

extern "C" s32 CheckCharmy__16TObjFlowerCommonFv(FlowerCommon* flower)
{
	s32 no = -1;
	C_COLLI* hitter;

	fn_80021824(lbl_8042C1A4);
	if (flowerHitter(fn_80020BD8(&flower->colli, 0x13)) != NULL) {
		return -1;
	}
	fn_80021824(&flower->colli);
	if (flowerHitter(fn_80020BD8(&flower->colli, 0x11)) == NULL) {
		return -1;
	}
	fn_80021824(&flower->colli);
	while ((hitter = flowerHitter(fn_800211A8(flower->colli))) != NULL) {
		switch (hitter->character_id) {
			case PLAYER_0:
				no = 0;
				break;
			case PLAYER_1:
				no = 1;
				break;
			case PLAYER_2:
				no = 2;
				break;
			case PLAYER_3:
				no = 3;
				break;
			case PLAYER_4:
				no = 4;
				break;
			case PLAYER_5:
				no = 5;
				break;
		}
		if (no != -1 && lbl_802AD0D0[no] != NULL && lbl_802AD0D0[no]->character == 0xB) {
			return no;
		}
	}
	return -1;
}

extern "C" s32 CheckSomebody__16TObjFlowerCommonFv(FlowerCommon* flower)
{
	s32 no = -1;
	C_COLLI* hitter;

	fn_80021824(lbl_8042C1A4);
	if (flowerHitter(fn_80020BD8(&flower->colli, 0x13)) != NULL) {
		return -1;
	}
	fn_80021824(&flower->colli);
	while ((hitter = flowerHitter(fn_800211A8(flower->colli))) != NULL) {
		switch (hitter->character_id) {
			case PLAYER_0:
				no = 0;
				break;
			case PLAYER_1:
				no = 1;
				break;
			case PLAYER_2:
				no = 2;
				break;
			case PLAYER_3:
				no = 3;
				break;
			case PLAYER_4:
				no = 4;
				break;
			case PLAYER_5:
				no = 5;
				break;
		}
	}
	return no;
}
