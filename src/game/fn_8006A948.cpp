#include "types.h"

// Lands a player on an object (third argument unused): refused (0) while the play-mode flags 31 or
// 32 (lbl_8042C180) are set for any other team than the player's (+0x9BC), or when fn_800E22AC
// rejects the action/object pair. Actions 4 and 10 only set the object's state +0x14E to 0x39;
// others copy the object's +0xE0 to +0x64, call fn_8004675C and, unless the object has flag 0x2
// (+0x22C) with its two heights (+0x23C, +0x240) more than lbl_8042D510 apart, fn_80046A04. The
// action then becomes 2 with flag 0x400 set and 0x2500 and 0x2 cleared, and the object's +0x12 is
// cleared. Returns 1. HYPOTHESIS: the roles are UNKNOWN.

struct Player8006A948 {
	u8 pad0[0x9BC];
	s8 team; // 0x9BC
};

struct Action8006A948 {
	s16 action; // 0x0
	u8 pad2[0x6 - 0x2];
	s16 flags; // 0x6
};

struct Object8006A948 {
	u8 pad0[0x12];
	s16 unknown12; // 0x12
	u8 pad14[0x64 - 0x14];
	f32 unknown64; // 0x64
	u8 pad68[0xE0 - 0x68];
	f32 unknownE0; // 0xE0
	u8 padE4[0x14E - 0xE4];
	s16 state; // 0x14E
	u8 pad150[0x22C - 0x150];
	u32 flags; // 0x22C
	u8 pad230[0x23C - 0x230];
	f32 height23C; // 0x23C
	f32 height240; // 0x240
};

struct PlayMode8006A948 {
	s8 flags[44];
};

extern "C" {
extern PlayMode8006A948* lbl_8042C180;
extern const f32 lbl_8042D510;
double __fabs(double x);
s32 fn_800E22AC(Action8006A948* action, Object8006A948* object);
void fn_8004675C(Player8006A948* player);
void fn_80046A04(Player8006A948* player);
}

static inline BOOL HeightsApart(const Object8006A948* object)
{
	if ((object->flags & 0x2)
	    && (f32)__fabs(object->height23C - object->height240) > lbl_8042D510) {
		return TRUE;
	}
	return FALSE;
}

extern "C" s32 fn_8006A948(
    Player8006A948* player, Action8006A948* action, void* unused, Object8006A948* object)
{
	s32 others = ~(1 << player->team);

	if ((others & lbl_8042C180->flags[31]) || (others & lbl_8042C180->flags[32])) {
		return 0;
	}
	if (fn_800E22AC(action, object)) {
		if (action->action == 4 || action->action == 10) {
			object->state = 0x39;
		} else {
			object->unknown64 = object->unknownE0;
			fn_8004675C(player);
			if (!HeightsApart(object)) {
				fn_80046A04(player);
			}
		}
		action->action = 2;
		action->flags &= ~0x2500;
		action->flags |= 0x400;
		action->flags &= ~0x2;
		object->unknown12 = 0;
		return 1;
	}
	return 0;
}
