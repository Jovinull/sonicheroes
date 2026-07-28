#include "types.h"

// ADV_WINDOW - the advertise-module window (message/selection box) class.
//
// Module-relative .text 0x14728-0x152C0 (10 functions). Class ADV_WINDOW
// (name string at .data 0x853C, vtable at .data 0x854C). Reference-guided from
// the PS2 debug build's ADV_WINDOW class (semantic, not byte-identical).
//
// REL symbols are unmangled, so every function is written extern "C".

struct Vec3f {
	f32 x, y, z;
};

struct V3i {
	u32 a, b, c;
};
struct V2i {
	u32 a, b;
};

struct RwV2d {
	f32 x, y;
};

// The 0x44-byte parameter/state block embedded at ADV_WINDOW+0x28.
struct sADV_WINDOW_PARAM {
	/* 0x00 */ void* p00;
	/* 0x04 */ void* p04;
	/* 0x08 */ void* p08;
	/* 0x0C */ void* p0c;
	/* 0x10 */ s32 i10;
	/* 0x14 */ RwV2d v14;
	/* 0x1C */ s32 i1c;
	/* 0x20 */ RwV2d v20;
	/* 0x28 */ RwV2d v28;
	/* 0x30 */ RwV2d v30;
	/* 0x38 */ s32 i38;
	/* 0x3C */ s32 i3c;
	/* 0x40 */ s32 i40;
}; // 0x44

struct ADV_WINDOW {
	/* 0x000 */ void* name;
	/* 0x004 */ u8 pad_0x04[0x18 - 0x04];
	/* 0x018 */ void* vtable;
	/* 0x01C */ u8 pad_0x1C[0x1E - 0x1C];
	/* 0x01E */ u16 unk_0x1e;
	/* 0x020 */ u8 pad_0x20[0x28 - 0x20];
	/* 0x028 */ sADV_WINDOW_PARAM param;
	/* 0x06C */ s32 unk_0x6c;
	/* 0x070 */ s32 unk_0x70;
	/* 0x074 */ u8 selector[0x100 - 0x74];
	/* 0x100 */ s32 mode;
	/* 0x104 */ f32 w0;
	/* 0x108 */ f32 w1;
	/* 0x10C */ f32 w2;
	/* 0x110 */ u8 sprite0[0x510 - 0x110];
	/* 0x510 */ u8 sprite1[0x610 - 0x510];
	/* 0x610 */ u8 sprite2[0x710 - 0x610];
	/* 0x710 */ u8 sprite3[0x838 - 0x710];
	void Disp();
}; // size 0x838

