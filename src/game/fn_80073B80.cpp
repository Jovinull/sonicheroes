#include "types.h"

struct Player73B80 {
	u8 pad0[0xA4A];
	s8 flags; // 0xA4A
	u8 pad1[0xA50 - 0xA4B];
	f32 x;    // 0xA50
	f32 y;    // 0xA54
	f32 z;    // 0xA58
	f32 fA5C; // 0xA5C
};

struct Obj73B80A {
	s16 f0; // 0x0
	u8 pad2[0x6 - 0x2];
	s16 f6; // 0x6
	u8 pad8[0xC - 0x8];
	s32 fC; // 0xC
	u8 pad10[0x14 - 0x10];
	s32 f14; // 0x14
	f32 fx;  // 0x18
	f32 fy;  // 0x1C
	f32 fz;  // 0x20
};

struct Obj73B80B {
	u8 pad0[0x18];
	s32 f18; // 0x18
	u8 pad1[0x20 - 0x1C];
	s32 f20; // 0x20
};

struct State73B80 {
	s8 playerNo;  // 0x0
	s8 character; // 0x1
	u8 pad2[0x64 - 0x2];
	f32 f64; // 0x64
	u8 pad3[0x14E - 0x68];
	s16 f14E; // 0x14E
};

extern "C" {
extern f32 lbl_8042D624;
extern f32 lbl_8042D64C;
int fn_800E259C(Player73B80* o);
void fn_80137D0C(s32 voice, s32 character, s32 player);

void fn_80073B80(Player73B80* p, Obj73B80A* a, Obj73B80B* b, State73B80* s)
{
	s16 flags;

	s->f64  = lbl_8042D64C;
	a->fC   = 0;
	b->f18  = 0;
	a->f14  = 0;
	b->f20  = 0;
	p->x    = a->fx;
	p->y    = a->fy;
	p->z    = a->fz;
	flags   = a->f6;
	a->f6   = flags & ~0x2500;
	a->f0   = 0x34;
	s->f14E = 0x41;
	p->flags |= 1;
	p->fA5C = lbl_8042D624;
	if (fn_800E259C(p) != 0) {
		fn_80137D0C(9, s->character, s->playerNo);
	}
}
}
