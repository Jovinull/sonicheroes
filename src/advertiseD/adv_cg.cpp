#include "types.h"

// ADV_CG - the advertise-module movie/CG gallery classes.
//
// Module-relative .text 0xDAB0-0xEDB8 (~37 functions). Sub-classes
// ADV_MOVIE (vtable lbl_1_data_6364), ADV_CG_LST (vtable lbl_1_data_63A0)
// and ADV_CG (vtable lbl_1_data_63CC). Reference-guided from the PS2 debug
// build (semantic, not byte-identical). REL symbols are unmangled.

// ---- shared parameter block passed to ADV_CG_LST ctor (0x1c bytes) --------
struct sADV_CG_LIST {
	/* 0x00 */ void* spr;
	/* 0x04 */ f32 x0;
	/* 0x08 */ f32 y0;
	/* 0x0C */ f32 x1;
	/* 0x10 */ f32 y1;
	/* 0x14 */ s32 i14;
	/* 0x18 */ s32 i18;
}; // 0x1c

// ---- ADV_MOVIE (vtable 6364, size 0x98) -----------------------------------
struct ADV_MOVIE {
	/* 0x00 */ void* templ;
	/* 0x04 */ u8 _04[0x18 - 0x04];
	/* 0x18 */ void* vtable;
	/* 0x1C */ u8 _1c[0x1E - 0x1C];
	/* 0x1E */ u16 objsize;
	/* 0x20 */ u8 _20[0x28 - 0x20];
	/* 0x28 */ s32 i28;
	/* 0x2C */ s32 i2c;
	/* 0x30 */ u8 _30[0x40 - 0x30];
	/* 0x40 */ s32 i40;
	/* 0x44 */ s32 i44;
	/* 0x48 */ s32 i48;
	/* 0x4C */ u8 _4c[0x80 - 0x4C];
	/* 0x80 */ s32 movie[5];
	/* 0x94 */ s32 i94;
}; // 0x98

// ---- ADV_CG_LST (vtable 63A0, size 0xac) ----------------------------------
struct ADV_CG_LST {
	/* 0x00 */ void* templ;
	/* 0x04 */ u8 _04[0x0C - 0x04];
	/* 0x0C */ ADV_CG_LST* next;
	/* 0x10 */ u8 _10[0x18 - 0x10];
	/* 0x18 */ void* vtable;
	/* 0x1C */ u8 _1c[0x1E - 0x1C];
	/* 0x1E */ u16 objsize;
	/* 0x20 */ u8 _20[0x28 - 0x20];
	/* 0x28 */ void* spr;
	/* 0x2C */ f32 f2c;
	/* 0x30 */ f32 f30;
	/* 0x34 */ f32 x;
	/* 0x38 */ f32 y;
	/* 0x3C */ s32 i3c;
	/* 0x40 */ s32 i40;
	/* 0x44 */ f32 f44;
	/* 0x48 */ f32 vx;
	/* 0x4C */ f32 vy;
	/* 0x50 */ f32 ax;
	/* 0x54 */ f32 ay;
	/* 0x58 */ u8 _58[0x98 - 0x58];
	/* 0x98 */ s32 i98;
	/* 0x9C */ s32 i9c;
	/* 0xA0 */ s32 ia0;
	/* 0xA4 */ s32 ia4;
	/* 0xA8 */ s32 ia8;
}; // 0xac

// ---- ADV_CG (vtable 63CC, size 0x13c) -------------------------------------
struct ADV_CG {
	/* 0x000 */ void* templ;
	/* 0x004 */ u8 _04[0x18 - 0x04];
	/* 0x018 */ void* vtable;
	/* 0x01C */ u8 _1c[0x1E - 0x1C];
	/* 0x01E */ u16 objsize;
	/* 0x020 */ u8 _20[0x28 - 0x20];
	/* 0x028 */ s32 mode;
	/* 0x02C */ s32 state;
	/* 0x030 */ u8 _30[0x34 - 0x30];
	/* 0x034 */ f32 timer;
	/* 0x038 */ void* data;
	/* 0x03C */ u8 _3c[0x40 - 0x3C];
	/* 0x040 */ s32 x40;
	/* 0x044 */ s32 x44;
	/* 0x048 */ u8 _48[0x78 - 0x48];
	/* 0x078 */ s32 x78;
	/* 0x07C */ u8 _7c[0x80 - 0x7C];
	/* 0x080 */ s32 sel;
	/* 0x084 */ u8 selector[0x110 - 0x84];
	/* 0x110 */ void* list;
	/* 0x114 */ void* movieObj;
	/* 0x118 */ f32 f118;
	/* 0x11C */ s32 i11c;
	/* 0x120 */ s32 i120;
	/* 0x124 */ s32 avail[6];
}; // 0x13c

