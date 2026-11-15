#include "types.h"

// Puts player slot idx into action 4 with a given velocity, unless it is already in action 0x3F
// with flag 0x1000, it has no player object (lbl_802AD070) or fn_800AB35C refuses: the record's
// +0x24 (lbl_802AD0D0) becomes its +0x150 in team states 2 and 3 (team +0x258, +0x140) and 0xB
// otherwise; the velocity goes to the slot's position record (lbl_802AD0B0) and, turned into the
// action's frame (fn_8003EB18) with X and Z between lbl_8042E218 and lbl_8042E214 snapped to
// zero, to the record's +0x60. HYPOTHESIS: the roles are UNKNOWN (see fn_800E03B4).

struct Vec800E0E98 {
	f32 x;
	f32 y;
	f32 z;
};

struct Action800E0E98 {
	u8 pad0[0x4];
	s16 action; // 0x4
	s16 flags;  // 0x6
};

struct Team800E0E98 {
	u8 pad0[0x140];
	s32 state; // 0x140
};

struct Record800E0E98 {
	u8 pad0[0x24];
	s32 unknown24; // 0x24
	u8 pad28[0x60 - 0x28];
	Vec800E0E98 velocity; // 0x60
	u8 pad6C[0x150 - 0x6C];
	s16 unknown150; // 0x150
	u8 pad152[0x258 - 0x152];
	Team800E0E98* team; // 0x258
};

extern "C" {
extern Action800E0E98* lbl_802AD090[];
extern Vec800E0E98* lbl_802AD0B0[];
extern Record800E0E98* lbl_802AD0D0[];
extern void* lbl_802AD070[];
extern f32 lbl_8042E1F0; // 0.0f
extern f32 lbl_8042E214;
extern f32 lbl_8042E218;
s32 fn_800AB35C(void* player);
void fn_8003EB18(Action800E0E98* action, Vec800E0E98* velocity);
}

// Stores a velocity for slot idx (see fn_800E104C).
static inline void SetVelocity(s32 idx, f32 x, f32 y, f32 z)
{
	Action800E0E98* action = lbl_802AD090[idx];
	Vec800E0E98* position  = lbl_802AD0B0[idx];
	Record800E0E98* record = lbl_802AD0D0[idx];
	Vec800E0E98 local;

	position->x = x;
	position->y = y;
	position->z = z;
	local.x     = x;
	local.y     = y;
	local.z     = z;
	fn_8003EB18(action, &local);
	// Through a pointer: the retail code reloads the limits after each store.
	Vec800E0E98* v = &local;
	if (v->x <= lbl_8042E214 && v->x >= lbl_8042E218) {
		v->x = lbl_8042E1F0;
	}
	if (v->z <= lbl_8042E214 && v->z >= lbl_8042E218) {
		v->z = lbl_8042E1F0;
	}
	record->velocity.x = local.x;
	record->velocity.y = local.y;
	record->velocity.z = local.z;
}

extern "C" void fn_800E0E98(s32 idx, f32 x, f32 y, f32 z)
{
	Action800E0E98* action = lbl_802AD090[idx];

	if (((action->flags & 0x1000) && action->action == 0x3F) || lbl_802AD070[idx] == NULL
	    || fn_800AB35C(lbl_802AD070[idx])) {
		return;
	}
	action->flags |= 0x1000;
	action->action         = 4;
	Record800E0E98* record = lbl_802AD0D0[idx];
	if (record->team->state == 2 || record->team->state == 3) {
		record->unknown24 = record->unknown150;
	} else {
		record->unknown24 = 0xB;
	}
	SetVelocity(idx, x, y, z);
}
