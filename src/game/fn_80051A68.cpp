#include "game/misc.h"

// Runs the current team's area triggers (the first argument is the trigger owner): the team
// (lbl_80303DC8[lbl_8042C1FC]) member +0x3C picks the slot whose action position (+0x18 of
// lbl_802AD090) is tested, and the team formation (fn_80091FAC: 0, 1, 2) the mask bit 1, 4 or 2.
// For each area (fn_8004E608 / fn_8004E5AC), sphere areas (kind 1, fn_8004DD84) and box areas
// (kind 3; fn_8005110C) whose mask (+0x8 of fn_8004DD18) has the bit and that contain the point
// are kept; the others are ended with fn_8004DE10. fn_80050D40 runs afterwards. HYPOTHESIS: the
// roles (formation-specific triggers) are UNKNOWN.
// NonMatching (one instruction long, then shifted): retail compares the area kind with 5 and
// branches to the loop end without a beq (MWCC keeps one for case 5), and swaps the mask/index
// registers (r28/r29). The loop is written with a top test as in the retail code. Tried: case 5
// with default, goto, the switch as an inline.

struct Angle80051A68 {
	s32 x;
	s32 y;
	s32 z;
};

struct Box80051A68 {
	RwV3d* center;        // 0x0
	RwV3d* extent;        // 0x4
	Angle80051A68* angle; // 0x8
	RwV3d* point;         // 0xC
};

struct Area80051A68 {
	u8 pad0[0x8];
	s32 mask; // 0x8
	u8 padC[0x14 - 0xC];
	RwV3d center;        // 0x14
	Angle80051A68 angle; // 0x20
	RwV3d extent;        // 0x2C
};

struct Team80051A68 {
	u8 pad0[0x3C];
	s8 member; // 0x3C
	u8 pad3D[0x110 - 0x3D];
	s8 slots[4]; // 0x110
};

struct Action80051A68 {
	u8 pad0[0x18];
	RwV3d position; // 0x18
};

extern "C" {
extern Team80051A68* lbl_80303DC8[4];
extern Action80051A68* lbl_802AD090[];
extern s32 lbl_8042C1FC;
s32 fn_80091FAC(Team80051A68* team);
s32 fn_8004E608(void* owner);
s32 fn_8004E5AC(void* owner, s32 index);
s32 fn_8004DD84(void* owner, s32 index);
Area80051A68* fn_8004DD18(void* owner, s32 index);
void fn_8004DE10(void* owner, s32 index);
void fn_80050D40(void* owner);
s32 fn_8005110C(void* owner, Box80051A68* box);
}

static inline BOOL InSphere(const Box80051A68* box)
{
	RwV3d offset;
	SubVectorReturnToVector(box->point, box->center, &offset);
	if (offset.z * offset.z + (offset.x * offset.x + offset.y * offset.y) < box->extent->z) {
		return TRUE;
	}
	return FALSE;
}

extern "C" void fn_80051A68(void* owner)
{
	Team80051A68* team = lbl_80303DC8[lbl_8042C1FC];
	s32 slot           = team->slots[team->member];
	s32 mask;
	s32 index;
	Box80051A68 box;

	switch (fn_80091FAC(team)) {
		case 0:
			mask = 1;
			break;
		case 1:
			mask = 4;
			break;
		case 2:
			mask = 2;
			break;
	}
	index = fn_8004E608(owner);
	for (;;) {
		if (index <= 0) {
			break;
		}
		switch (fn_8004DD84(owner, index)) {
			case 1: {
				Area80051A68* area = fn_8004DD18(owner, index);
				box.center         = &area->center;
				box.extent         = &area->extent;
				box.point          = &lbl_802AD090[slot]->position;
				if (!(area->mask & mask) || !InSphere(&box)) {
					fn_8004DE10(owner, index);
				}
				break;
			}
			case 3: {
				Area80051A68* area = fn_8004DD18(owner, index);
				box.center         = &area->center;
				box.extent         = &area->extent;
				box.angle          = &area->angle;
				box.point          = &lbl_802AD090[slot]->position;
				if (!(area->mask & mask) || !fn_8005110C(owner, &box)) {
					fn_8004DE10(owner, index);
				}
				break;
			}
			case 5:
				break;
		}
		index = fn_8004E5AC(owner, index);
	}
	fn_80050D40(owner);
}
