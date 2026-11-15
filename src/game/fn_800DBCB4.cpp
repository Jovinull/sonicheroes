#include "game/rw_types.h"

// Computes a player's acceleration for the frame into the record's +0x54, unless the action has
// flag 0x4000: the motion's base acceleration (+0xC) plus gravity (lbl_80242B38 times the record's
// +0x140), turned into the action's frame (fn_8003EB18). With flag 0x2000 fn_800DB060 runs and,
// if the flag stays, Y loses lbl_8042E0DC, else Y becomes lbl_8042E09C. Above the speed limit
// (+0x60 over +0xF0) with +0x30 below lbl_8042E178, Y is scaled by lbl_8042E17C. The speed (+0x60)
// then adds drag per axis (+0x11C/+0x120/+0x124; on X lbl_8042E184 instead with flag 0x100 while
// +0x30 is at most lbl_8042E180). HYPOTHESIS: the field names are UNKNOWN.

struct Action800DBCB4 {
	u8 pad0[0x6];
	s16 flags; // 0x6
};

struct Motion800DBCB4 {
	u8 pad0[0xC];
	RwV3d acceleration; // 0xC
};

struct Record800DBCB4 {
	u8 pad0[0x30];
	f32 unknown30; // 0x30
	u8 pad34[0x54 - 0x34];
	RwV3d acceleration; // 0x54
	RwV3d speed;        // 0x60
	u8 pad6C[0xF0 - 0x6C];
	f32 speedLimit; // 0xF0
	u8 padF4[0x11C - 0xF4];
	RwV3d drag; // 0x11C
	u8 pad128[0x140 - 0x128];
	f32 gravity; // 0x140
};

struct Gravity800DBCB4 {
	RwV3d direction; // 0x0
	u8 padC[0x10 - 0xC];
};

extern "C" {
extern Gravity800DBCB4 lbl_80242B38;
extern const f32 lbl_8042E09C;
extern const f32 lbl_8042E0DC;
extern const f32 lbl_8042E178;
extern const f32 lbl_8042E17C;
extern const f32 lbl_8042E180;
extern const f32 lbl_8042E184;
void fn_8003EB18(Action800DBCB4* action, RwV3d* vector);
void fn_800DB060(Action800DBCB4* action, Motion800DBCB4* motion, Record800DBCB4* record);
}

extern "C" void fn_800DBCB4(Action800DBCB4* action, Motion800DBCB4* motion, Record800DBCB4* record)
{
	RwV3d a;
	a = motion->acceleration;
	if (action->flags & 0x4000) {
		return;
	}
	a.x = a.x + lbl_80242B38.direction.x * record->gravity;
	a.y = a.y + lbl_80242B38.direction.y * record->gravity;
	a.z = a.z + lbl_80242B38.direction.z * record->gravity;
	fn_8003EB18(action, &a);
	if (action->flags & 0x2000) {
		fn_800DB060(action, motion, record);
		if (action->flags & 0x2000) {
			a.y -= lbl_8042E0DC;
		} else {
			a.y = lbl_8042E09C;
		}
	}
	if (record->speed.x > record->speedLimit && record->unknown30 < lbl_8042E178) {
		a.y = lbl_8042E17C * a.y;
	}
	if (action->flags & 0x100) {
		if (record->unknown30 > lbl_8042E180) {
			a.x += record->drag.x * record->speed.x;
		} else {
			a.x += lbl_8042E184 * record->speed.x;
		}
	} else {
		a.x += record->drag.x * record->speed.x;
	}
	a.y += record->drag.y * record->speed.y;
	a.z += record->drag.z * record->speed.z;
	record->acceleration = a;
}
