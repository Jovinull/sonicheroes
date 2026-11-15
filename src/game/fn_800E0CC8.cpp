#include "types.h"

// Launches player slot idx upward with a given speed (returns 1, or 0 when refused like
// fn_800E03B4): the value is stored as an s16 at +0x14 of the record; on stages 6, 7, 0x27 and
// 0x2C (lbl_8029C310 +0x2C) a slot in mode 0x12 or 0x28 enters action 0x3D, otherwise action 6
// with the record's +0x24 from the team state (its +0x150 in states 2 and 3, else 0xB). The
// velocity (0, speed, 0) goes to the record (+0x60) and, turned by the action angle set from the
// given angle (fn_800E01E4 style) through fn_8003E9B4, to the slot's position record.
// HYPOTHESIS: springs; the roles are UNKNOWN. The signature agrees with the declaration in
// src/rel/itembaloon_player.cpp.

struct Vec800E0CC8 {
	f32 x;
	f32 y;
	f32 z;
};

struct Angle800E0CC8 {
	s32 x;
	s32 y;
	s32 z;
};

struct Action800E0CC8 {
	s16 mode; // 0x0
	u8 pad2[0x4 - 0x2];
	s16 action; // 0x4
	s16 flags;  // 0x6
	u8 pad8[0xC - 0x8];
	Angle800E0CC8 angle; // 0xC
};

struct Position800E0CC8 {
	Vec800E0CC8 position; // 0x0
	u8 padC[0x1C - 0xC];
	s32 yaw; // 0x1C
};

struct Team800E0CC8 {
	u8 pad0[0x121];
	s8 count; // 0x121
	u8 pad122[0x140 - 0x122];
	s32 state; // 0x140
};

struct Record800E0CC8 {
	u8 pad0[0x14];
	s16 unknown14; // 0x14
	u8 pad16[0x24 - 0x16];
	s32 unknown24; // 0x24
	u8 pad28[0x60 - 0x28];
	Vec800E0CC8 point; // 0x60
	u8 pad6C[0x150 - 0x6C];
	s16 unknown150; // 0x150
	u8 pad152[0x258 - 0x152];
	Team800E0CC8* team; // 0x258
};

extern "C" {
extern Action800E0CC8* lbl_802AD090[];
extern Position800E0CC8* lbl_802AD0B0[];
extern Record800E0CC8* lbl_802AD0D0[];
extern const f32 lbl_8042E1F0; // 0.0f
struct Stage800E0CC8 {
	u8 pad0[0x2C];
	s32 stage; // 0x2C
};
extern Stage800E0CC8 lbl_8029C310;
extern void* lbl_802AD070[];
s32 fn_800AB35C(void* player);
void fn_8003E9B4(Action800E0CC8* action, Vec800E0CC8* point);
}

extern "C" s32 fn_800E0CC8(s32 idx, f32 speed, const Angle800E0CC8* angle, s32 value)
{
	Action800E0CC8* action     = lbl_802AD090[idx];
	Position800E0CC8* position = lbl_802AD0B0[idx];
	Record800E0CC8* record     = lbl_802AD0D0[idx];

	if ((action->flags & 0x1000) && action->action == 0x3F) {
		return 0;
	}
	if (lbl_802AD070[idx] == NULL || fn_800AB35C(lbl_802AD070[idx])) {
		return 0;
	}
	record->unknown14 = (s16)value;
	action->flags |= 0x1000;
	switch (lbl_8029C310.stage) {
		case 6:
		case 7:
		case 0x27:
		case 0x2C:
			if (action->mode == 0x12 || action->mode == 0x28) {
				action->action = 0x3D;
				break;
			}
			// fall through
		default: {
			action->action     = 6;
			Team800E0CC8* team = record->team;
			if (team->state == 2 || team->state == 3) {
				record->unknown24 = record->unknown150;
			} else {
				record->unknown24 = 0xB;
			}
			break;
		}
	}
	Vec800E0CC8 velocity;
	velocity.x      = lbl_8042E1F0;
	velocity.y      = speed;
	velocity.z      = lbl_8042E1F0;
	record->point.x = velocity.x;
	record->point.y = velocity.y;
	record->point.z = velocity.z;
	action->angle.x = angle->x;
	action->angle.y = 0x4000 - angle->y;
	position->yaw   = action->angle.y;
	action->angle.z = angle->z;
	fn_8003E9B4(action, &velocity);
	position->position.x = velocity.x;
	position->position.y = velocity.y;
	position->position.z = velocity.z;
	return 1;
}
