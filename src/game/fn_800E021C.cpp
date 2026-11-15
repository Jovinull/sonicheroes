#include "types.h"

// fn_800E03B4 for action 0x32: puts player slot idx into action 0x32 at a given point and angle
// (same refusals, the given value as an s16 at +0x14 of the record), with the record's +0x24 set
// from the team (+0x258): 10 unless the team state (+0x140) is 2 or 3 with more than one member
// (+0x121), then 0x40 in mode 0x1D (action state +0x0) or the record's +0x150 otherwise.
// HYPOTHESIS: the roles are UNKNOWN.

struct Vec800E021C {
	f32 x;
	f32 y;
	f32 z;
};

struct Angle800E021C {
	s32 x;
	s32 y;
	s32 z;
};

struct Action800E021C {
	s16 mode; // 0x0
	u8 pad2[0x4 - 0x2];
	s16 action; // 0x4
	s16 flags;  // 0x6
	u8 pad8[0xC - 0x8];
	Angle800E021C angle; // 0xC
};

struct Position800E021C {
	Vec800E021C position; // 0x0
	u8 padC[0x1C - 0xC];
	s32 yaw; // 0x1C
};

struct Team800E021C {
	u8 pad0[0x121];
	s8 count; // 0x121
	u8 pad122[0x140 - 0x122];
	s32 state; // 0x140
};

struct Record800E021C {
	u8 pad0[0x14];
	s16 unknown14; // 0x14
	u8 pad16[0x24 - 0x16];
	s32 unknown24; // 0x24
	u8 pad28[0x60 - 0x28];
	Vec800E021C point; // 0x60
	u8 pad6C[0x150 - 0x6C];
	s16 unknown150; // 0x150
	u8 pad152[0x258 - 0x152];
	Team800E021C* team; // 0x258
};

extern "C" {
extern Action800E021C* lbl_802AD090[];
extern Position800E021C* lbl_802AD0B0[];
extern Record800E021C* lbl_802AD0D0[];
extern void* lbl_802AD070[];
s32 fn_800AB35C(void* player);
void fn_8003E9B4(Action800E021C* action, Vec800E021C* point);
}

extern "C" void fn_800E021C(
    s32 idx, const Vec800E021C* point, const Angle800E021C* angle, s32 value)
{
	Action800E021C* action     = lbl_802AD090[idx];
	Position800E021C* position = lbl_802AD0B0[idx];
	Record800E021C* record     = lbl_802AD0D0[idx];

	if (((action->flags & 0x1000) && action->action == 0x3F) || lbl_802AD070[idx] == NULL
	    || fn_800AB35C(lbl_802AD070[idx])) {
		return;
	}
	record->unknown14 = (s16)value;
	action->flags |= 0x1000;
	action->action     = 0x32;
	Team800E021C* team = record->team;
	if (team->state == 2 || team->state == 3) {
		if (team->count <= 1) {
			record->unknown24 = 10;
		} else if (action->mode == 0x1D) {
			record->unknown24 = 0x40;
		} else {
			record->unknown24 = record->unknown150;
		}
	} else {
		record->unknown24 = 10;
	}
	record->point.x = point->x;
	record->point.y = point->y;
	record->point.z = point->z;
	action->angle.x = angle->x;
	action->angle.y = 0x4000 - angle->y;
	position->yaw   = action->angle.y;
	action->angle.z = angle->z;

	Vec800E021C filtered;
	filtered.x = point->x;
	filtered.y = point->y;
	filtered.z = point->z;
	fn_8003E9B4(action, &filtered);
	position->position.x = filtered.x;
	position->position.y = filtered.y;
	position->position.z = filtered.z;
}
