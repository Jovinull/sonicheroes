#include "game/rw_types.h"

// Computes a player's acceleration along a rail (HYPOTHESIS: grinding; see fn_800DCB20 and
// fn_800E1F28): skipped with action flag 0x4000 (+0x6) or without a rail direction
// (fn_8004102C). The side (1 for wall classes 4 and up of fn_800E1F28, -1 for class 1, else 0)
// picks the push: the wall strength (fn_800E27D8) times +0x104, or +0x10C with no wall. The yaw
// (+0x73C, also the action's yaw) follows the rail on the gravity plane. The acceleration is
// gravity (lbl_80242B38 times +0x140) in the action's frame (fn_8003EB18) plus the speed (+0x60)
// times +0x11C plus the push; at rest and with no wall it is dropped while within the slope
// friction (Y times +0x130). Its X goes to +0x54 signed by the side, or against the speed. One
// vector holds the rail direction and then the acceleration (the retail stack slot).
// NonMatching (6 words, float registers only): in the no-side tail retail rounds |X| into f1 and
// loads 0 into f0 (MWCC: f0 and f1). Temporaries for the magnitude, the speed and the constant,
// an inline fabsf and double temporaries did not change it.

struct Gravity800DC8B4 {
	RwV3d direction; // 0x0
	u8 padC[0x10 - 0xC];
};

struct Action800DC8B4 {
	u8 pad0[0x6];
	s16 flags; // 0x6
	u8 pad8[0x10 - 0x8];
	s32 yaw; // 0x10
};

struct Record800DC8B4 {
	u8 pad0[0x54];
	f32 acceleration; // 0x54
	u8 pad58[0x60 - 0x58];
	f32 speed; // 0x60
	u8 pad64[0x104 - 0x64];
	f32 wallPush; // 0x104
	u8 pad108[0x10C - 0x108];
	f32 push; // 0x10C
	u8 pad110[0x11C - 0x110];
	f32 drag; // 0x11C
	u8 pad120[0x130 - 0x120];
	f32 friction; // 0x130
	u8 pad134[0x140 - 0x134];
	f32 gravity; // 0x140
};

struct Player800DC8B4 {
	u8 pad0[0x6F0];
	Action800DC8B4 action; // 0x6F0
	u8 pad704[0x73C - 0x704];
	s32 yaw; // 0x73C
	u8 pad740[0x760 - 0x740];
	Record800DC8B4 record; // 0x760
};

extern "C" {
extern Gravity800DC8B4 lbl_80242B38;
extern const f32 lbl_8042E098; // radians to 16-bit angle units
extern const f32 lbl_8042E09C; // 0.0f
double atan2(double y, double x);
f64 __fabs(f64 x);
s32 fn_800E1F28(Player800DC8B4* player);
s32 fn_8004102C(Player800DC8B4* player, RwV3d* direction);
void fn_8003EB18(Action800DC8B4* action, RwV3d* vector);
s32 fn_800E27D8(Action800DC8B4* action, Record800DC8B4* record, s32* angle, f32* strength);
}

extern "C" void fn_800DC8B4(Player800DC8B4* player)
{
	s32 side;
	Action800DC8B4* action;
	RwV3d a;
	f32 push;

	action = &player->action;

	if (action->flags & 0x4000) {
		return;
	}
	s32 wall = fn_800E1F28(player);
	if (wall >= 4) {
		side = 1;
	} else if (wall == 1) {
		side = -1;
	} else {
		side = 0;
	}
	if (fn_8004102C(player, &a) == 0) {
		return;
	}
	if (lbl_80242B38.direction.y > lbl_8042E09C) {
		player->yaw = (u16)(s32)(lbl_8042E098 * (f32)atan2(-a.z, a.x));
	} else {
		player->yaw = (u16)(s32)(lbl_8042E098 * (f32)atan2(-a.z, -a.x));
	}
	action->yaw            = player->yaw;
	Record800DC8B4* record = &player->record;
	a.x = a.y = a.z = lbl_8042E09C;
	a.x             = a.x + lbl_80242B38.direction.x * record->gravity;
	a.y             = a.y + lbl_80242B38.direction.y * record->gravity;
	a.z             = a.z + lbl_80242B38.direction.z * record->gravity;
	fn_8003EB18(action, &a);
	a.x = a.x + record->drag * record->speed;
	if (side == 0) {
		push = record->push;
	} else {
		fn_800E27D8(action, record, NULL, &push);
		push = record->wallPush * push;
	}
	f32 x = a.x + push;
	a.x   = x;
	if (lbl_8042E09C == record->speed) {
		f32 limit = a.y * record->friction;
		if (side == 0 && x < limit && x > -limit) {
			a.x = lbl_8042E09C;
		}
	}
	if (side > 0) {
		record->acceleration = a.x;
	} else if (side < 0) {
		record->acceleration = -a.x;
	} else {
		a.x = __fabs(a.x);
		if (record->speed > lbl_8042E09C) {
			record->acceleration = -a.x;
		} else if (record->speed < lbl_8042E09C) {
			record->acceleration = a.x;
		}
	}
}
