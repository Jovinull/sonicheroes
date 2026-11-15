#include "game/rw_types.h"

// Whether a player can start a wall action: never with action flags 0x3 (+0x6F6), when its height
// (+0x70C) is less than lbl_8042D214 above the record's +0x9A0, or when the wall normal (the
// record's +0x6C, or +0x84 when that one has zero length; fn_801991B4) is steeper than
// lbl_8042D218 on Y. The wall's attributes (+0x98, or +0xA0 with the second normal) must have
// 0x80000 and lack 0xC000. In mode 0x45 (+0x6F0) the answer is yes; otherwise the player needs
// +0x6A1 set and the wall direction from fn_800E27D8 within 0x3800 of its yaw (+0x73C).
// HYPOTHESIS: the roles (wall jumps, triangle jumps) are UNKNOWN. Built with -bool off: the final
// comparison is returned without a byte clip.

struct Action80044FA4 {
	s16 mode; // 0x0
	u8 pad2[0x6 - 0x2];
	s16 flags; // 0x6
	u8 pad8[0x1C - 0x8];
	f32 height; // 0x1C
};

struct Record80044FA4 {
	u8 pad0[0x6C];
	RwV3d normal; // 0x6C
	u8 pad78[0x84 - 0x78];
	RwV3d normal84; // 0x84
	u8 pad90[0x98 - 0x90];
	u32 attributes; // 0x98
	u8 pad9C[0xA0 - 0x9C];
	u32 attributesA0; // 0xA0
	u8 padA4[0x240 - 0xA4];
	f32 floor; // 0x240
};

struct Player80044FA4 {
	u8 pad0[0x6A1];
	s8 canWall; // 0x6A1
	u8 pad6A2[0x6F0 - 0x6A2];
	Action80044FA4 action; // 0x6F0
	u8 pad710[0x73C - 0x710];
	s32 yaw; // 0x73C
	u8 pad740[0x760 - 0x740];
	Record80044FA4 record; // 0x760
};

extern "C" {
extern const f32 lbl_8042D1BC; // 0.0f
extern const f32 lbl_8042D214;
extern const f32 lbl_8042D218;
double __fabs(double x);
f32 fn_801991B4(const RwV3d* v);
s32 fn_800E27D8(Action80044FA4* action, Record80044FA4* record, s32* angle, s32 unknown);
}

// game/misc.h declares DiffAngle returning u16; the callers use the full register.
s32 DiffAngle(s32 first, s32 second);

extern "C" s32 fn_80044FA4(Player80044FA4* player)
{
	Action80044FA4* action = &player->action;
	Record80044FA4* record = &player->record;

	if (action->flags & 3) {
		return 0;
	}
	if (action->height - record->floor < lbl_8042D214) {
		return 0;
	}
	RwV3d normal   = record->normal;
	u32 attributes = record->attributes;
	if (lbl_8042D1BC == fn_801991B4(&normal)) {
		RwV3d second = record->normal84;
		if (lbl_8042D1BC == fn_801991B4(&second)) {
			return 0;
		}
		attributes = record->attributesA0;
	}
	if ((f32)__fabs(normal.y) >= lbl_8042D218) {
		return 0;
	}
	if (attributes & 0xC000) {
		return 0;
	}
	if (!(attributes & 0x80000)) {
		return 0;
	}
	if (action->mode == 0x45) {
		return 1;
	}
	if (player->canWall == 0) {
		return 0;
	}
	s32 angle;
	if (fn_800E27D8(action, record, &angle, 0) == 0) {
		return 0;
	}
	return DiffAngle(angle, player->yaw) <= 0x3800;
}
