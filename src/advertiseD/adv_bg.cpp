#include "types.h"

// advertiseD module (REL, module 1) - the TAdvBg attract-mode background task
// class plus its embedded menu-cursor helper. .text 0x112CC-0x122CC (~26
// functions). Class name string "TAdvBg" @data 0x7DC8. vtable
// lbl_1_data_81CC. Loads "adv_bg.one".
//
// PS2 reference: TAdvBg in advertise.cpp (SetMode/Disp/ExecToMain/ExecSubMode/
// ExecMain/Exec/__dt/__ct/Key/To/Create/Finalize/Initialize). GC bytes are
// ground truth; names below inspired by the PS2 symbols, not proven.
//
// Functions are ordered caller-before-callee (leaf helpers last) so MWCC emits
// `bl` to the helpers instead of inlining them.
//
// Object is NonMatching while the TU is carved; do not flip to Matching here.

extern "C" {

// ---- data / rodata / bss (dtk labels, paired by name) ------------------
struct Obj {
	u8 pad0[0x8];
	void* x8; // 0x8 -> per-window data
};

struct WinData {
	u8 pad0[0x84];
	f32 f84; // 0x84
	u8 pad88[0x8C - 0x88];
	f32 f8C; // 0x8C
};

// 8-byte {index, float} render-table entry (window->x8 array).
struct Ent {
	s32 a;
	f32 b;
};

// 8-byte {index, index} lookup-table entry (rodata_19D8).
struct Idx {
	s32 a;
	s32 b;
};

// TAdvBg task object (vtable at 0x18).
struct TAdvObject {
	/* 0x00 */ void* name;
	/* 0x04 */ u8 pad04[0x18 - 0x04];
	virtual void Disp(s32);
	virtual void slot0();
	virtual void slot4();
};

struct TAdvBg : TAdvObject {
	/* 0x1C */ u8 pad1C[0x1E - 0x1C];
	/* 0x1E */ u16 unk1E;
	/* 0x20 */ u8 pad20[0x28 - 0x20];
	/* 0x28 */ Obj* win[3]; // 0x28,0x2C,0x30
	/* 0x34 */ f32 posX[3]; // 0x34,0x38,0x3C
	/* 0x40 */ f32 posY[3]; // 0x40,0x44,0x48
	/* 0x4C */ s32 mode;    // 0x4C
	/* 0x50 */ s32 next;    // 0x50
	/* 0x54 */ s32 sub;     // 0x54
	/* 0x58 */ f32 f58;
	/* 0x5C */ f32 f5C;
	/* 0x60 */ f32 f60;
	/* 0x64 */ s32 i64;
	/* 0x68 */ s32 i68;
	/* 0x6C */ f32 f6C;
	void Exec();
};

// menu-cursor helper (array of ids at 0, counters at 0x80..).
struct Cursor {
	/* 0x00 */ s32 arr[32];
	/* 0x80 */ s32 count;
	/* 0x84 */ s32 index;
	/* 0x88 */ s32 wrap;
};

extern void* lbl_1_data_81CC[]; // TAdvBg vtable
extern u8 lbl_1_data_81B4[];    // task registration record
extern void* lbl_1_data_7DD0;   // -> class name
extern u8 lbl_1_data_8064[];    // window-0 template
extern char lbl_1_data_8220[];  // ADX/scene name
extern char lbl_1_data_8230[];
extern char lbl_1_data_8240[];
extern char lbl_1_data_8250[];
extern const Idx lbl_1_rodata_19D8[3];
extern const f32 lbl_1_rodata_19F0;
extern const f32 lbl_1_rodata_19F4;
extern TAdvBg* lbl_1_bss_7D0; // TAdvBg singleton

extern u8 lbl_80303EC8[];  // pad/edge controller object
extern u8 lbl_803E774C[];  // global sound/anim controller object
extern void* lbl_8042C180; // game-config handle
extern u8 lbl_8042C7E0[];  // scene/render object

// ---- external functions ------------------------------------------------
void fn_1_11030(TAdvBg*);
void fn_8012CC20(void*);
void fn_8012CE00(void*, f32, f32);
void fn_8012CA94(void*);
void fn_8012CB70(void*);
void fn_800CC9F4(char*);
void fn_800CCC6C(char*);
void fn_800CC1C4(void);
int fn_800A92E0(void*, int, int);
void* __ct__7TObjectFP7TObject(void*, void*);
void __dt__7TObjectFv(void*, int);
void advE3Rom_pause(void*);
void* advE3Rom_resume(s32);
void __dl__FPv(void*);
void* fn_80116D2C(void*);
void* memset(void*, int, int);
int fn_1_12A0(s8*, int);
int fn_801383F0(void*);
int fn_80138994(void*, int, int);
int fn_80116AE4(void*);
int fn_80117274(void*, int);

// forward declarations for the leaf helpers defined at the bottom
void fn_1_11320(TAdvBg* self);
void fn_1_11404(TAdvBg* self);
void fn_1_11438(TAdvBg* self);
TAdvBg* fn_1_11654(TAdvBg* self, void* parent);
void fn_1_11A38(Cursor* self);

// ---- destroy the three child windows -----------------------------------
void fn_1_112CC(TAdvBg* self)
{
	s32 i = 0;
	do {
		if (self->win[i]) {
			fn_8012CC20(self->win[i]);
		}
		i++;
	} while (i != 3);
}

// ---- window-0 slide animation ------------------------------------------
void fn_1_11320(TAdvBg* self)
{
	switch (self->sub) {
		case 0:
			self->posX[0] += lbl_1_rodata_19F4;
			if (self->f5C < self->posX[0]) {
				self->posX[0] = self->f58;
			}
			self->posX[2] += lbl_1_rodata_19F4;
			if (self->f60 < self->posX[2]) {
				self->win[2]  = 0;
				self->win[0]  = (Obj*)lbl_1_data_8064;
				self->posX[0] = ((WinData*)self->win[0]->x8)->f84;
				self->f60     = ((WinData*)self->win[0]->x8)->f8C;
				self->sub     = 1;
			}
			break;
		case 1:
			self->posX[0] += lbl_1_rodata_19F4;
			if (self->f60 < self->posX[0]) {
				self->next = 1;
			}
			break;
	}
}

// ---- window-0 clamp -----------------------------------------------------
void fn_1_11404(TAdvBg* self)
{
	self->posX[0] += lbl_1_rodata_19F4;
	if (self->f5C < self->posX[0]) {
		self->posX[0] = self->f58;
	}
}

// ---- window-1 table-driven slide ---------------------------------------
void fn_1_11438(TAdvBg* self)
{
	Ent* tbl0;
	Ent* tbl;
	if (self->i64 != self->i68) {
		tbl0          = (Ent*)self->win[1]->x8;
		tbl           = tbl0;
		self->posX[1] = tbl[lbl_1_rodata_19D8[self->i64].a].b;
		tbl           = (Ent*)self->win[1]->x8;
		self->f6C     = tbl[lbl_1_rodata_19D8[self->i64].b].b;
		self->i64     = self->i68;
	}
	self->posX[1] += lbl_1_rodata_19F4;
	if (self->f6C < self->posX[1]) {
		tbl           = (Ent*)self->win[1]->x8;
		self->posX[1] = tbl[lbl_1_rodata_19D8[self->i64].a].b;
		tbl           = (Ent*)self->win[1]->x8;
		self->f6C     = tbl[lbl_1_rodata_19D8[self->i64].a].b;
	}
}

// ---- Exec: run the current mode then draw the windows ------------------
#pragma dont_inline on
void TAdvBg::Exec()
{
	TAdvBg* self = this;
	s32 mode;
	s32 next;
	s32 i;
	mode = *(volatile s32*)&self->mode;
	next = *(volatile s32*)&self->next;
	if (mode != next) {
		fn_1_11030(self);
	}
	switch (self->mode) {
		case 1:
			fn_1_11438(self);
			fn_1_11404(self);
			break;
		case 2:
		case 3:
		case 4:
		case 5:
			fn_1_11404(self);
			break;
		case 6:
		case 7:
		case 8:
		case 9:
			fn_1_11320(self);
			break;
	}
	i = 0;
	do {
		if (self->win[i]) {
			fn_8012CE00(self->win[i], self->posX[i], self->posY[i]);
		}
		i++;
	} while (i != 3);
}
#pragma dont_inline reset

// ---- __dt ---------------------------------------------------------------
TAdvBg* fn_1_115DC(TAdvBg* self, int flag)
{
	if (self) {
		*(void**)((u8*)self + 0x18) = lbl_1_data_81CC;
		lbl_1_bss_7D0               = 0;
		__dt__7TObjectFv(self, 0);
		if ((s16)flag > 0) {
			advE3Rom_pause(self);
		}
	}
	return self;
}

// ---- __ct ---------------------------------------------------------------
TAdvBg* fn_1_11654(TAdvBg* self, void* parent)
{
	__ct__7TObjectFP7TObject(self, parent);
	*(void**)((u8*)self + 0x18) = lbl_1_data_81CC;
	self->name                  = lbl_1_data_7DD0;
	self->unk1E                 = 0x70;
	self->win[0]                = 0;
	self->posX[0]               = lbl_1_rodata_19F0;
	self->posY[0]               = lbl_1_rodata_19F4;
	self->win[1]                = 0;
	self->posX[1]               = lbl_1_rodata_19F0;
	self->posY[1]               = lbl_1_rodata_19F4;
	self->win[2]                = 0;
	self->posX[2]               = lbl_1_rodata_19F0;
	self->posY[2]               = lbl_1_rodata_19F4;
	self->mode                  = 0;
	self->next                  = 0;
	self->i64                   = 0;
	self->i68                   = 0;
	lbl_1_bss_7D0               = self;
	return self;
}

// ---- Key: advance the 3-cycle counter ----------------------------------
void fn_1_11704(void)
{
	TAdvBg* p = lbl_1_bss_7D0;
	if (p == 0) {
		return;
	}
	if (p->mode != 1) {
		return;
	}
	p->i68 = (p->i64 + 1) % 3;
}

// ---- SetMode ------------------------------------------------------------
void fn_1_11750(s32 mode)
{
	if (lbl_1_bss_7D0 == 0) {
		return;
	}
	if (mode == 1) {
		fn_800CC9F4(lbl_1_data_8220);
		switch (lbl_1_bss_7D0->mode) {
			case 2:
				fn_800CC9F4(lbl_1_data_8220);
				lbl_1_bss_7D0->next = 6;
				break;
			case 3:
				fn_800CC9F4(lbl_1_data_8220);
				lbl_1_bss_7D0->next = 7;
				break;
			case 4:
				fn_800CC9F4(lbl_1_data_8220);
				lbl_1_bss_7D0->next = 8;
				break;
			case 5:
				fn_800CCC6C(lbl_1_data_8220);
				lbl_1_bss_7D0->next = 9;
				break;
			case 6:
			case 7:
			case 8:
			case 9:
				break;
			default:
				lbl_1_bss_7D0->next = mode;
				break;
		}
	} else {
		switch (mode) {
			case 2:
				fn_800CC9F4(lbl_1_data_8230);
				break;
			case 3:
				fn_800CC9F4(lbl_1_data_8240);
				break;
			case 4:
				fn_800CC9F4(lbl_1_data_8250);
				break;
			case 5:
				fn_800CC1C4();
				break;
		}
		lbl_1_bss_7D0->next = mode;
	}
}

// ---- create the singleton if needed ------------------------------------
#pragma dont_inline on
void fn_1_118E4(void* parent)
{
	if (parent != 0) {
		if (lbl_1_bss_7D0 == 0) {
			TAdvBg* obj = (TAdvBg*)advE3Rom_resume(0x70);
			if (obj != 0) {
				fn_1_11654(obj, parent);
			}
		}
	}
}
#pragma dont_inline reset

// ---- Disp: forward to the singleton's virtual disp ---------------------
void fn_1_11940(void)
{
	fn_8012CA94(lbl_1_data_81B4);
	if (lbl_1_bss_7D0) {
		if (lbl_1_bss_7D0) {
			lbl_1_bss_7D0->Disp(1);
		}
	}
}

void fn_1_11994(void)
{
	fn_8012CB70(lbl_1_data_81B4);
}

// ---- cursor: set a small in-range value --------------------------------
void fn_1_119BC(Cursor* self, s32 n)
{
	if (n > 0 && n < 3) {
		self->index = n;
	}
}

// ---- cursor: enable wrap ------------------------------------------------
void fn_1_119D4(Cursor* self)
{
	self->wrap = 1;
}

// ---- cursor: select by value -------------------------------------------
void fn_1_119E0(Cursor* self, s32 val)
{
	s32* p;
	s32 i;
	for (i = 0, p = self->arr; i != self->count; p++, i++) {
		if (val == *p) {
			self->index = i;
			fn_1_11A38(self);
			break;
		}
	}
}

// ---- cursor: clamp/wrap the index --------------------------------------
void fn_1_11A38(Cursor* self)
{
	if (self->wrap != 0) {
		if (self->index < 0) {
			self->index = self->count - 1;
		}
		if (self->count > self->index) {
			return;
		}
		self->index = 0;
	} else {
		if (self->index < 0) {
			self->index = 0;
		}
		if (self->count > self->index) {
			return;
		}
		self->index = self->count - 1;
	}
}

// ---- cursor: 2D grid navigation ----------------------------------------
#pragma dont_inline on
#pragma opt_common_subs off
#pragma opt_propagation off
s32 fn_1_11AA8(Cursor* self, s32 col, s32 rowlen, s32 port)
{
	u32 x, sign;
	s32 shifted;
	u32 masked;
	s32 idx;
	s32 a;
	s32 b, c, d;
	if (port == -1) {
		port = 0;
	}
	a       = 1;
	b       = 1;
	c       = 1;
	d       = 1;
	idx     = self->index;
	x       = (u32)(col ^ idx);
	shifted = (s32)x >> 1;
	masked  = x;
	masked &= col;
	sign = (u32)(shifted - (s32)masked) >> 31;
	if (sign != 0) {
		a = 0;
	}
	if (sign == 0) {
		b = 0;
	}
	if (self->index == 0 || idx == col) {
		c = 0;
	}
	if (idx == col - 1 || idx == col + rowlen - 1) {
		d = 0;
	}
	if (a && fn_800A92E0(lbl_80303EC8, 8, port)) {
		self->index -= col;
		while (self->index >= col) {
			self->index--;
		}
	} else if (b && fn_800A92E0(lbl_80303EC8, 4, port)) {
		self->index += col;
		while (self->index < col) {
			self->index++;
		}
	} else if (c && fn_800A92E0(lbl_80303EC8, 1, port)) {
		self->index--;
	} else if (d && fn_800A92E0(lbl_80303EC8, 2, port)) {
		self->index++;
	}
	fn_1_11A38(self);
	if (self->index == -1) {
		return -1;
	}
	return self->arr[self->index];
}
#pragma opt_propagation reset
#pragma opt_common_subs reset

// ---- cursor: 4-way ring navigation -------------------------------------
s32 fn_1_11C8C(Cursor* self, s32 port)
{
	if (port == -1) {
		port = 0;
	}
	switch (self->index) {
		case 0:
			if (fn_800A92E0(lbl_80303EC8, 2, port)) {
				self->index = 2;
			}
			if (fn_800A92E0(lbl_80303EC8, 4, port)) {
				self->index = 1;
			}
			break;
		case 1:
			if (fn_800A92E0(lbl_80303EC8, 8, port)) {
				self->index = 0;
			}
			if (fn_800A92E0(lbl_80303EC8, 2, port)) {
				self->index = 3;
			}
			break;
		case 2:
			if (fn_800A92E0(lbl_80303EC8, 1, port)) {
				self->index = 0;
			}
			if (fn_800A92E0(lbl_80303EC8, 4, port)) {
				self->index = 3;
			}
			break;
		case 3:
			if (fn_800A92E0(lbl_80303EC8, 8, port)) {
				self->index = 2;
			}
			if (fn_800A92E0(lbl_80303EC8, 1, port)) {
				self->index = 1;
			}
			break;
	}
	fn_1_11A38(self);
	if (self->index == -1) {
		return -1;
	}
	return self->arr[self->index];
}

// ---- cursor: left/right navigation -------------------------------------
s32 fn_1_11E48(Cursor* self, s32 port)
{
	if (port == -1) {
		port = 0;
	}
	if (fn_800A92E0(lbl_80303EC8, 1, port)) {
		self->index--;
	} else if (fn_800A92E0(lbl_80303EC8, 2, port)) {
		self->index++;
	}
	fn_1_11A38(self);
	if (self->index == -1) {
		return -1;
	}
	return self->arr[self->index];
}

// ---- cursor: up/down navigation for both players -----------------------
s32 fn_1_11F00(Cursor* self)
{
	if (fn_800A92E0(lbl_80303EC8, 8, 0)) {
		self->index--;
	} else if (fn_800A92E0(lbl_80303EC8, 4, 0)) {
		self->index++;
	}
	fn_1_11A38(self);
	if (fn_800A92E0(lbl_80303EC8, 8, 1)) {
		self->index--;
	} else if (fn_800A92E0(lbl_80303EC8, 4, 1)) {
		self->index++;
	}
	fn_1_11A38(self);
	if (self->index == -1) {
		return -1;
	}
	return self->arr[self->index];
}

// ---- cursor: up/down navigation ----------------------------------------
s32 fn_1_11FFC(Cursor* self, s32 port)
{
	if (port == -1) {
		port = 0;
	}
	if (fn_800A92E0(lbl_80303EC8, 8, port)) {
		self->index--;
	} else if (fn_800A92E0(lbl_80303EC8, 4, port)) {
		self->index++;
	}
	fn_1_11A38(self);
	if (self->index == -1) {
		return -1;
	}
	return self->arr[self->index];
}
#pragma dont_inline reset

// ---- cursor: reset index/count -----------------------------------------
void fn_1_120B4(Cursor* self)
{
	self->index = 0;
	self->count = 0;
}

// ---- cursor: append id --------------------------------------------------
void fn_1_120C4(Cursor* self, s32 v)
{
	self->arr[self->count] = v;
	self->count++;
}

// ---- another __dt-style cleanup ----------------------------------------
void* fn_1_120E0(void* self, s32 flag)
{
	if (self != 0) {
		if ((s16)flag > 0) {
			__dl__FPv(self);
		}
	}
	return self;
}

// ---- cursor: full reset -------------------------------------------------
void fn_1_12124(Cursor* self)
{
	self->count = 0;
	self->index = 0;
	self->wrap  = 0;
}

// ---- save/controller readiness probe -----------------------------------
s32 fn_1_12138(void)
{
	void* a = (char*)fn_80116D2C(lbl_803E774C) + 0x624;
	void* b = (char*)fn_80116D2C(lbl_803E774C) + 0x3C;
	s32 buf[5];
	memset(buf, 0, 0x14);
	if (fn_1_12A0((s8*)lbl_8042C180, 0x27)) {
		buf[fn_801383F0(lbl_8042C7E0)] = 2;
	}
	if (fn_80138994(lbl_8042C7E0, 0, buf[0]) != 0x64 || fn_80138994(lbl_8042C7E0, 1, buf[1]) != 0x64
	    || fn_80138994(lbl_8042C7E0, 2, buf[2]) != 0x64
	    || fn_80138994(lbl_8042C7E0, 3, buf[3]) != 0x64) {
		return 0;
	}
	if (fn_80116AE4(a) != 7) {
		return 1;
	}
	if (fn_80138994(lbl_8042C7E0, 4, buf[4]) != 0x64) {
		return 2;
	}
	if (fn_80117274(b, 5) != 0x8d) {
		return 3;
	}
	if (fn_1_12A0((s8*)lbl_8042C180, 0x28) != 2) {
		return 4;
	}
	return 5;
}
}
