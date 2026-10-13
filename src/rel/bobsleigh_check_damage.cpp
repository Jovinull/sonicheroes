#include "types.h"

// TObjBobsleigh::CheckBobDamage (the PS2 build's name). It counts down the
// riders' fall-off timers (0x2F4 for type 0, 0x2FC for type 2; at 0 the rider
// lands, fn_80043E9C) and the hurt time. While hurt it ignores hits until the
// grace time is over; otherwise a hit on the sled's damage collision (flag
// 0x1000000) slows it to its hit speed, plays the hit sound (another one in
// stage 13) and, for a hit that counts, starts the hurt time and throws off one
// more rider (RemovePlayer, inlined): types 0, 2 and then 1. When the last one
// falls in a race, the other team wins (once); otherwise the leader is hurt.

typedef struct BobsleighTeam {
	u8 unk000[0x3B];
	s8 leader; // 0x3B
	u8 unk03C[0xD4];
	s8 members[4]; // 0x110
} BobsleighTeam;

typedef struct BobsleighRider {
	u8 unk000[0x10];
	s16 flags; // 0x10
	u8 unk012[0x13C];
	s16 action; // 0x14E
} BobsleighRider;

typedef struct BobsleighPlayer BobsleighPlayer;

typedef struct BobsleighHitter {
	u8 unk00[0x4];
	s16 counts; // 0x04
} BobsleighHitter;

typedef struct BobsleighHit {
	u8 unk00[0x4];
	BobsleighHitter* hitter; // 0x04
} BobsleighHit;

typedef struct GameState {
	u8 unk00[0x2C];
	s32 stage; // 0x2C
} GameState;

typedef struct Bobsleigh {
	u8 unk000[0x68];
	u8 world[0xF0]; // 0x068
	f32 speed;      // 0x158
	u8 unk15C[0x40];
	s32 team; // 0x19C
	u8 unk1A0[0x30];
	f32 hitSpeed; // 0x1D0
	u8 unk1D4[0x10C];
	s32 off;  // 0x2E0
	s32 hurt; // 0x2E4
	u8 unk2E8[0xC];
	s32 fallTimer0; // 0x2F4
	u8 unk2F8[0x4];
	s32 fallTimer2; // 0x2FC
	u8 unk300[0x60];
	s32 race; // 0x360
	u8 unk364[0xC];
	s32 decided; // 0x370
} Bobsleigh;

extern "C" BobsleighTeam* lbl_80303DC8[];
extern "C" BobsleighRider* lbl_802AD0D0[];
extern "C" BobsleighPlayer* lbl_802AD070[];
extern "C" Bobsleigh* lbl_80288E0C[];
extern "C" GameState lbl_8029C310;
extern "C" void* lbl_8042C388;
extern "C" s32 bobsleighHurtTime;
extern "C" s32 bobsleighHurtGrace;
extern "C" s32 bobsleighHitVolume;

extern "C" s32 fn_8009278C(BobsleighTeam* team, int type);
extern "C" void fn_800E1208(int player, int kind, int arg);
extern "C" void fn_80043E9C(BobsleighPlayer* player);
extern "C" void fn_80044960(BobsleighPlayer* player);
extern "C" void fn_80021824(void* world);
extern "C" BobsleighHit* fn_80020ABC(void* world, u32 flags);
extern "C" void fn_800B52E8(void* sound, s32 id, s8 volume, s32 arg);
extern "C" void fn_8009142C(BobsleighTeam* team);
extern "C" void fn_80092580(BobsleighTeam* team);
extern "C" void fn_80019898(GameState* state, int winner);
extern "C" void fn_80137880(int player);
extern "C" void fn_800C0EA0(int winner);

static inline BobsleighPlayer* bobsleighPlayer(BobsleighTeam* team, int type)
{
	return lbl_802AD070[team->members[fn_8009278C(team, type)]];
}

static inline void bobsleighRemovePlayer(Bobsleigh* object, int type)
{
	BobsleighTeam* team   = lbl_80303DC8[object->team];
	int no                = team->members[fn_8009278C(team, type)];
	BobsleighRider* rider = lbl_802AD0D0[no];

	rider->action = 0x16;
	fn_800E1208(no, 0xF, 0);
	rider->flags &= ~0x8000;
}

extern "C" void CheckBobDamage__13TObjBobsleighFv(Bobsleigh* object)
{
	BobsleighTeam* team = lbl_80303DC8[object->team];
	BobsleighHitter* hitter;
	BobsleighHit* hit;

	if (object->fallTimer0 > 0) {
		object->fallTimer0--;
		if (object->fallTimer0 == 0) {
			fn_80043E9C(bobsleighPlayer(team, 0));
		}
	}
	if (object->fallTimer2 > 0) {
		object->fallTimer2--;
		if (object->fallTimer2 == 0) {
			fn_80043E9C(bobsleighPlayer(team, 2));
		}
	}
	if (object->hurt > 0) {
		object->hurt--;
		if (object->hurt > bobsleighHurtTime - bobsleighHurtGrace) {
			return;
		}
	}
	fn_80021824(object->world);
	hit = fn_80020ABC(object->world, 0x1000000);
	if (hit != NULL) {
		hitter = hit->hitter;
	} else {
		hitter = NULL;
	}
	if (hitter == NULL) {
		return;
	}
	object->speed = object->hitSpeed;
	if (lbl_8029C310.stage != 13) {
		if (lbl_8042C388 != NULL) {
			fn_800B52E8(lbl_8042C388, 0x1062, bobsleighHitVolume, 0);
		}
	} else {
		if (lbl_8042C388 != NULL) {
			fn_800B52E8(lbl_8042C388, 0x5A0F, bobsleighHitVolume, 0);
		}
	}
	if (hitter->counts == 0) {
		return;
	}
	object->hurt = bobsleighHurtTime;
	object->off++;
	switch (object->off) {
		case 1:
			bobsleighRemovePlayer(object, 0);
			object->fallTimer0 = 30;
			break;
		case 2:
			bobsleighRemovePlayer(object, 2);
			object->fallTimer2 = 30;
			break;
		case 3:
			bobsleighRemovePlayer(object, 1);
			if (object->race != 0) {
				fn_8009142C(lbl_80303DC8[object->team]);
				fn_80092580(lbl_80303DC8[object->team]);
				if (object->team == 0) {
					if (lbl_80288E0C[1]->off != 3 && object->decided == 0) {
						fn_80019898(&lbl_8029C310, 1);
						fn_80137880(lbl_80303DC8[1]->members[lbl_80303DC8[1]->leader]);
						lbl_80288E0C[object->team ^ 1]->decided = 1;
						fn_800C0EA0(1);
					}
				} else {
					if (lbl_80288E0C[0]->off != 3 && object->decided == 0) {
						fn_80019898(&lbl_8029C310, 0);
						fn_80137880(lbl_80303DC8[0]->members[lbl_80303DC8[0]->leader]);
						lbl_80288E0C[object->team ^ 1]->decided = 1;
						fn_800C0EA0(0);
					}
				}
			} else {
				fn_80044960(bobsleighPlayer(team, 1));
			}
			break;
	}
}
