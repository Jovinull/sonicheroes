#include "types.h"

// fn_800E0710 for action 3 with an optional angle: when one is given it is set in the action state
// as fn_800E01E4 does (only the yaw mirrored into the slot's position record); the point, the
// filtered position and the dash effect for the team leader are as in fn_800E0710. HYPOTHESIS:
// the roles are UNKNOWN.

struct Vec800E0880 {
	f32 x;
	f32 y;
	f32 z;
};

struct Angle800E0880 {
	s32 x;
	s32 y;
	s32 z;
};

struct Action800E0880 {
	u8 pad0[0x4];
	s16 action; // 0x4
	s16 flags;  // 0x6
	u8 pad8[0xC - 0x8];
	Angle800E0880 angle; // 0xC
};

struct Position800E0880 {
	Vec800E0880 position; // 0x0
	u8 padC[0x18 - 0xC];
	Angle800E0880 angle; // 0x18
};

struct Team800E0880 {
	u8 pad0[0x3B];
	s8 current; // 0x3B
	u8 pad3C[0x114 - 0x3C];
	void* members[3]; // 0x114
};

struct Record800E0880 {
	u8 pad0[0x14];
	s16 unknown14; // 0x14
	u8 pad16[0x24 - 0x16];
	s32 unknown24; // 0x24
	u8 pad28[0x60 - 0x28];
	Vec800E0880 point; // 0x60
	u8 pad6C[0x258 - 0x6C];
	Team800E0880* team; // 0x258
};

extern "C" {
extern Action800E0880* lbl_802AD090[];
extern Position800E0880* lbl_802AD0B0[];
extern Record800E0880* lbl_802AD0D0[];
extern void* lbl_802AD070[];
s32 fn_800AB35C(void* player);
void fn_8003E9B4(Action800E0880* action, Vec800E0880* point);
}

void SetEffectDash(s32 idx);

extern "C" void fn_800E0880(
    s32 idx, const Vec800E0880* point, const Angle800E0880* angle, s32 value)
{
	Action800E0880* action     = lbl_802AD090[idx];
	Position800E0880* position = lbl_802AD0B0[idx];
	Record800E0880* record     = lbl_802AD0D0[idx];

	if (((action->flags & 0x1000) && action->action == 0x3F) || lbl_802AD070[idx] == NULL
	    || fn_800AB35C(lbl_802AD070[idx])) {
		return;
	}
	record->unknown14 = (s16)value;
	action->flags |= 0x1000;
	action->action  = 3;
	record->point.x = point->x;
	record->point.y = point->y;
	record->point.z = point->z;
	if (angle != NULL) {
		action->angle.x   = angle->x;
		action->angle.y   = 0x4000 - angle->y;
		position->angle.y = action->angle.y;
		action->angle.z   = angle->z;
	}

	Vec800E0880 filtered;
	filtered.x = point->x;
	filtered.y = point->y;
	filtered.z = point->z;
	fn_8003E9B4(action, &filtered);
	position->position.x = filtered.x;
	position->position.y = filtered.y;
	position->position.z = filtered.z;
	Team800E0880* team   = record->team;
	if (lbl_802AD070[idx] == team->members[team->current]) {
		SetEffectDash(idx);
	}
}
