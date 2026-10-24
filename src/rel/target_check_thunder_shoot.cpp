#include "types.h"

// TObjTarget::CheckThunderShoot (the PS2 build's name, by its place in the PS2
// order; targetCheckThunderShoot here). Among the collisions that hit the
// target it takes the last thunder shoot (a collision of kind 0xF); if there
// is one the target is hit (state 5, sound 0x100C) by that player's team,
// scores the point the shot hit (CheckHitPoint inlined), the team is rewarded
// by the score as for a fire dunk, sound 0x100B plays and the target lingers
// 60 frames.

#include "src/rel/target.inc"

typedef struct TargetHitInfo {
	u8 kind; // 0x0
} TargetHitInfo;

typedef struct TargetHitColli {
	u8 unk00[0x10];
	TargetHitInfo* info; // 0x10
	u8 unk14[0x4C];
	RwV3d pos; // 0x60
	u8 unk6C[0xC];
	void* owner; // 0x78
} TargetHitColli;

typedef struct TargetHitLink {
	u8 unk0[0x4];
	TargetHitColli* colli; // 0x04
} TargetHitLink;

typedef struct TargetPlayer {
	u8 unk000[0x258];
	s32 reward; // 0x258
	s8 team;    // 0x25C
	s8 member;  // 0x25D
} TargetPlayer;

extern "C" u8 lbl_8042C1A4[];
extern "C" void* lbl_8042C388;
extern "C" TargetPlayer* lbl_802AD0D0[];

extern "C" void fn_80021824(void* collision);
extern "C" TargetHitLink* fn_800211A8(void* colli);
extern "C" s32 fn_80041B64(void* owner);
extern "C" void fn_800908C0(s32 reward, s32 member, s32 kind);
extern "C" void fn_800B52E8(void* sound, s32 id, s32 a, s32 b);

// the next collision that hit the target, if any
static inline TargetHitColli* targetNextHit(Target* object)
{
	TargetHitLink* link = fn_800211A8(object->colli);

	return link != NULL ? link->colli : NULL;
}

extern "C" void targetCheckThunderShoot(Target* object)
{
	TargetHitColli* hit;
	RwV3d* point;
	s32 player = -1;

	fn_80021824(lbl_8042C1A4);
	while ((hit = targetNextHit(object)) != NULL) {
		if (hit->info->kind == 0xF) {
			player = fn_80041B64(hit->owner);
			point  = &hit->pos;
		}
	}
	if (player != -1) {
		if (lbl_8042C388 != NULL) {
			fn_800B52E8(lbl_8042C388, 0x100C, 0, 0);
		}
		object->state = 5;
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
		if (lbl_8042C388 != NULL) {
			fn_800B52E8(lbl_8042C388, 0x100B, 0, 0);
		}
		object->time = 60;
	}
}
