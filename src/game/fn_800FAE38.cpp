#include "game/rw_types.h"

// Draws an object's shadow-like quad (fn_800B7514 between fn_800B7864(0) and fn_800B7820, with
// render state 0xE cleared and restored through fn_80194294/fn_80194234): not in state 6 (+0xE9)
// or without +0xEB. With a player slot (+0xE8) it is skipped while the slot is in action 0x27,
// its record (lbl_802AD0D0) state +0x150 is 0x1F/0x20 or 0x2B..0x2F or has flag 0x1000 (+0x10),
// or, with play-mode flag 30, when several players are active (lbl_8042C204) and the record's team
// (+0x25C) is not the current one, or lbl_8042C21C equals lbl_8042C224. Its size is lbl_8042E5E4
// minus lbl_8042E5E8 times the height above the floor (+0x124; the slot's +0x188 in action 0x2B,
// else +0x100) and it is drawn only while that stays above lbl_8042E5E8 (offset lbl_8023A750).
// HYPOTHESIS: the roles are UNKNOWN.
// NonMatching (one instruction short, then shifted): for the last guard retail branches over a
// `b exit` (bne ok; b exit) where MWCC branches straight to the exit (beq). Tried: && and ||
// forms, an else-return, gotos, a nested if.

struct Action800FAE38 {
	s16 mode; // 0x0
};

struct Record800FAE38 {
	u8 pad0[0x10];
	s16 flags; // 0x10
	u8 pad12[0x150 - 0x12];
	s16 state; // 0x150
	u8 pad152[0x25C - 0x152];
	s8 team; // 0x25C
};

struct Object800FAE38 {
	u8 pad0[0xE8];
	s8 slot;  // 0xE8
	s8 state; // 0xE9
	u8 padEA;
	s8 visible; // 0xEB
	u8 padEC[0x100 - 0xEC];
	f32 height100; // 0x100
	u8 pad104[0x120 - 0x104];
	RwV3d position;   // 0x120
	RwV3d unknown12C; // 0x12C
	u8 pad138[0x188 - 0x138];
	f32 height188; // 0x188
};

struct PlayMode800FAE38 {
	s8 flags[44];
};

extern "C" {
extern Action800FAE38* lbl_802AD090[];
extern Record800FAE38* lbl_802AD0D0[];
extern PlayMode800FAE38* lbl_8042C180;
extern s32 lbl_8042C204;
extern s32 lbl_8042C1FC;
extern s32 lbl_8042C21C;
extern s32 lbl_8042C224;
extern const RwV3d lbl_8023A750;
extern const f32 lbl_8042E5E4;
extern const f32 lbl_8042E5E8;
void fn_800B7864(s32 unknown);
void fn_80194294(s32 state, u32* value);
void fn_80194234(s32 state, u32 value);
void fn_800B7514(RwV3d* position, RwV3d* unknown, RwV3d* offset, f32 size);
void fn_800B7820(void);
}

extern "C" void fn_800FAE38(Object800FAE38* object)
{
	if (object->state == 6) {
		return;
	}
	if (object->visible == 0) {
		return;
	}
	RwV3d offset           = lbl_8023A750;
	Action800FAE38* action = NULL;
	if (object->slot != -1) {
		action = lbl_802AD090[object->slot];
		switch (action->mode) {
			case 0x27:
				return;
		}
		s32 multi;
		Record800FAE38* record;
		record = lbl_802AD0D0[object->slot];
		switch (record->state) {
			case 0x1F:
			case 0x20:
			case 0x2B:
			case 0x2C:
			case 0x2D:
			case 0x2E:
			case 0x2F:
				return;
		}
		if (record->flags & 0x1000) {
			return;
		}
		multi = lbl_8042C180->flags[30];
		if (multi != 0 && lbl_8042C204 > 1 && record->team != lbl_8042C1FC) {
			return;
		}
		if (multi == 0 || lbl_8042C21C - lbl_8042C224 != 0) {
		} else {
			return;
		}
	}
	f32 size;
	if (action != NULL && action->mode == 0x2B) {
		size = lbl_8042E5E4 - lbl_8042E5E8 * (object->height188 - object->position.y);
	} else {
		size = lbl_8042E5E4 - lbl_8042E5E8 * (object->height100 - object->position.y);
	}
	if (size <= lbl_8042E5E8) {
		return;
	}
	u32 old;
	fn_800B7864(0);
	fn_80194294(0xE, &old);
	fn_80194234(0xE, 0);
	fn_800B7514(&object->position, &object->unknown12C, &offset, size);
	fn_80194234(0xE, old);
	fn_800B7820();
}
