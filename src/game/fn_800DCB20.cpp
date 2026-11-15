#include "game/rw_types.h"

// Computes a player's acceleration on a wall-run (record +0x54; see fn_800DBCB4): the base
// acceleration (+0xC of the motion) plus gravity (lbl_80242B38 times +0x140) in the action's frame
// (fn_8003EB18) plus the speed (+0x60) times the per-axis factors (+0x118/+0x120/+0x124). Without a
// wall (fn_800E27D8) or with wall attribute 0x40000 (+0x98) the push is lbl_8042E09C and the motion
// yaw (+0x1C) keeps the action's angle (+0x10); otherwise the motion yaw follows the wall unless
// the player is fast (+0x60 over +0xF0) and more than 0x6000 off it (the push then scales by
// +0x114), the push is the wall strength times +0x108 (and lbl_8042E0CC while the motion's +0x4 is
// below lbl_8042E09C outside busy stages) within 0x1000, else lbl_8042E09C, and fn_800E1A48 runs.
// The push is added on X. HYPOTHESIS: the roles are UNKNOWN.

struct Action800DCB20 {
	u8 pad0[0x10];
	s32 angle; // 0x10
};

struct Motion800DCB20 {
	u8 pad0[0x4];
	f32 unknown4; // 0x4
	u8 pad8[0xC - 0x8];
	RwV3d acceleration; // 0xC
	u8 pad18[0x1C - 0x18];
	s32 yaw; // 0x1C
};

struct Record800DCB20 {
	u8 pad0[0x54];
	RwV3d acceleration; // 0x54
	RwV3d speed;        // 0x60
	u8 pad6C[0x98 - 0x6C];
	u32 attributes; // 0x98
	u8 pad9C[0xF0 - 0x9C];
	f32 speedLimit; // 0xF0
	u8 padF4[0x108 - 0xF4];
	f32 push; // 0x108
	u8 pad10C[0x114 - 0x10C];
	f32 fastPush; // 0x114
	f32 dragX;    // 0x118
	u8 pad11C[0x120 - 0x11C];
	f32 dragY; // 0x120
	f32 dragZ; // 0x124
	u8 pad128[0x140 - 0x128];
	f32 gravity; // 0x140
};

struct Gravity800DCB20 {
	RwV3d direction; // 0x0
	u8 padC[0x10 - 0xC];
};

extern "C" {
extern Gravity800DCB20 lbl_80242B38;
extern u8 lbl_8029C310[];
extern const f32 lbl_8042E09C;
extern const f32 lbl_8042E0CC;
void fn_8003EB18(Action800DCB20* action, RwV3d* vector);
s32 fn_800E27D8(Action800DCB20* action, Record800DCB20* record, s32* angle, f32* strength);
s32 fn_80018EA8(void* stage);
void fn_800E1A48(Action800DCB20* action, Motion800DCB20* motion, Record800DCB20* record, s32 yaw);
}

// game/misc.h declares DiffAngle returning u16; the callers use the full register.
s32 DiffAngle(s32 first, s32 second);

extern "C" void fn_800DCB20(Action800DCB20* action, Motion800DCB20* motion, Record800DCB20* record)
{
	RwV3d a;
	s32 angle;
	f32 push;

	a   = motion->acceleration;
	a.x = a.x + lbl_80242B38.direction.x * record->gravity;
	a.y = a.y + lbl_80242B38.direction.y * record->gravity;
	a.z = a.z + lbl_80242B38.direction.z * record->gravity;
	fn_8003EB18(action, &a);
	a.x += record->dragX * record->speed.x;
	a.y += record->dragY * record->speed.y;
	a.z += record->dragZ * record->speed.z;
	if (fn_800E27D8(action, record, &angle, &push) == 0 || (record->attributes & 0x40000)) {
		push        = lbl_8042E09C;
		motion->yaw = action->angle;
	} else {
		s32 diff = DiffAngle(action->angle, angle);
		if (record->speed.x > record->speedLimit && diff > 0x6000) {
			push = record->fastPush * push;
		} else if (diff > 0x1000) {
			motion->yaw = angle;
			push        = lbl_8042E09C;
		} else {
			motion->yaw = angle;
			if (motion->unknown4 < lbl_8042E09C && fn_80018EA8(lbl_8029C310) == 0) {
				push = lbl_8042E0CC * (record->push * push);
			} else {
				push = record->push * push;
			}
		}
		fn_800E1A48(action, motion, record, motion->yaw);
	}
	a.x += push;
	record->acceleration = a;
}
