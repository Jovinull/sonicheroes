#include "types.h"

// Puts player slot idx into action 0x10 at a given point and angle, unless it is already in action
// 0x3F with the action flag 0x1000 set, the slot has no player object (lbl_802AD070), or
// fn_800AB35C says its current state cannot be interrupted. It stores the given value as an s16 at
// +0x14 and 0x37 at +0x24 of the slot's record (lbl_802AD0D0), the point at +0x60, the angle in the
// action state (as fn_800E01E4 does), and the point, filtered by fn_8003E9B4, as the slot's
// position (lbl_802AD0B0). HYPOTHESIS: a forced warp/launch; the field names are UNKNOWN.

struct Vec800E03B4 {
	f32 x;
	f32 y;
	f32 z;
};

struct Angle800E03B4 {
	s32 x;
	s32 y;
	s32 z;
};

struct Action800E03B4 {
	u8 pad0[0x4];
	s16 action; // 0x4
	s16 flags;  // 0x6
	u8 pad8[0xC - 0x8];
	Angle800E03B4 angle; // 0xC
};

struct Position800E03B4 {
	Vec800E03B4 position; // 0x0
	u8 padC[0x1C - 0xC];
	s32 yaw; // 0x1C
};

struct Record800E03B4 {
	u8 pad0[0x14];
	s16 unknown14; // 0x14
	u8 pad16[0x24 - 0x16];
	s32 unknown24; // 0x24
	u8 pad28[0x60 - 0x28];
	Vec800E03B4 point; // 0x60
};

extern "C" {
extern Action800E03B4* lbl_802AD090[];
extern Position800E03B4* lbl_802AD0B0[];
extern Record800E03B4* lbl_802AD0D0[];
extern void* lbl_802AD070[];
s32 fn_800AB35C(void* player);
void fn_8003E9B4(Action800E03B4* action, Vec800E03B4* point);
}

extern "C" void fn_800E03B4(
    s32 idx, const Vec800E03B4* point, const Angle800E03B4* angle, s32 value)
{
	Action800E03B4* action     = lbl_802AD090[idx];
	Position800E03B4* position = lbl_802AD0B0[idx];
	Record800E03B4* record     = lbl_802AD0D0[idx];

	if (((action->flags & 0x1000) && action->action == 0x3F) || lbl_802AD070[idx] == NULL
	    || fn_800AB35C(lbl_802AD070[idx])) {
		return;
	}
	record->unknown14 = (s16)value;
	action->flags |= 0x1000;
	action->action    = 0x10;
	record->unknown24 = 0x37;
	record->point.x   = point->x;
	record->point.y   = point->y;
	record->point.z   = point->z;
	action->angle.x   = angle->x;
	action->angle.y   = 0x4000 - angle->y;
	position->yaw     = action->angle.y;
	action->angle.z   = angle->z;

	Vec800E03B4 filtered;
	filtered.x = point->x;
	filtered.y = point->y;
	filtered.z = point->z;
	fn_8003E9B4(action, &filtered);
	position->position.x = filtered.x;
	position->position.y = filtered.y;
	position->position.z = filtered.z;
}
