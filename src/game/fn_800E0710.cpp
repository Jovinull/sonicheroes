#include "types.h"

// fn_800E03B4 for action 0x28: puts player slot idx into action 0x28 at a given point and angle
// (same refusals, the given value as an s16 at +0x14 of the record, no +0x24), also mirrors the
// angle into the slot's position record (lbl_802AD0B0, +0x18..+0x20), and starts the dash effect
// (SetEffectDash) when the slot's player object is its team's current leader (team +0x258 of the
// record, members +0x114, current +0x3B). HYPOTHESIS: a dash panel or launcher; names UNKNOWN.

struct Vec800E0710 {
	f32 x;
	f32 y;
	f32 z;
};

struct Angle800E0710 {
	s32 x;
	s32 y;
	s32 z;
};

struct Action800E0710 {
	u8 pad0[0x4];
	s16 action; // 0x4
	s16 flags;  // 0x6
	u8 pad8[0xC - 0x8];
	Angle800E0710 angle; // 0xC
};

struct Position800E0710 {
	Vec800E0710 position; // 0x0
	u8 padC[0x18 - 0xC];
	Angle800E0710 angle; // 0x18
};

struct Team800E0710 {
	u8 pad0[0x3B];
	s8 current; // 0x3B
	u8 pad3C[0x114 - 0x3C];
	void* members[3]; // 0x114
};

struct Record800E0710 {
	u8 pad0[0x14];
	s16 unknown14; // 0x14
	u8 pad16[0x24 - 0x16];
	s32 unknown24; // 0x24
	u8 pad28[0x60 - 0x28];
	Vec800E0710 point; // 0x60
	u8 pad6C[0x258 - 0x6C];
	Team800E0710* team; // 0x258
};

extern "C" {
extern Action800E0710* lbl_802AD090[];
extern Position800E0710* lbl_802AD0B0[];
extern Record800E0710* lbl_802AD0D0[];
extern void* lbl_802AD070[];
s32 fn_800AB35C(void* player);
void fn_8003E9B4(Action800E0710* action, Vec800E0710* point);
}

void SetEffectDash(s32 idx);

extern "C" void fn_800E0710(
    s32 idx, const Vec800E0710* point, const Angle800E0710* angle, s32 value)
{
	Action800E0710* action     = lbl_802AD090[idx];
	Position800E0710* position = lbl_802AD0B0[idx];
	Record800E0710* record     = lbl_802AD0D0[idx];

	if (((action->flags & 0x1000) && action->action == 0x3F) || lbl_802AD070[idx] == NULL
	    || fn_800AB35C(lbl_802AD070[idx])) {
		return;
	}
	record->unknown14 = (s16)value;
	action->flags |= 0x1000;
	action->action    = 0x28;
	record->point.x   = point->x;
	record->point.y   = point->y;
	record->point.z   = point->z;
	position->angle.x = action->angle.x = angle->x;
	action->angle.y                     = 0x4000 - angle->y;
	position->angle.y                   = action->angle.y;
	position->angle.z = action->angle.z = angle->z;

	Vec800E0710 filtered;
	filtered.x = point->x;
	filtered.y = point->y;
	filtered.z = point->z;
	fn_8003E9B4(action, &filtered);
	position->position.x = filtered.x;
	position->position.y = filtered.y;
	position->position.z = filtered.z;
	Team800E0710* team   = record->team;
	if (lbl_802AD070[idx] == team->members[team->current]) {
		SetEffectDash(idx);
	}
}
