// PS2 name: TObjOldPlayer::UpdateFrame_SetFormationEffect (medium)
#include "types.h"

struct V3_8003DEA4 {
	f32 x, y, z;
};
struct Mtx_8003DEA4 {
	u8 raw[0x40];
};
struct Frame_8003DEA4 {
	u8 pad[0x10];
	Mtx_8003DEA4 m;
};
struct Team_8003DEA4;
struct Obj_8003DEA4 {
	u8 pad0[0x628];
	s32 f628;
	u8 pad1[0x644 - 0x62C];
	s32 f644;
	u8 pad2[4];
	s32 f64c;
	u8 pad3[0x718 - 0x650];
	f32 f718;
	u8 pad4[0x761 - 0x71C];
	s8 f761;
	u8 pad5[0x89C - 0x762];
	f32 f89c;
	u8 pad6[0x8B0 - 0x8A0];
	s16 f8b0;
	u8 pad7[0x9B8 - 0x8B2];
	Team_8003DEA4* team;
};
struct Team_8003DEA4 {
	u8 pad0[0x3B];
	s8 f3b;
	u8 pad1[0x114 - 0x3C];
	Obj_8003DEA4* mem[9];
	Obj_8003DEA4* f138;
	Obj_8003DEA4* f13c;
	s32 f140;
	u8 pad2[0x154 - 0x144];
	s32 f154;
};

extern "C" {
f32 fn_800D7AE4(s32);
f32 fn_800D7B00(s32);
Mtx_8003DEA4* fn_80195790(Mtx_8003DEA4*, const V3_8003DEA4*, f32, f32, s32);
void fn_8019E880(Frame_8003DEA4*);
void fn_8019EB94(Frame_8003DEA4*, V3_8003DEA4*, s32);
void fn_8019EC30(Frame_8003DEA4*, V3_8003DEA4*, s32);
extern V3_8003DEA4 AxisX, AxisZ;
extern const f32 lbl_8042D0E8;
extern const f32 lbl_8042D0F4;
extern const f32 lbl_8042D120;
extern const f32 lbl_8042D140;
extern const f32 lbl_8042D144;

void fn_8003DEA4(Obj_8003DEA4* o, Frame_8003DEA4* fr, s32* a, s32* b, f32 unused, f32 scale)
{
	Team_8003DEA4* t = o->team;
	V3_8003DEA4 tr;
	V3_8003DEA4 sc;
	V3_8003DEA4* pt = &tr;
	f32 s;
	if (t->f154 == 9) {
		switch (o->f8b0) {
			case 0x52:
			case 0x1F:
				return;
		}
	}
	switch (t->f140) {
		case 3:
			*a = o->f644;
			*b = o->f64c;
			s  = fn_800D7B00(-*b);
			fn_80195790(&fr->m, &AxisZ, lbl_8042D0E8 - fn_800D7AE4(-*b), s, 1);
			s = fn_800D7B00(-*a);
			fn_80195790(&fr->m, &AxisX, lbl_8042D0E8 - fn_800D7AE4(-*a), s, 1);
			fn_8019E880(fr);
			break;
		case 2:
		case 7:
		case 8:
		case 9:
			*a = o->f644;
			*b = o->f64c;
			s  = fn_800D7B00(-*b);
			fn_80195790(&fr->m, &AxisZ, lbl_8042D0E8 - fn_800D7AE4(-*b), s, 1);
			s = fn_800D7B00(-*a);
			fn_80195790(&fr->m, &AxisX, lbl_8042D0E8 - fn_800D7AE4(-*a), s, 1);
			fn_8019E880(fr);
			break;
		case 1:
			if (o->f8b0 == 0x44) {
				f32 y = lbl_8042D140 * -o->f89c;
				tr.y  = y * o->f718;
				tr.z  = lbl_8042D120;
				tr.x  = lbl_8042D120;
				if (t->mem[t->f3b]->f761 == 0xA) {
					if (o->f761 == 9) {
						scale = lbl_8042D144;
					} else if (o->f761 == 0xB) {
						scale = lbl_8042D144;
					}
					if (t->f138 == o && t->f138->f628 == 0xC) {
						sc.y = lbl_8042D0E8;
						sc.z = lbl_8042D0F4;
						sc.x = lbl_8042D0F4;
						if (t->f13c != 0 && t->f13c->f628 == 0xC) {
							pt->x -= lbl_8042D0F4;
						}
						if (o->f761 == 9) {
							tr.y -= lbl_8042D0F4;
						}
					} else if (t->f13c == o && t->f13c->f628 == 0xC) {
						sc.y = lbl_8042D0E8;
						sc.z = lbl_8042D0F4;
						sc.x = lbl_8042D0F4;
						if (t->f138->f628 == 0xC) {
							pt->x += lbl_8042D0F4;
						}
						if (o->f761 == 9) {
							tr.y -= lbl_8042D0F4;
						}
					} else {
						sc.z = lbl_8042D0E8;
						sc.y = lbl_8042D0E8;
						sc.x = lbl_8042D0E8;
					}
					sc.x *= scale;
					sc.y *= scale;
					sc.z *= scale;
				} else {
					sc.x = lbl_8042D144;
					sc.y = lbl_8042D144;
					sc.z = lbl_8042D144;
				}
				fn_8019EC30(fr, &sc, 1);
				fn_8019EB94(fr, &tr, 1);
			}
			break;
	}
}
}
