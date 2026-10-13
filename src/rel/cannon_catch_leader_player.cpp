#include "types.h"

// TObjCannon::CatchLeaderPlayer (cannonCatchLeaderPlayer here). Unless the game's
// flag at 0x22 is set or the cannon's volume is touched by kind 0x13, and once
// its wait is over, it looks for the nearest team leader within reach (leaders in
// the states 0x53 and 0x55 are skipped). With one found it checks the team's
// three members: a member not in state 0x11 is told so (fn_800E1208) and clears
// its bit, the others set theirs, and the leader catching it starts the load
// (state 1, a short wait). Each member's offset is cleared; when no member is the
// leader the cannon waits for the team (state 2) and keeps the team's formation.
//
// The distance is summed with separate multiplies and adds: the unit is built
// without fused multiply-add.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct CannonTeam {
	u8 unk00[0x3A];
	s8 leader; // 0x3A
	u8 unk3B[0xD5];
	s8 members[0x30]; // 0x110
	s32 status;       // 0x140
} CannonTeam;

typedef struct CannonPlayerInfo {
	s16 state; // 0x00
} CannonPlayerInfo;

typedef struct CannonPlayerTask {
	u8 unk000[0x628];
	s32 mode; // 0x628
} CannonPlayerTask;

typedef struct CannonHit {
	u8 unk00[0x4];
	u32 hit; // 0x04
} CannonHit;

typedef struct Cannon {
	u8 unk00[0x30];
	u8 colli[0x88]; // 0x30
	s32 state;      // 0xB8
	RwV3d pos;      // 0xBC
	u8 unkC8[0xC];
	s8 leader;    // 0xD4
	s8 formation; // 0xD5
	s8 unkD6;     // 0xD6
	u8 unkD7[0x3];
	s8 mask;   // 0xDA
	s8 unkDB;  // 0xDB
	s16 timer; // 0xDC
	u8 unkDE[0x3A];
	RwV3d offsets[3]; // 0x118
} Cannon;

extern "C" u8* lbl_8042C180;
extern "C" u8 lbl_8042C1A4[];
extern "C" CannonTeam* lbl_80303DC8[];
extern "C" CannonPlayerInfo* lbl_802AD090[];
extern "C" CannonPlayerTask* lbl_802AD070[];
extern "C" s32 cannonMemberKinds[];
extern "C" const f32 cannonCatchStart[1];
extern "C" const f32 cannonCatchReach[1];
extern "C" const f32 cannonZero[1];

extern "C" void fn_80021824(void* list);
extern "C" CannonHit* fn_80020BD8(void* colli, s32 kind);
extern "C" s32 fn_8003E2E4(s32 player, s32 kind, RwV3d* position, s32 arg3);
extern "C" CannonTeam* fn_800924E4(s32 player);
extern "C" s32 fn_800927D0(CannonTeam* team, s32 kind);
extern "C" s32 fn_80091FAC(CannonTeam* team);
extern "C" void fn_800E1208(s32 player, s32 arg1, s32 arg2);

extern "C" void cannonCatchLeaderPlayer(Cannon* object)
{
	CannonHit* hit;
	CannonTeam* team;
	f32 best;
	int i;

	if ((s8)lbl_8042C180[0x22] != 0) {
		return;
	}
	fn_80021824(lbl_8042C1A4);
	hit = fn_80020BD8(object->colli, 0x13);
	if ((hit != NULL ? hit->hit : 0) != 0) {
		return;
	}
	if (object->timer > 0) {
		object->timer--;
		return;
	}

	best           = cannonCatchStart[0];
	object->leader = -1;
	for (i = 0; i < 4; i++) {
		team = lbl_80303DC8[i];
		if (team != NULL && team->status != 3) {
			int player             = team->members[team->leader];
			CannonPlayerInfo* info = lbl_802AD090[player];
			RwV3d delta;

			if (info != NULL) {
				switch (info->state) {
					case 0x53:
					case 0x55:
						continue;
				}
			}
			if (fn_8003E2E4(player, 0, &delta, 0)) {
				f32 dist;

				delta.x -= object->pos.x;
				delta.y -= object->pos.y;
				delta.z -= object->pos.z;
				dist = delta.z * delta.z + (delta.x * delta.x + delta.y * delta.y);
				if (!(dist > cannonCatchReach[0]) && !(best < dist)) {
					best           = dist;
					object->leader = player;
				}
			}
		}
	}

	if (object->leader != -1) {
		CannonTeam* leaderTeam;
		int j;

		object->mask = 0;
		leaderTeam   = fn_800924E4(object->leader);
		for (j = 0; j < 3; j++) {
			int player = leaderTeam->members[fn_800927D0(leaderTeam, cannonMemberKinds[j])];

			if (lbl_802AD090[player] != NULL && lbl_802AD070[player]->mode != 0x11) {
				fn_800E1208(player, 0xA, 9);
				object->mask &= ~(1 << j);
			} else {
				object->mask |= 1 << j;
				if (player == leaderTeam->members[leaderTeam->leader]) {
					object->state = 1;
					object->unkD6 = 0;
					object->timer = 5;
					return;
				}
			}
			object->offsets[j].x = object->offsets[j].y = object->offsets[j].z = cannonZero[0];
		}
		object->state     = 2;
		object->formation = (s8)fn_80091FAC(fn_800924E4(object->leader));
		object->unkDB     = 0;
	}
}
