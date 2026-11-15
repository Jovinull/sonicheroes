// Per-frame reset of a player record: clears action flags 0x1238 (+0x6F6) and the half-word at
// +0x6F4, zeroes the vectors at +0x72C, +0x7A8 and +0x7B4 and the float at +0x794, counts the
// timers at +0x774/+0x77A (16-bit, floored at 0) and +0x9E8 (8-bit) down, and records the player
// slot's position and angle (lbl_802AD090[number]) into the next entry of the history rings
// lbl_8042C1B0/lbl_8042C1B4 (read back by fn_8003E2E4). It then clears +0x776 and lbl_8042C1B8.
// Field roles are HYPOTHESIS/UNKNOWN.
// NonMatching (one instruction short, 23 words shifted): the retail code zero-extends the player
// number again (clrlwi) before the `<< 8` of the ring index although it was loaded with lbz.
// Tried: (u8) casts, s32/int/u32 locals, an inline index helper with u8 parameters.
#include "types.h"

struct Vec8003EC84 {
	f32 x;
	f32 y;
	f32 z;
};

struct Angle8003EC84 {
	s32 x;
	s32 y;
	s32 z;
};

// Player slot record of lbl_802AD090 (see fn_800DFF34).
struct Slot8003EC84 {
	u8 pad0[0xC];
	Angle8003EC84 angle;  // 0xC
	Vec8003EC84 position; // 0x18
};

struct Player8003EC84 {
	u8 pad0[0x6F4];
	s16 unknown6F4; // 0x6F4
	s16 flags;      // 0x6F6
	u8 pad6F8[0x72C - 0x6F8];
	Vec8003EC84 unknown72C; // 0x72C
	u8 pad738[0x760 - 0x738];
	u8 number; // 0x760
	u8 pad761[0x774 - 0x761];
	s16 timer774;   // 0x774
	s16 unknown776; // 0x776
	u8 pad778[2];
	s16 timer77A; // 0x77A
	u8 pad77C[0x794 - 0x77C];
	f32 unknown794; // 0x794
	u8 pad798[0x7A8 - 0x798];
	Vec8003EC84 unknown7A8; // 0x7A8
	Vec8003EC84 unknown7B4; // 0x7B4
	u8 pad7C0[0x9E8 - 0x7C0];
	s8 timer9E8; // 0x9E8
};

extern "C" {
extern f32 lbl_8042D120; // 0.0f
extern Slot8003EC84* lbl_802AD090[8];
extern u8 lbl_8042C1A8[8];
extern Vec8003EC84* lbl_8042C1B0;
extern Angle8003EC84* lbl_8042C1B4;
extern s32 lbl_8042C1B8;

void fn_8003EC84(Player8003EC84* p)
{
	Slot8003EC84* slot;
	u8 number;
	u8 entry;

	p->flags &= ~0x1238;
	p->unknown6F4 = 0;
	p->unknown794 = p->unknown7A8.x = p->unknown7A8.y = p->unknown7A8.z = p->unknown7B4.x
	    = p->unknown7B4.y = p->unknown7B4.z = p->unknown72C.x = p->unknown72C.y = p->unknown72C.z
	    = lbl_8042D120;
	if (p->timer774 > 0) {
		p->timer774--;
	} else {
		p->timer774 = 0;
	}
	if (p->timer77A > 0) {
		p->timer77A--;
	} else {
		p->timer77A = 0;
	}
	if (p->timer9E8 > 0) {
		p->timer9E8--;
	}
	number                              = p->number;
	slot                                = lbl_802AD090[number];
	entry                               = ++lbl_8042C1A8[number];
	lbl_8042C1B0[entry + (number << 8)] = slot->position;
	lbl_8042C1B4[entry + (number << 8)] = slot->angle;
	p->unknown776                       = 0;
	lbl_8042C1B8                        = 0;
}
}
