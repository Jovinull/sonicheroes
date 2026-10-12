#include "types.h"

// Two TObjBobsleigh members on its riders (the PS2 build's names), with no
// caller left:
// - RemovePlayer: the team member of the given player type (looked up in the
//   sled's team) gets off: action 0x16, fn_800E1208(player, 0xF, 0) and its
//   0x8000 flag cleared.
// - SetInvinc: sets the 0x8000 flag of the riders still on board, from the
//   count at 0x2E0 (0: types 0, 2 and 1; 1: types 2 and 1; 2: type 1).

typedef struct BobsleighTeam {
	u8 unk000[0x110];
	s8 members[4]; // 0x110
} BobsleighTeam;

typedef struct BobsleighRider {
	u8 unk000[0x10];
	s16 flags; // 0x10
	u8 unk012[0x13C];
	s16 action; // 0x14E
} BobsleighRider;

typedef struct Bobsleigh {
	u8 unk000[0x19C];
	s32 team; // 0x19C
	u8 unk1A0[0x140];
	s32 off; // 0x2E0
} Bobsleigh;

extern "C" BobsleighTeam* lbl_80303DC8[];
extern "C" BobsleighRider* lbl_802AD0D0[];

extern "C" s32 fn_8009278C(BobsleighTeam* team, int type);
extern "C" void fn_800E1208(int player, int kind, int arg);

extern "C" void RemovePlayer__13TObjBobsleighF16ENUM_PLAYER_TYPE(Bobsleigh* object, int type)
{
	BobsleighTeam* team   = lbl_80303DC8[object->team];
	int no                = team->members[fn_8009278C(team, type)];
	BobsleighRider* rider = lbl_802AD0D0[no];

	rider->action = 0x16;
	fn_800E1208(no, 0xF, 0);
	rider->flags &= ~0x8000;
}

static inline BobsleighRider* bobsleighRider(BobsleighTeam* team, int type)
{
	return lbl_802AD0D0[team->members[fn_8009278C(team, type)]];
}

extern "C" void SetInvinc__13TObjBobsleighFv(Bobsleigh* object)
{
	BobsleighTeam* team = lbl_80303DC8[object->team];

	switch (object->off) {
		case 0:
			bobsleighRider(team, 0)->flags |= 0x8000;
		case 1:
			bobsleighRider(team, 2)->flags |= 0x8000;
		case 2:
			bobsleighRider(team, 1)->flags |= 0x8000;
	}
}