extern "C" {

// --- externs to other modules / the DOL / earlier TUs ----------------------
void fn_1_1397C(ADV_WINDOW* self, void* a, void* b);
void fn_1_145B4(ADV_WINDOW* self, void* a, void* b);
void fn_1_14624(ADV_WINDOW* self, Vec3f* pos, RwV2d* size, s32 flag);
void fn_8012F858(void* list, void* addr, f32 a, f32 b, s32 mode);
int fn_1_13744(void* p);
int fn_1_11FFC(void* p, int dir);
void fn_800B52E8(void* a, int b, int c, int d);
void fn_80014154(void);
void fn_1_120E0(void* p, int a);
ADV_WINDOW* dtor_800186D0(ADV_WINDOW* self, int flag);
void advE3Rom_pause(void* obj);
ADV_WINDOW* fn_80018818(ADV_WINDOW* self, void* parent);
void fn_1_152C0(sADV_WINDOW_PARAM* p);
void fn_1_12124(void* p);
void fn_1_15020(sADV_WINDOW_PARAM* dst, const sADV_WINDOW_PARAM* src);
void fn_8012EBD4(void* sprite, void* res);
void fn_1_120C4(void* p, int idx);
int fn_8012EF3C(void* list, void* res);
void* fn_8012ECA8(int a, int b);
void fn_1_119BC(void* p, int n);
void* advE3Rom_resume(s32 id);
ADV_WINDOW* fn_1_14DA4(ADV_WINDOW* self, void* parent, const sADV_WINDOW_PARAM* param);
void fn_801A46D0(void*);
void* fn_80057644(int size);
void* fn_800BCC84(void* h, void* name, int a);
void* fn_80012994(int size);
void* fn_800BC580(void* h, int a, void* buf);
void* fn_801A4BBC(void* h, void* name);
void fn_800126C8(void* p);
void fn_800BCBD4(void* h, int a);
void fn_8012FF6C(void* list);
void fn_801301C8(void* list);
void fn_1_1517C(void);
void fn_1_15108(void);

extern u8 lbl_803E8150[];
extern void* lbl_1_data_854C[]; // ADV_WINDOW vtable
extern void* lbl_1_data_8548;   // -> "ADV_WINDOW"
extern u8 lbl_1_data_8578[];    // "./advertise/adv_window.one"
extern void* lbl_1_data_8528[]; // 5-entry resource-name table
extern void* lbl_8042C388;      // global sound-enable flag

extern void* lbl_1_bss_830;    // resource file handle
extern void* lbl_1_bss_834[5]; // loaded resource pointers

extern const f32 lbl_1_rodata_1A50[3]; // {16, 16, 0}
extern const V3i lbl_1_rodata_1A5C;    // zeros
extern const V2i lbl_1_rodata_1A68;    // {0, 32.0f}
extern const V2i lbl_1_rodata_1A70;    // zeros
extern const V2i lbl_1_rodata_1A78;    // zeros
extern const f32 lbl_1_rodata_1CDC;    // 0.5
extern const f32 lbl_1_rodata_1CE8;    // 2.0
extern const f32 lbl_1_rodata_1CEC;    // 16.0
extern const f32 lbl_1_rodata_1CF0;    // 3.0
extern const f32 lbl_1_rodata_1CF4;    // 8.0
extern const f32 lbl_1_rodata_1CF8;    // 0.0
extern const u32 lbl_1_rodata_1D00[2] = { 0x43300000, 0 };
extern u8 lbl_8029BB80[];

#pragma optimization_level 1
static inline void ClearWindowResources(void** p)
{
	void* zero = 0;
	*p         = zero;
	*++p       = zero;
	*++p       = zero;
	*++p       = zero;
	*++p       = zero;
}
#pragma optimization_level reset

// clang-format off

// ADV_WINDOW::Disp() - vtable[4]
#pragma fp_contract off
#pragma opt_common_subs off
void ADV_WINDOW::Disp()
{
	ADV_WINDOW* self = this;
	u8 body[4];

	body[0] = 0;
	body[1] = 0;
	body[2] = 0;
	body[3] = 0;
	fn_1_1397C(self, &self->param.v28, body);

	if (self->param.p00) {
		fn_1_145B4(self, &self->param.v14.x, &self->param.v20.x);
		fn_8012F858(lbl_803E8150, &self->sprite0,
			self->param.v14.x + lbl_1_rodata_1A50[0],
			self->param.v14.y + lbl_1_rodata_1A50[1], 1);
	}

	V3i quad60 = lbl_1_rodata_1A5C;
	Vec3f pos54;
	((Vec3f*)&quad60)->x = self->param.v14.x;
	((Vec3f*)&quad60)->y = self->param.v14.y + self->param.v20.y;
	((Vec3f*)&quad60)->z = *(f32*)&self->param.i1c;

	V2i wk34 = lbl_1_rodata_1A68;
	((RwV2d*)&wk34)->x = self->param.v20.x;

	void* p04 = self->param.p04;
	if (p04 && self->param.p08 && self->param.p0c) {
		V2i quad2c = lbl_1_rodata_1A70;
		((RwV2d*)&quad2c)->x = ((RwV2d*)&wk34)->x;
		((RwV2d*)&quad2c)->y = lbl_1_rodata_1CEC + lbl_1_rodata_1CF0 * ((RwV2d*)&wk34)->y;
		fn_1_145B4(self, (Vec3f*)&quad60, (RwV2d*)&quad2c);
	} else if (p04 && self->param.p08) {
		V2i tmp24 = lbl_1_rodata_1A78;
		((RwV2d*)&tmp24)->x = ((RwV2d*)&wk34)->x;
		((RwV2d*)&tmp24)->y = lbl_1_rodata_1CEC + lbl_1_rodata_1CE8 * ((RwV2d*)&wk34)->y;
		fn_1_145B4(self, (Vec3f*)&quad60, (RwV2d*)&tmp24);
	}

	RwV2d sz1c;
	if (self->param.p04) {
		pos54.x = lbl_1_rodata_1CF4 + ((Vec3f*)&quad60)->x;
		pos54.y = lbl_1_rodata_1CF4 + ((Vec3f*)&quad60)->y;
		pos54.z = lbl_1_rodata_1CDC;
		sz1c.x = ((RwV2d*)&wk34)->x - lbl_1_rodata_1CEC;
		sz1c.y = ((RwV2d*)&wk34)->y;
		fn_1_14624(self, &pos54, &sz1c, self->mode == 1);
		fn_8012F858(lbl_803E8150, &self->sprite1,
			pos54.x + lbl_1_rodata_1CDC * sz1c.x - lbl_1_rodata_1CDC * self->w0,
			((Vec3f*)&quad60)->y + lbl_1_rodata_1A50[1], 1);
	}

	if (self->param.p08) {
		Vec3f p14;
		RwV2d s0c;
		s0c.x = ((RwV2d*)&wk34)->x - lbl_1_rodata_1CEC;
		s0c.y = ((RwV2d*)&wk34)->y;
		p14.x = lbl_1_rodata_1CF4 + ((Vec3f*)&quad60)->x;
		p14.y = lbl_1_rodata_1CF4 + ((Vec3f*)&quad60)->y + ((RwV2d*)&wk34)->y;
		p14.z = lbl_1_rodata_1CDC;
		fn_1_14624(self, &p14, &s0c, self->mode == 2);
		fn_8012F858(lbl_803E8150, &self->sprite2,
			p14.x + lbl_1_rodata_1CDC * s0c.x - lbl_1_rodata_1CDC * self->w1,
			p14.y + lbl_1_rodata_1A50[1] - lbl_1_rodata_1CF4, 1);
	}

	if (self->param.p0c) {
		Vec3f p3c;
		RwV2d s0c;
		s0c.x = ((RwV2d*)&wk34)->x - lbl_1_rodata_1CEC;
		s0c.y = ((RwV2d*)&wk34)->y;
		p3c.x = lbl_1_rodata_1CF4 + ((Vec3f*)&quad60)->x;
		p3c.y = lbl_1_rodata_1CF4 + ((Vec3f*)&quad60)->y + ((RwV2d*)&wk34)->y + ((RwV2d*)&wk34)->y;
		p3c.z = lbl_1_rodata_1CDC;
		fn_1_14624(self, &p3c, &s0c, self->mode == 3);
		fn_8012F858(lbl_803E8150, &self->sprite3,
			p3c.x + lbl_1_rodata_1CDC * s0c.x - lbl_1_rodata_1CDC * self->w2,
			p3c.y + lbl_1_rodata_1A50[1] - lbl_1_rodata_1CF4, 1);
	}
}
#pragma opt_common_subs reset
#pragma fp_contract reset

// ADV_WINDOW::Exec() - vtable[3]
void fn_1_14BB0(ADV_WINDOW* self)
{
	int trg;
	int sel;

	if (self->unk_0x70 == 0) {
		switch (self->param.i10) {
		case 0:
		case 2:
			trg = fn_1_13744((void*)self->param.i3c);
			switch (trg) {
			case 0:
				switch (self->param.i3c) {
				case 1:
					sel = fn_1_11FFC(&self->selector, 0);
					break;
				case 2:
					sel = fn_1_11FFC(&self->selector, 1);
					break;
				case 0:
				default:
					sel = fn_1_11FFC(&self->selector, -1);
					break;
				}
				if (sel != -1 && sel != self->mode) {
					self->mode = sel;
					if (lbl_8042C388) {
						fn_800B52E8(lbl_8042C388, 0xE007, 0, 0);
					}
				}
				break;
			case 2:
				self->unk_0x6c = self->mode;
				if (self->param.i40 != 0 && lbl_8042C388) {
					fn_800B52E8(lbl_8042C388, 0xE008, 0, 0);
				}
				if (self->param.i38 != 0) {
					fn_80014154();
				}
				break;
			}
			break;
		case 1:
			self->unk_0x6c = 1;
			break;
		}
	} else {
		self->unk_0x70 = self->unk_0x70 - 1;
	}
}

// ADV_WINDOW::~ADV_WINDOW() - vtable[2]
ADV_WINDOW* fn_1_14D2C(ADV_WINDOW* self, int flag)
{
	if (self) {
		self->vtable = lbl_1_data_854C;
		fn_1_120E0(&self->selector, -1);
		dtor_800186D0(self, 0);
		if ((s16)flag > 0) {
			advE3Rom_pause(self);
		}
	}
	return self;
}

// ADV_WINDOW::ADV_WINDOW(TObject*, const sADV_WINDOW_PARAM&)
ADV_WINDOW* fn_1_14DA4(ADV_WINDOW* self, void* parent, const sADV_WINDOW_PARAM* param)
{
	fn_80018818(self, parent);
	self->vtable = lbl_1_data_854C;
	fn_1_152C0(&self->param);
	fn_1_12124(&self->selector);
	self->name = lbl_1_data_8548;
	self->unk_0x1e = 0x838;
	fn_1_15020(&self->param, param);
	self->unk_0x6c = 0;
	self->mode = 1;

	fn_8012EBD4(&self->sprite0, param->p00);

	fn_8012EBD4(&self->sprite1, param->p04);
	if (param->p04) {
		fn_1_120C4(&self->selector, 1);
		self->w0 = (f32)(u32)fn_8012EF3C(lbl_803E8150, param->p04);
	} else {
		self->w0 = lbl_1_rodata_1CF8;
	}

	fn_8012EBD4(&self->sprite2, param->p08);
	if (param->p08) {
		fn_1_120C4(&self->selector, 2);
		self->w1 = (f32)(u32)fn_8012EF3C(lbl_803E8150, param->p08);
	} else {
		self->w1 = lbl_1_rodata_1CF8;
	}

	fn_8012EBD4(&self->sprite3, param->p0c);
	if (param->p0c) {
		fn_1_120C4(&self->selector, 3);
		self->w2 = (f32)(u32)fn_8012EF3C(lbl_803E8150, param->p0c);
	} else {
		self->w2 = lbl_1_rodata_1CF8;
	}

	switch (param->i10) {
	case 0:
	case 2:
		self->unk_0x70 = 0;
		break;
	case 1:
		self->unk_0x70 = 0;
		break;
	}

	if (self->param.p04 == fn_8012ECA8(0, 0x54) ||
	    self->param.p04 == fn_8012ECA8(0, 0x56)) {
		if (self->param.p0c) {
			self->mode = 3;
			fn_1_119BC(&self->selector, 2);
		} else {
			self->mode = 2;
			fn_1_119BC(&self->selector, 1);
		}
	}

	return self;
}

// sADV_WINDOW_PARAM copy
void fn_1_15020(sADV_WINDOW_PARAM* dst, const sADV_WINDOW_PARAM* src)
{
	*dst = *src;
}

// ADV_WINDOW::Create(TObject*, const sADV_WINDOW_PARAM&)
ADV_WINDOW* fn_1_150AC(void* parent, const sADV_WINDOW_PARAM* param)
{
	ADV_WINDOW* obj = (ADV_WINDOW*)advE3Rom_resume(0x838);
	if (obj) {
		obj = fn_1_14DA4(obj, parent, param);
	}
	return obj;
}

// Release the loaded resources.
#pragma optimization_level 1
void fn_1_15108(void)
{
	void* h;
	ClearWindowResources(lbl_1_bss_834);

	h = lbl_1_bss_830;
	if (h) {
		fn_801A46D0(h);
		lbl_1_bss_830 = 0;
	}
}
#pragma optimization_level reset

// Load ./advertise/adv_window.one and resolve its sprites.
void fn_1_1517C(void)
{
	struct Handle {
		void* value;
	};
	Handle h;
	void* buf;
	int i;
	void* res;

	h.value = fn_80057644(0x58);
	if (h.value) {
		h.value = fn_800BCC84(h.value, lbl_1_data_8578, 0);
	}
	if (h.value) {
		buf = fn_80012994(0x300000);
		if (buf) {
			lbl_1_bss_830 = fn_800BC580(h.value, 2, buf);
			if (lbl_1_bss_830) {
				i = 0;
				do {
					res = fn_801A4BBC(lbl_1_bss_830, lbl_1_data_8528[i]);
					if (res) {
						lbl_1_bss_834[i] = *(void**)res;
					}
					i++;
				} while (i != 5);
			}
			fn_800126C8(buf);
		}
		fn_800BCBD4(h.value, 1);
	}
}

// ADV_WINDOW::Finalize() - unregister from the render list
#pragma dont_inline on
void fn_1_15268(void)
{
	fn_8012FF6C(lbl_803E8150);
	fn_1_15108();
}
#pragma dont_inline reset

// ADV_WINDOW::Initialize() - register with the render list
#pragma dont_inline on
void fn_1_15294(void)
{
	fn_1_1517C();
	fn_801301C8(lbl_803E8150);
}
#pragma dont_inline reset

// sADV_WINDOW_PARAM default construction.
void fn_1_152C0(sADV_WINDOW_PARAM* p)
{
	s32 zero = 0;
	p->p00 = (void*)zero;
	p->p04 = (void*)zero;
	p->p08 = (void*)zero;
	p->p0c = (void*)zero;
	p->i10 = zero;
	p->v14.x = lbl_1_rodata_1CF8;
	p->v14.y = lbl_1_rodata_1CF8;
	*(f32*)&p->i1c = lbl_1_rodata_1CF8;
	p->v20.x = lbl_1_rodata_1CF8;
	p->v20.y = lbl_1_rodata_1CF8;
	*(s32*)&p->v28.x = zero;
	*(s32*)&p->v28.y = zero;
	*(V2i*)&p->v30 = *(V2i*)(lbl_8029BB80 + 4);
	p->i38 = zero;
	p->i40 = 1;
	p->i3c = 1;
}

}