// table of {tag, value} pairs (8 bytes) pointed to by data records
struct FPair {
	s32 a;
	f32 b;
};

// raw word view of sADV_CG_LIST for the ctor copy
struct CGListRaw {
	s32 w[7];
};

// memberwise (Vec2-grouped) view for the through-pointer copy in E1F4
struct Vec2w {
	s32 x, y;
};
struct CGListMbr {
	void* spr;
	Vec2w v0;
	Vec2w v1;
	s32 i14;
	s32 i18;
};

// 0x68-stride CG data record (field 0xd8 holds the FPair table pointer)
struct CGDataRec {
	u8 pad[0x68];
};

// small CG animator sub-object (EC2C..ECD0)
struct CGAnim {
	/* 0x00 */ u8 _00[0x2c];
	/* 0x2C */ f32 f2c;
	/* 0x30 */ f32 f30;
	/* 0x34 */ u8 _34[0x38 - 0x34];
	/* 0x38 */ s32 i38;
	/* 0x3C */ s32 i3c;
	/* 0x40 */ s32 i40;
	/* 0x44 */ s32 i44;
};

extern "C" {

// --- forward declarations (this TU) --------------------------------------
void fn_1_DAB0(ADV_MOVIE* self);
void fn_1_DB70(void);
ADV_MOVIE* fn_1_DB74(ADV_MOVIE* self, int flag);
ADV_MOVIE* fn_1_DCD0(void* parent);
void fn_1_DD10(void);
void fn_1_DD58(void);
void fn_1_DD8C(ADV_CG_LST* self, s32 idx);
void fn_1_DE08(ADV_CG_LST* self, s32 idx);
void fn_1_DEC0(ADV_CG_LST* self);
void fn_1_DEEC(ADV_CG_LST* self);
ADV_MOVIE* fn_1_DBDC(ADV_MOVIE* self, void* parent);
void fn_1_E064(void* dst, const void* src);
ADV_CG_LST* fn_1_E078(ADV_CG_LST* self, int flag);
ADV_CG_LST* fn_1_E0E0(ADV_CG_LST* self, void* parent, const sADV_CG_LIST* param);
void fn_1_E1F4(void* dst, const sADV_CG_LIST* src);
void fn_1_E230(ADV_CG* self);
void fn_1_E328(ADV_CG* self, s32 v);
void fn_1_E36C(ADV_CG* self, s32 idx);
void fn_1_E3EC(ADV_CG* self, s32 idx);
void fn_1_E46C(ADV_CG* self, s32 idx);
void fn_1_E4F8(ADV_CG* self);
void fn_1_E6C0(ADV_CG* self);
void fn_1_E7C4(ADV_CG* self);
void fn_1_E820(ADV_CG* self, s32 mode);
void fn_1_E890(ADV_CG* self);
ADV_CG* fn_1_E9D0(ADV_CG* self, int flag);
ADV_CG* fn_1_EA48(ADV_CG* self, void* parent);
ADV_CG* fn_1_EB80(void* parent);
void fn_1_EBC0(void);
void fn_1_EBE8(void);
void fn_1_EC18(void* p);
void fn_1_EC2C(CGAnim* self);
void fn_1_EC70(void);
void fn_1_EC74(CGAnim* self);
void fn_1_ECAC(CGAnim* self);
void fn_1_ECC0(CGAnim* self, s32 v);
void fn_1_ECD0(CGAnim* self, s32 mode);

// --- externs -------------------------------------------------------------
void* advE3Rom_resume(int size);
void advE3Rom_pause(void* p);
void fn_1_DA84(ADV_MOVIE* self);
void fn_1_8740(void);
void fn_1_86C8(void);
int fn_1_86B0(ADV_CG_LST* node, s32 tag);
int fn_1_12A0(void* p, int a);
void fn_1_7B24(void* dst, const void* src);
int fn_1_11FFC(void* p, int dir);
void fn_1_120E0(void* p, int a);
void fn_1_120C4(void* p, int idx);
void fn_1_12124(void* p);
void fn_1_10F40(void* obj, ADV_CG* self);
void fn_1_11750(int a);

void fn_800A8620(void* self, int flag);
void fn_800A8828(void* self, void* parent);
void* dtor_800186D0(void* self, int flag);
void* fn_80018818(void* self, void* parent);
void fn_800421C8(void* a, void* b);
void fn_80042310(void* a, void* b);
f32 fn_801992A4(void* v);
void fn_8019930C(void* dst, void* src);
void fn_8012CC0C(void* spr, void* pos);
void fn_8012CEF0(void* spr, f32 frame);
void fn_8012CC20(void* spr);
int fn_80138994(void* cat, int idx, int c);
int fn_800A9398(void* p, int a);
void fn_800A8174(void* self, int a);
void fn_800A8264(void* self);
void fn_800A80DC(void* self, int a);
void fn_8012CA94(void* p);
void fn_8012CB70(void* p);
void fn_800B52E8(void* a, int b, int c, int d);
int fn_8011253C(void);
void* memset(void* dst, int val, unsigned long n);

// module-local data (defined in unclaimed splits)
extern void* lbl_1_data_6364[];
extern void* lbl_1_data_63A0[];
extern void* lbl_1_data_63CC[];
extern u32 lbl_1_data_6360;
extern u32 lbl_1_data_6350;
extern u32 lbl_1_data_6340;
extern u8 lbl_1_data_6398[];
extern CGDataRec lbl_1_data_5D40[];
extern u8 lbl_1_data_60B8[];
extern u8 lbl_1_data_60A0[];
extern u8 lbl_1_data_75FC[];

extern s32 lbl_1_bss_720;
extern f32 lbl_1_bss_724;
extern u8 lbl_1_bss_728;

extern u8 lbl_803EC340[];
extern void* lbl_8028CEF0[];
extern void* lbl_8042C180;
extern u8 lbl_8042C1C0[];
extern void* lbl_8042C388;
extern u8 lbl_8042C7E0[];
extern u8 lbl_80303EC8[];

extern const s32 lbl_1_rodata_1410[14];
extern const s32 lbl_1_rodata_1448[6];
extern const s32 lbl_1_rodata_1460[6][5];
extern const f32 lbl_1_rodata_14D8; // 5.0
extern const f32 lbl_1_rodata_14DC; // 1.0
extern const f32 lbl_1_rodata_14E0; // 0.0
extern const f32 lbl_1_rodata_14E4; // 0.001
extern const s32 lbl_1_rodata_1950[10];
extern const s32 lbl_1_rodata_1978[10];
extern const f32 lbl_1_rodata_19A0; // 1.0

// clang-format off

#pragma force_active on

void fn_1_DAB0(ADV_MOVIE* self)
{
	int i;

	switch (self->i28) {
	case 5:
		i = 0;
		do {
			int r;
			if (self->movie[0] == -1) {
				break;
			}
			((s32*)lbl_803EC340)[1] = self->movie[0];
			((void (*)(void))lbl_8028CEF0[0])();
			do {
				r = (int)((int (*)(void))lbl_8028CEF0[2])();
				fn_8011253C();
			} while (r == 0);
			((void (*)(void))lbl_8028CEF0[1])();
			fn_1_DA84(self);
			if ((u32)(r - 2) <= 1) {
				break;
			}
			i++;
		} while (i != 5);
		self->i2c = 2;
		break;
	}
}

void fn_1_DB70(void)
{
}

ADV_MOVIE* fn_1_DB74(ADV_MOVIE* self, int flag)
{
	if (self) {
		self->vtable = lbl_1_data_6364;
		fn_800A8620(self, 0);
		if ((s16)flag > 0) {
			advE3Rom_pause(self);
		}
	}
	return self;
}

ADV_MOVIE* fn_1_DBDC(ADV_MOVIE* self, void* parent)
{
	s32 i;

	fn_800A8828(self, parent);
	self->vtable = lbl_1_data_6364;
	self->templ = (void*)lbl_1_data_6360;
	self->objsize = 0x98;
	self->i40 = 0xa;
	self->i44 = 0xa;
	self->i48 = 1;
	self->i28 = 0;
	self->i2c = 5;
	self->i94 = 0;
	for (i = 0; i != 5; i++) {
		self->movie[i] = lbl_1_rodata_1460[lbl_1_bss_720][i];
		if (self->movie[i] == 0x19) {
			if (fn_1_12A0(lbl_8042C180, 0x14) == 0) {
				self->movie[i] = 0x1a;
			}
		}
	}
	return self;
}

#pragma peephole on
#pragma optimization_level 1
ADV_MOVIE* fn_1_DCD0(void* parent)
{
	ADV_MOVIE* obj = (ADV_MOVIE*)advE3Rom_resume(0x98);
	if (obj) {
		return fn_1_DBDC(obj, parent);
	}
	return obj;
}
#pragma optimization_level reset
#pragma peephole reset

void fn_1_DD10(void)
{
	fn_800421C8(lbl_8042C1C0, &lbl_1_data_6398);
	memset(lbl_8028CEF0, 0, 0x14);
	fn_1_8740();
}

void fn_1_DD58(void)
{
	fn_1_86C8();
	fn_80042310(lbl_8042C1C0, &lbl_1_data_6398);
}

#pragma opt_common_subs off
#pragma opt_propagation off
void fn_1_DD8C(ADV_CG_LST* self, s32 idx)
{
	FPair* tbl;
	CGDataRec* rec;
	CGDataRec* records;

	if (self->i3c != idx) {
		return;
	}
	self->ia0 = self->i40 ? 8 : 3;
	self->ia4 = self->i40 ? 9 : 4;
	records = lbl_1_data_5D40;
	rec = &records[self->i3c];
	tbl = (FPair*)*(void**)((u8*)rec + 0xd8);
	self->f44 = tbl[self->ia0].b;
	self->ia8 = 1;
}
#pragma opt_propagation reset
#pragma opt_common_subs reset

#pragma opt_common_subs off
#pragma opt_propagation off
void fn_1_DE08(ADV_CG_LST* self, s32 idx)
{
	FPair* tbl;
	CGDataRec* rec;
	CGDataRec* records;

	if (self->i3c == idx) {
		self->i98 = self->i40 ? 6 : 1;
		self->i9c = self->i40 ? 7 : 2;
	} else {
		self->i98 = self->i40 ? 5 : 0;
		self->i9c = self->i40 ? 5 : 0;
	}
	records = lbl_1_data_5D40;
	rec = &records[self->i3c];
	tbl = (FPair*)*(void**)((u8*)rec + 0xd8);
	self->f44 = tbl[self->i98].b;
	self->ia8 = 0;
}
#pragma opt_propagation reset
#pragma opt_common_subs reset

void fn_1_DEC0(ADV_CG_LST* self)
{
	if (self->spr) {
		fn_8012CC20(self->spr);
	}
}

#pragma opt_common_subs off
#pragma opt_propagation off
void fn_1_DEEC(ADV_CG_LST* self)
{
	f32 wk[2];
	f32* base;
	CGDataRec* rec;
	CGDataRec* records;

	wk[0] = self->x - self->ax;
	wk[1] = self->y - self->ay;
	if (fn_801992A4(wk) <= lbl_1_rodata_14D8) {
		fn_1_E064(&self->ax, &self->x);
	} else {
		self->ax = self->ax + self->vx;
		self->ay = self->ay + self->vy;
	}
	self->f44 = self->f44 + lbl_1_rodata_14DC;
	if (self->ia8 == 0) {
		records = lbl_1_data_5D40;
		rec = &records[self->i3c];
		base = (f32*)((u8*)*(void**)((u8*)rec + 0xd8) + 4);
		if (base[self->i9c * 2] <= self->f44) {
			self->f44 = base[self->i98 * 2];
		}
	} else {
		records = lbl_1_data_5D40;
		rec = &records[self->i3c];
		base = (f32*)((u8*)*(void**)((u8*)rec + 0xd8) + 4);
		if (base[self->ia4 * 2] <= self->f44) {
			self->f44 = base[self->i98 * 2];
			self->ia8 = 0;
		}
	}
	if (self->spr) {
		fn_8012CC0C(self->spr, &self->ax);
		fn_8012CEF0(self->spr, self->f44);
	}
}
#pragma opt_propagation reset
#pragma opt_common_subs reset

void fn_1_E064(void* dst, const void* src)
{
	((f32*)dst)[0] = ((const f32*)src)[0];
	((f32*)dst)[1] = ((const f32*)src)[1];
}

ADV_CG_LST* fn_1_E078(ADV_CG_LST* self, int flag)
{
	if (self) {
		self->vtable = lbl_1_data_63A0;
		dtor_800186D0(self, 0);
		if ((s16)flag > 0) {
			advE3Rom_pause(self);
		}
	}
	return self;
}

ADV_CG_LST* fn_1_E0E0(ADV_CG_LST* self, void* parent, const sADV_CG_LIST* param)
{
	f32 len;

	fn_80018818(self, parent);
	self->vtable = lbl_1_data_63A0;
	self->templ = (void*)lbl_1_data_6350;
	self->objsize = 0xac;
	fn_1_E1F4(&self->spr, param);
	self->f44 = lbl_1_rodata_14E0;
	fn_1_E064(&self->ax, &param->x0);
	self->ia8 = 0;
	self->vx = param->x1 - param->x0;
	self->vy = param->y1 - param->y0;
	len = fn_801992A4(&self->vx);
	if (len < lbl_1_rodata_14E4) {
		self->vx = self->vy = lbl_1_rodata_14E0;
	} else {
		fn_8019930C(&self->vx, &self->vx);
	}
	self->vx = lbl_1_rodata_14D8 * self->vx;
	self->vy = lbl_1_rodata_14D8 * self->vy;
	return self;
}

void fn_1_E1F4(void* dst, const sADV_CG_LIST* src)
{
	*(CGListMbr*)dst = *(const CGListMbr*)src;
}

void fn_1_E230(ADV_CG* self)
{
	self->avail[0] = 1;
	self->avail[1] = fn_80138994(lbl_8042C7E0, 0, 0) == 0x64;
	self->avail[2] = fn_80138994(lbl_8042C7E0, 1, 0) == 0x64;
	self->avail[3] = fn_80138994(lbl_8042C7E0, 2, 0) == 0x64;
	self->avail[4] = fn_80138994(lbl_8042C7E0, 3, 0) == 0x64;
	self->avail[5] = fn_80138994(lbl_8042C7E0, 4, 0) == 0x64;
}

void fn_1_E328(ADV_CG* self, s32 v)
{
	self->x78 = 0x78;
	self->state = 3;
	self->x40 = 0xd;
	self->x44 = 0xd;
	if (v < 0) {
		v = 0;
	}
	if (v >= 6) {
		v = 5;
	}
	lbl_1_bss_720 = v;
}

void fn_1_E36C(ADV_CG* self, s32 idx)
{
	ADV_CG_LST* node;

	if (self->list) {
		node = *(ADV_CG_LST**)((u8*)self->list + 0x14);
		while (node) {
			if (fn_1_86B0(node, lbl_1_data_6350)) {
				fn_1_DD8C(node, idx);
			}
			node = node->next;
		}
	}
}

void fn_1_E3EC(ADV_CG* self, s32 idx)
{
	ADV_CG_LST* node;

	if (self->list) {
		node = *(ADV_CG_LST**)((u8*)self->list + 0x14);
		while (node) {
			if (fn_1_86B0(node, lbl_1_data_6350)) {
				fn_1_DE08(node, idx);
			}
			node = node->next;
		}
	}
}

void fn_1_E46C(ADV_CG* self, s32 idx)
{
	FPair* p;

	if (self->avail[idx] == 0) {
		fn_1_7B24(&self->i11c, &lbl_1_rodata_1410[0]);
	} else {
		fn_1_7B24(&self->i11c, &lbl_1_rodata_1410[(idx + 1) * 2]);
	}
	p = (FPair*)(*(void**)((u8*)lbl_1_data_5D40 + 0x70));
	self->f118 = p[self->i11c].b;
}

void fn_1_E4F8(ADV_CG* self)
{
	s32 sel;

	sel = fn_1_11FFC(&self->selector, -1);
	if (sel != -1 && self->sel != sel) {
		if (lbl_8042C388) {
			fn_800B52E8(lbl_8042C388, 0xE007, 0, 0);
		}
		self->sel = sel;
		fn_1_E3EC(self, sel);
		fn_1_E46C(self, self->sel);
	} else {
		switch (fn_800A9398(lbl_80303EC8, -1)) {
		case 0:
			break;
		case 3:
			if (self->avail[self->sel] != 0) {
				fn_800A8174(self, lbl_1_rodata_1448[self->sel]);
			} else {
				fn_800A8174(self, 0x185);
			}
			break;
		case 1:
			if (lbl_8042C388) {
				fn_800B52E8(lbl_8042C388, 0xE009, 0, 0);
			}
			self->state = 2;
			break;
		case 2:
			if (self->avail[self->sel] != 0) {
				if (lbl_8042C388) {
					fn_800B52E8(lbl_8042C388, 0xE008, 0, 0);
				}
				fn_1_E36C(self, self->sel);
				fn_1_E328(self, self->sel);
			} else {
				if (lbl_8042C388) {
					fn_800B52E8(lbl_8042C388, 0xE018, 0, 0);
				}
			}
			break;
		}
	}
}

void fn_1_E6C0(ADV_CG* self)
{
	CGListRaw wk;
	ADV_CG* p;
	u8* src;
	u32 i;
	ADV_CG_LST* n;

	if (((f32*)(*(void**)((u8*)lbl_1_data_5D40 + 0x8)))[1] <= self->timer) {
		src = lbl_1_data_60B8;
		i = 0;
		p = self;
		do {
			wk = *(CGListRaw*)src;
			wk.w[6] = p->avail[0];
			n = (ADV_CG_LST*)advE3Rom_resume(0xac);
			if (n) {
				fn_1_E0E0(n, self->list, (sADV_CG_LIST*)&wk);
			}
			p = (ADV_CG*)((u8*)p + 4);
			i++;
			src += 0x1c;
		} while (i != 6);
		fn_1_E3EC(self, self->sel);
		fn_1_E46C(self, self->sel);
		self->state = 6;
	}
}

void fn_1_E7C4(ADV_CG* self)
{
	fn_800A8264(self);
	if (self->movieObj) {
		if (((f32*)(*(void**)((u8*)lbl_1_data_5D40 + 0x8)))[5] <= self->timer) {
			fn_8012CC20(self->movieObj);
		}
	}
}

void fn_1_E820(ADV_CG* self, s32 mode)
{
	if (self->list) {
		fn_1_EC18(self->list);
	}
	switch (mode) {
	case 5:
		break;
	case 6:
		fn_1_E3EC(self, self->sel);
		fn_1_E46C(self, self->sel);
		break;
	}
}

void fn_1_E890(ADV_CG* self)
{
	f32* q;

	switch (self->mode) {
	case 5:
		fn_1_E6C0(self);
		break;
	case 6:
		fn_1_E4F8(self);
		break;
	}
	self->timer += lbl_1_rodata_14DC;
	if ((s8)lbl_1_bss_728 == 0) {
		lbl_1_bss_724 = lbl_1_rodata_14E0;
		lbl_1_bss_728 = 1;
	}
	if (*(f32*)((u8*)(*(void**)((u8*)lbl_1_data_5D40 + 0x8)) + 0x1c) < self->timer - lbl_1_bss_724) {
		self->timer = *(f32*)((u8*)(*(void**)((u8*)lbl_1_data_5D40 + 0x8)) + 0x14);
	}
	if (self->movieObj) {
		self->f118 += lbl_1_rodata_14DC;
		q = (f32*)((u8*)(*(void**)((u8*)lbl_1_data_5D40 + 0x70)) + 4);
		if (q[self->i120 * 2] <= self->f118) {
			self->f118 = q[self->i11c * 2];
		}
		fn_8012CEF0(self->movieObj, self->f118);
	}
}

ADV_CG* fn_1_E9D0(ADV_CG* self, int flag)
{
	if (self) {
		self->vtable = lbl_1_data_63CC;
		fn_1_120E0(&self->selector, -1);
		fn_800A8620(self, 0);
		if ((s16)flag > 0) {
			advE3Rom_pause(self);
		}
	}
	return self;
}

ADV_CG* fn_1_EA48(ADV_CG* self, void* parent)
{
	void* obj;

	fn_800A8828(self, parent);
	self->vtable = lbl_1_data_63CC;
	fn_1_12124(&self->selector);
	self->templ = (void*)lbl_1_data_6340;
	self->objsize = 0x13c;
	self->x40 = 4;
	self->x44 = 4;
	self->mode = 0;
	self->state = 5;
	self->data = (u8*)lbl_1_data_5D40;
	self->movieObj = (u8*)lbl_1_data_5D40 + 0x68;
	fn_1_E46C(self, 0);
	self->sel = 0;
	fn_1_120C4(&self->selector, 0);
	fn_1_120C4(&self->selector, 1);
	fn_1_120C4(&self->selector, 2);
	fn_1_120C4(&self->selector, 3);
	fn_1_120C4(&self->selector, 4);
	fn_1_120C4(&self->selector, 5);
	obj = advE3Rom_resume(0x28);
	if (obj) {
		obj = fn_80018818(obj, self);
	}
	self->list = obj;
	fn_1_E230(self);
	fn_800A80DC(self, 4);
	obj = advE3Rom_resume(0x30);
	if (obj) {
		fn_1_10F40(obj, self);
	}
	return self;
}

#pragma peephole on
#pragma optimization_level 1
ADV_CG* fn_1_EB80(void* parent)
{
	ADV_CG* obj = (ADV_CG*)advE3Rom_resume(0x13c);
	if (obj) {
		return fn_1_EA48(obj, parent);
	}
	return obj;
}
#pragma optimization_level reset
#pragma peephole reset

void fn_1_EBC0(void)
{
	fn_8012CA94(&lbl_1_data_60A0);
}

void fn_1_EBE8(void)
{
	fn_1_11750(4);
	fn_8012CB70(&lbl_1_data_60A0);
}

void fn_1_EC18(void* p)
{
	*(u16*)((u8*)p + 4) &= ~0x10;
}

void fn_1_EC2C(CGAnim* self)
{
	self->f2c += lbl_1_rodata_19A0;
	if (self->f30 <= self->f2c) {
		if (self->i3c != 4) {
			self->i3c = 1;
		}
	}
}

void fn_1_EC70(void)
{
}

void fn_1_EC74(CGAnim* self)
{
	self->f2c += lbl_1_rodata_19A0;
	if (self->f30 <= self->f2c) {
		self->i3c = 2;
	}
}

void fn_1_ECAC(CGAnim* self)
{
	self->i44 = 0;
	self->i3c = 3;
}

void fn_1_ECC0(CGAnim* self, s32 v)
{
	self->i44 = v;
	self->i3c = 3;
}

void fn_1_ECD0(CGAnim* self, s32 mode)
{
	self->i38 = mode;
	self->i3c = mode;
	switch (self->i38) {
	case 1: {
		self->i40 = self->i44;
		FPair*& t = *(FPair**)(lbl_1_data_75FC + 0xd8);
		self->f2c = t[lbl_1_rodata_1950[self->i40 * 2]].b;
		self->f30 = t[lbl_1_rodata_1950[self->i40 * 2 + 1]].b;
		break;
	}
	case 3: {
		FPair*& t = *(FPair**)(lbl_1_data_75FC + 0xd8);
		self->f2c = t[lbl_1_rodata_1978[self->i40 * 2]].b;
		self->f30 = t[lbl_1_rodata_1978[self->i40 * 2 + 1]].b;
		break;
	}
	}
}

#pragma force_active reset

// clang-format on
}
