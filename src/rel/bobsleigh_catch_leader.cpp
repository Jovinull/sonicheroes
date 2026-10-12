#include "types.h"

// TObjBobsleigh::CatchLeaderPlayer (the PS2 build's name). With the game not
// paused it checks the sled's boarding collision: the first player that
// touches it (character types 1 to 6, player slots 0 to 5) gives the sled its
// team, the team picks the sled's model kind (0x0E0: 7 to 10) and the riders
// board (InitRideOn).

typedef struct C_COLLI C_COLLI;

typedef struct BobsleighHitter {
	u8 unk00[0x78];
	s32 type; // 0x78
} BobsleighHitter;

typedef struct BobsleighHit {
	u8 unk00[0x4];
	BobsleighHitter* hitter; // 0x04
} BobsleighHit;

typedef struct BobsleighBoarding {
	u8 unk00[0x28];
	u8 colli[0x4]; // 0x28 (C_COLLI)
} BobsleighBoarding;

typedef struct BobsleighPlayer {
	u8 unk000[0x9BC];
	s8 team; // 0x9BC
} BobsleighPlayer;

typedef struct Bobsleigh {
	u8 unk000[0x68];
	u8 world[0x78]; // 0x068
	s32 kind;       // 0x0E0
	u8 unk0E4[0xB8];
	s32 team; // 0x19C
	u8 unk1A0[0x1AC];
	BobsleighBoarding* boarding; // 0x34C
} Bobsleigh;

extern "C" u8* lbl_8042C180;
extern "C" BobsleighPlayer* lbl_802AD070[];

extern "C" void fn_80021824(void* world);
extern "C" BobsleighHit* fn_800211A8(void* colli);
extern "C" void InitRideOn__13TObjBobsleighFv(Bobsleigh* object);

static inline BobsleighHitter* bobsleighHitter(BobsleighHit* hit)
{
	if (hit != NULL) {
		return hit->hitter;
	}
	return NULL;
}

extern "C" void CatchLeaderPlayer__13TObjBobsleighFv(Bobsleigh* object)
{
	if ((s8)lbl_8042C180[0x20] == 0) {
		int no = -1;
		BobsleighHitter* hitter;

		fn_80021824(object->world);
		if (object->boarding != NULL
		    && (hitter = bobsleighHitter(fn_800211A8(object->boarding->colli))) != NULL) {
			switch (hitter->type) {
				case 1:
					no = 0;
					break;
				case 2:
					no = 1;
					break;
				case 3:
					no = 2;
					break;
				case 4:
					no = 3;
					break;
				case 5:
					no = 4;
					break;
				case 6:
					no = 5;
					break;
			}
		}
		if (no != -1) {
			object->team = lbl_802AD070[no]->team;
			switch (object->team) {
				case 0:
					object->kind = 7;
					break;
				case 1:
					object->kind = 8;
					break;
				case 2:
					object->kind = 9;
					break;
				case 3:
					object->kind = 10;
					break;
			}
		} else {
			return;
		}
		InitRideOn__13TObjBobsleighFv(object);
	}
}
