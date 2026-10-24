#include "types.h"

// TObjTarget::CheckFireDunk (the PS2 build's name, by its place in the PS2
// order; targetCheckFireDunk here). Among the collisions that hit the target
// it looks for one from a player in a fire dunk (state 0x40); if there is one
// the target is hit (state 7) by that player's team, scores the point the
// player hit (CheckHitPoint inlined), and the team is rewarded by the score
// (2 for the bull's-eye, else 4) and the target lingers 60 frames.

#include "src/rel/target.inc"

typedef struct TargetHitColli {
	u8 unk00[0x60];
	RwV3d pos; // 0x60
	u8 unk6C[0xC];
	void* owner; // 0x78
} TargetHitColli;

typedef struct TargetHitLink {
	u8 unk0[0x4];
	TargetHitColli* colli; // 0x04
} TargetHitLink;

typedef struct TargetPlayerState {
	s16 state; // 0x0
} TargetPlayerState;

typedef struct TargetPlayer {
	u8 unk000[0x258];
	s32 reward; // 0x258
	s8 team;    // 0x25C
	s8 member;  // 0x25D
} TargetPlayer;

extern "C" u8 lbl_8042C1A4[];
extern "C" TargetPlayerState* lbl_802AD090[];
extern "C" TargetPlayer* lbl_802AD0D0[];

extern "C" void fn_80021824(void* collision);
extern "C" TargetHitLink* fn_800211A8(void* colli);
extern "C" s32 fn_80041B64(void* owner);
extern "C" void fn_800908C0(s32 reward, s32 member, s32 kind);

// the next collision that hit the target, if any
static inline TargetHitColli* targetNextHit(Target* object)
{
	TargetHitLink* link = fn_800211A8(object->colli);

	return link != NULL ? link->colli : NULL;
}

extern "C" void targetCheckFireDunk(Target* object)
{
	TargetHitColli* hit;
	RwV3d* point;
	s32 player = -1;

	fn_80021824(lbl_8042C1A4);
	while ((hit = targetNextHit(object)) != NULL) {
		player = fn_80041B64(hit->owner);
		if (player == -1) {
			continue;
		}
		if (lbl_802AD090[player]->state != 0x40) {
			player = -1;
		} else {
			point = &hit->pos;
			break;
		}
	}
	if (player != -1) {
		object->state = 7;
		// the team passes through an int (the extsb before the store)
		s32 team       = lbl_802AD0D0[player]->team;
		object->holder = team;
		object->score  = targetCheckHitPoint(object, point);
		switch (object->score) {
			case 2:
				fn_800908C0(lbl_802AD0D0[player]->reward, lbl_802AD0D0[player]->member, 4);
				break;
			case 0:
			case 1:
				fn_800908C0(lbl_802AD0D0[player]->reward, lbl_802AD0D0[player]->member, 2);
				break;
		}
		object->time = 60;
	}
}
