#include "types.h"

// advertiseD module (REL, module 1) - the ADV_OPTION options/config-menu task
// class. .text 0x0C1F0-0x0D090 (~14 functions). Its vtable is the run of
// function pointers at data 0x3CA8; the class name string "ADV_OPTION" lives at
// data 0x3C98 (pointer slot lbl_1_data_3CA4) and it loads "adv_option.one".
//
// PS2 reference: ADV_OPTION in advertise.cpp (SetMode/Create/__ct/OnExec/
// Initialize/Finalize/KillWindow/Exec plus the Exec* sub-state family). The GC
// build diverged from PS2; class shape/offsets are GC ground truth. This TU
// shares the ADVERTISE base object layout with adv_e3rom.cpp / adv_title.cpp
// and calls advE3Rom_pause/resume on that base.
//
// Object is NonMatching while the TU is carved; do not flip to Matching here.

extern "C" {

// 8-byte table entry {index, float}.
struct Ent8 {
	s32 a;
	f32 b;
};

// 0x28-byte menu-item entry.
struct Ent28 {
	u8 pad_00[0x24];
	s32 f24;
};

// global config object referenced through lbl_1_data_4B50.
struct Cfg4B50 {
	u8 pad_00[0x8];
	Ent8* p08; // 0x08
	u8 pad_0C[0x140 - 0xC];
	Ent8* p140; // 0x140
	u8 pad_144[0x1A8 - 0x144];
	Ent8* p1A8; // 0x1A8
};

// ---- shared ADVERTISE base object layout (ADV_OPTION extension) --------
struct Adv {
	/* 0x000 */ void* name;
	/* 0x004 */ u8 pad_004[0x18 - 0x04];
	/* 0x018 */ void* vtable;
	/* 0x01C */ u8 pad_01C[0x1E - 0x1C];
	/* 0x01E */ u16 unk_1E;
	/* 0x020 */ u8 pad_020[0x28 - 0x20];
	/* 0x028 */ s32 mode;
	/* 0x02C */ s32 state;
	/* 0x030 */ u8 pad_030[0x34 - 0x30];
	/* 0x034 */ f32 timer;
	/* 0x038 */ void* timeline;
	/* 0x03C */ u8 pad_03C[0x40 - 0x3C];
	/* 0x040 */ s32 unk_40;
	/* 0x044 */ s32 unk_44;
	/* 0x048 */ volatile s32 unk_48;
	/* 0x04C */ u8 pad_04C[0x60 - 0x4C];
	/* 0x060 */ s32 unk_60;
	/* 0x064 */ s32 unk_64;
	/* 0x068 */ u8 pad_068[0x6C - 0x68];
	/* 0x06C */ s32 unk_6C;
	/* 0x070 */ u8 pad_070[0x80 - 0x70];
	/* 0x080 */ s32 unk_80;
	/* 0x084 */ s32 unk_84;
	/* 0x088 */ s32 unk_88;
	/* 0x08C */ s32 unk_8C;
	/* 0x090 */ s32 unk_90;
	/* 0x094 */ s32 unk_94;
	/* 0x098 */ s32 unk_98;
	/* 0x09C */ s32 unk_9C;
	/* 0x0A0 */ u8 pad_0A0[0x10C - 0xA0];
	/* 0x10C */ s32 unk_10C;
	/* 0x110 */ u8 pad_110[0x128 - 0x110];
	/* 0x128 */ s32 unk_128;
	/* 0x12C */ u8 pad_12C[0x198 - 0x12C];
	/* 0x198 */ s32 unk_198;
	/* 0x19C */ s32 unk_19C;
	/* 0x1A0 */ u8 pad_1A0[0x1AC - 0x1A0];
	/* 0x1AC */ s32 unk_1AC;
	/* 0x1B0 */ s32 unk_1B0;
	/* 0x1B4 */ f32 unk_1B4;
	/* 0x1B8 */ u8 pad_1B8[0x1C0 - 0x1B8];
	/* 0x1C0 */ f32 unk_1C0;
	/* 0x1C4 */ f32 unk_1C4;
	/* 0x1C8 */ s32 unk_1C8;
	/* 0x1CC */ s32 unk_1CC;
	/* 0x1D0 */ s32 unk_1D0;
	/* 0x1D4 */ s32 unk_1D4;
	/* 0x1D8 */ u8 pad_1D8[0x1E0 - 0x1D8];
	/* 0x1E0 */ s32 unk_1E0;
	/* 0x1E4 */ u8 pad_1E4[0x240 - 0x1E4];
	/* 0x240 */ s32 unk_240;
	/* 0x244 */ u8 pad_244[0x2CC - 0x244];
	/* 0x2CC */ s32 unk_2CC;
	/* 0x2D0 */ u8 pad_2D0[0x358 - 0x2D0];
	/* 0x358 */ s32 unk_358;
	/* 0x35C */ u8 pad_35C[0x3F0 - 0x35C];
	/* 0x3F0 */ f32 unk_3F0;
	/* 0x3F4 */ f32 unk_3F4;
	/* 0x3F8 */ void* unk_3F8;
	/* 0x3FC */ s32 unk_3FC;
	/* 0x400 */ void* unk_400;
	/* 0x404 */ f32 unk_404;
	/* 0x408 */ s32 unk_408;
	/* 0x40C */ u8 pad_40C[0x4 * 3];
};

// ---- module data ------------------------------------------------------
extern void* lbl_1_data_3CA8[];  // ADV_OPTION vtable
extern void* lbl_1_data_3CA4;    // -> class name ("ADV_OPTION")
extern u8 lbl_1_data_3AB4[];     // default timeline
extern u8 lbl_1_data_3B8C[];     // mode-11 timeline
extern u8 lbl_1_data_3B3C[];     // .one load descriptor B
extern u8 lbl_1_data_3C80[];     // .one load descriptor A
extern Cfg4B50 lbl_1_data_4B50;  // global config object
extern Ent8* lbl_1_data_4D90[];  // per-page entry tables
extern Ent8* lbl_1_data_4DA0[];  // per-page entry tables (alt)
extern Ent28* lbl_1_data_5934[]; // per-page menu-item tables
extern s32 lbl_1_data_5944[];    // count table
extern void* lbl_8042C388;       // debug flag word
extern u8 lbl_80303EC8[];        // save/card controller object
extern u8 lbl_803E774C[];        // sound/anim controller object

extern const s32 lbl_1_rodata_F48[];
extern const s32 lbl_1_rodata_F90[];
extern const s32 lbl_1_rodata_FB0[];
extern const s32 lbl_1_rodata_FC8[];
extern const s32 lbl_1_rodata_FD8[];
extern const f32 lbl_1_rodata_102C;
extern const f32 lbl_1_rodata_1064;
extern const s32 lbl_1_rodata_1068[];
extern Ent8 lbl_1_rodata_10D8[];
extern Ent8 lbl_1_rodata_1098[];
extern s32 lbl_1_rodata_1108[];
extern Ent8 lbl_1_rodata_13B8[];
extern Ent8 lbl_1_rodata_13D8[];
extern const f32 lbl_1_rodata_13F8;
extern const f32 lbl_1_rodata_13FC;
extern const f32 lbl_1_rodata_1400;

// jump-through function pointers (callbacks)
void fn_1_120E0(void);
void fn_1_12124(void);

// ---- sibling-TU (adv_e3rom.cpp) shared base methods -------------------
void advE3Rom_pause(void*);
void* advE3Rom_resume(s32);

// ---- external functions (DOL / other modules) -------------------------
void fn_800A8120(void*);
void fn_800A8194(void*);
void fn_800A8264(void*);
void __ct__10DAnimClassFv(void*, int);
void fn_800A80E0(void*, const void*, int);
void fn_800A8620(void*, int);
void __ct__10EasySelectFP7TObject(void*);
void* fn_800A8BF0(void*);
int fn_800A9398(void*, int);
void fn_800B52E8(void*, int, int, int);
void fn_800CC280(void);
void fn_800CCC6C(char*);
int fn_80116B68(void*);
void* fn_80126200(void*);
void fn_8012CA94(void*);
void fn_8012CB70(void*);
void fn_8012CC20(void*);
void fn_8012CEF0(void*, f32);
void fn_8012EC18(void*, u16*, ...);
u16* fn_8012ECA8(int, int);
void fn_801255DC(void*);
void __destroy_arr(void*, void*, int, int);
void __construct_array(void*, void*, void*, int, int);

// ---- external functions in earlier TUs of this module -----------------
void fn_1_10F40(void*, void*);
void fn_1_11750(int);
int fn_1_11FFC(void*, int);
void fn_1_119D4(void*);
void fn_1_119E0(void*, int);
void fn_1_120B4(void*);
void fn_1_120C4(void*, int);
void fn_1_7B24(void*, void*);
void fn_1_B03C(void*, const s32*, int);
void fn_1_B078(void*, u16*);
void fn_1_B218(void*, u16*, u16*, u16*, int, int, int, int, int);
void fn_1_B1B4(void*);
void fn_1_B400(void*);
void fn_1_B518(void*);
void fn_1_B5DC(void*);
void fn_1_B674(void*);
void fn_1_B734(void*);
void fn_1_B828(void*);
void fn_1_B9E8(void*);
void fn_1_BC98(void*);
void fn_1_BE0C(void*);
void fn_1_BF80(void*);
void fn_1_C1CC(void*);
int fn_1_A9E0(void*);
int fn_1_A91C(void*);
int fn_1_A76C(void*);
int fn_1_A808(void*);
int fn_1_A714(void*);

// =======================================================================
// 0xC1F0 - SetMode: reconfigure the option menu for a new sub-mode.
void fn_1_C1F0(Adv* self, int mode)
{
	u16 buf[0x200];
	self->unk_80 = 0;
	switch (mode) {
		case 5:
			break;
		case 6:
			fn_1_B03C(self, lbl_1_rodata_F48, self->unk_94);
			break;
		case 7:
			fn_1_119E0(&self->unk_9C, self->unk_84);
			fn_1_B03C(self, lbl_1_rodata_F90, self->unk_84);
			break;
		case 8:
			fn_1_119E0(&self->unk_128, self->unk_88);
			fn_1_B03C(self, lbl_1_rodata_FB0, self->unk_88);
			break;
		case 10:
			if (self->unk_408 == 0) {
				fn_1_119E0(&self->unk_240, self->unk_90);
				fn_1_B03C(self, lbl_1_rodata_FC8, self->unk_90);
			} else {
				fn_1_119E0(&self->unk_1B4, self->unk_8C);
				fn_1_B03C(self, lbl_1_rodata_FD8, self->unk_8C);
			}
			break;
		case 12: {
			u16* msg = fn_8012ECA8(0, 0x39);
			fn_1_B078(self, msg);
			break;
		}
		case 15: {
			u16* m50;
			u16* m1 = fn_8012ECA8(1, 1);
			u16* m46;
			m50 = fn_8012ECA8(0, 0x50);
			m46 = fn_8012ECA8(0, 0x46);
			fn_1_B218(self, m46, m50, m1, 0, 0, 0, 0, 0);
			self->state = 0xf;
			break;
		}
		case 16: {
			u16* msg = fn_8012ECA8(0, 0x1b);
			fn_1_B078(self, msg);
			if (self->unk_3F8) {
				fn_801255DC(self->unk_3F8);
			}
			break;
		}
		case 17: {
			int n    = fn_80116B68(lbl_803E774C);
			u16* msg = fn_8012ECA8(0, 0xe);
			fn_8012EC18(buf, msg, n + 1);
			fn_1_B078(self, buf);
			break;
		}
		case 11: {
			fn_1_119E0(&self->unk_358, self->unk_98);
			self->timeline = lbl_1_data_3B8C;
			self->unk_400  = lbl_1_data_3B8C + 0x68;
			if (self->unk_98 == 0) {
				self->timer = lbl_1_rodata_1064;
			} else {
				self->timer = lbl_1_rodata_102C;
			}
			self->unk_404 = lbl_1_rodata_102C;
			break;
		}
	}
}

// 0xC450 - KillWindow: tear down the current option window if open.
void fn_1_C450(Adv* self)
{
	fn_800A8264(self);
	if (self->unk_400) {
		fn_8012CC20(self->unk_400);
	}
}

// 0xC48C - Exec: per-frame dispatch on the current sub-mode (0x28).
void fn_1_C48C(Adv* self)
{
	switch (self->mode) {
		case 5:
			fn_1_C1CC(self);
			break;
		case 6:
			fn_1_BF80(self);
			break;
		case 7:
			fn_1_BE0C(self);
			break;
		case 8:
			fn_1_BC98(self);
			break;
		case 10:
			fn_1_B9E8(self);
			break;
		case 11:
			fn_1_B828(self);
			break;
		case 12:
			fn_1_B734(self);
			break;
		case 13:
			fn_1_B674(self);
			break;
		case 14:
			fn_1_B1B4(self);
			break;
		case 16:
			fn_1_B518(self);
			break;
		case 17:
			fn_1_B400(self);
			break;
		case 15:
			fn_1_B5DC(self);
			break;
	}
	if (self->unk_400) {
		fn_8012CEF0(self->unk_400, self->unk_404);
	}
}

// 0xC54C - __ct.
Adv* fn_1_C54C(Adv* self, s16 flag)
{
	if (self) {
		self->vtable = lbl_1_data_3CA8;
		if ((self->unk_48 != 0 && self->unk_40 == 4) || (self->unk_48 == 0 && self->unk_44 == 4)) {
			fn_1_11750(1);
		}
		__destroy_arr(&self->unk_9C, (void*)fn_1_120E0, 0x8c, 6);
		fn_800A8620(self, 0);
		if (flag > 0) {
			advE3Rom_pause(self);
		}
	}
	return self;
}

// 0xC608 - Create: full field initialisation.
Adv* fn_1_C608(Adv* self, void* parent)
{
	void* p;
	(void)parent;
	__ct__10EasySelectFP7TObject(self);
	self->vtable = lbl_1_data_3CA8;
	__construct_array(&self->unk_9C, (void*)fn_1_12124, (void*)fn_1_120E0, 0x8c, 6);
	self->name     = lbl_1_data_3CA4;
	self->unk_1E   = 0x40c;
	self->unk_48   = 0;
	self->unk_40   = 4;
	self->unk_44   = 4;
	self->mode     = 0;
	self->state    = 5;
	self->unk_80   = 0;
	self->timeline = lbl_1_data_3AB4;
	self->unk_3F8  = fn_80126200(self);
	self->unk_3FC  = 0;
	self->unk_408  = 1;
	self->unk_400  = 0;
	self->unk_404  = lbl_1_rodata_102C;
	p              = fn_800A8BF0(lbl_80303EC8);
	switch (*(s32*)((char*)p + 4)) {
		case 3:
		case 8:
			self->unk_94 = 2;
			break;
		default:
			self->unk_94 = 0;
			break;
	}
	self->unk_84  = fn_1_A9E0(self);
	self->unk_88  = fn_1_A91C(self);
	self->unk_90  = fn_1_A76C(self);
	self->unk_8C  = fn_1_A808(self);
	self->unk_98  = fn_1_A714(self);
	self->unk_3F0 = lbl_1_rodata_102C;
	self->unk_3F4 = self->unk_3F0;
	fn_1_120C4(&self->unk_2CC, 0);
	fn_1_120C4(&self->unk_2CC, 1);
	fn_1_120C4(&self->unk_2CC, 2);
	fn_1_120C4(&self->unk_2CC, 3);
	fn_1_120C4(&self->unk_2CC, 4);
	fn_1_119E0(&self->unk_2CC, self->unk_94);
	fn_1_120C4(&self->unk_9C, 0);
	fn_1_120C4(&self->unk_9C, 1);
	fn_1_120C4(&self->unk_9C, 2);
	fn_1_119E0(&self->unk_9C, (int)self->unk_84);
	fn_1_120C4(&self->unk_128, 0);
	fn_1_120C4(&self->unk_128, 1);
	fn_1_119E0(&self->unk_128, (int)self->unk_88);
	fn_1_120C4(&self->unk_240, 0);
	fn_1_120C4(&self->unk_240, 1);
	fn_1_119E0(&self->unk_240, (int)self->unk_90);
	fn_1_120C4(&self->unk_1B4, 0);
	fn_1_120C4(&self->unk_1B4, 1);
	fn_1_120C4(&self->unk_1B4, 2);
	fn_1_120C4(&self->unk_1B4, 3);
	fn_1_120C4(&self->unk_1B4, 4);
	fn_1_120C4(&self->unk_1B4, 5);
	fn_1_119E0(&self->unk_1B4, (int)self->unk_8C);
	fn_1_120C4(&self->unk_358, 0);
	fn_1_120C4(&self->unk_358, 1);
	fn_1_119E0(&self->unk_358, (int)self->unk_98);
	p = advE3Rom_resume(0x30);
	if (p) {
		fn_1_10F40(p, self);
	}
	fn_1_11750(5);
	__ct__10DAnimClassFv(self, 4);
	return self;
}

// 0xC8D0 - OnExec: instantiate when the manager hands back a slot.
void fn_1_C8D0(Adv* self)
{
	Adv* obj = (Adv*)advE3Rom_resume(0x40c);
	if (obj) {
		fn_1_C608(obj, self);
	}
}

// 0xC910 - Initialize: load adv_option .one files.
void fn_1_C910(Adv* self)
{
	(void)self;
	fn_8012CA94(lbl_1_data_3C80);
	fn_8012CA94(lbl_1_data_3B3C);
}

// 0xC944 - Finalize: release adv_option .one files.
void fn_1_C944(Adv* self)
{
	(void)self;
	fn_8012CB70(lbl_1_data_3B3C);
	fn_8012CB70(lbl_1_data_3C80);
}

// 0xC978 - rebuild the entry list at 0x10C for the current page (0x198).
void fn_1_C978(Adv* self)
{
	int i;
	self->unk_1E0 = lbl_1_data_5944[self->unk_198];
	fn_1_120B4(&self->unk_10C);
	fn_1_119D4(&self->unk_10C);
	for (i = 0; i != self->unk_1E0; i++) {
		fn_1_120C4(&self->unk_10C, i);
	}
}

// 0xC9F4 - advance the mode timer; on expiry step to the next state.
void fn_1_C9F4(Adv* self)
{
	self->unk_1C0 += lbl_1_rodata_13F8;
	if (lbl_1_data_4B50.p140[self->unk_1CC].b < self->unk_1C0) {
		self->state  = 1;
		self->unk_60 = 8;
		fn_1_7B24(&self->unk_64, &lbl_1_rodata_13D8[self->unk_198]);
	}
}

// 0xCA80 - advance two timers with clamps, then commit the mode change.
void fn_1_CA80(Adv* self)
{
	self->unk_1C0 += lbl_1_rodata_13F8;
	if (lbl_1_data_4B50.p140[self->unk_1CC].b < self->unk_1C0) {
		self->unk_1C0 = lbl_1_data_4B50.p140[self->unk_1C8].b;
	}
	self->unk_1C4 += lbl_1_rodata_13FC;
	if (lbl_1_data_4B50.p1A8[self->unk_1D4].b - lbl_1_rodata_1400 < self->unk_1C4) {
		self->unk_1C4 = lbl_1_rodata_1400 + lbl_1_data_4B50.p1A8[self->unk_1D0].b;
	}
	switch (fn_800A9398(lbl_80303EC8, -1)) {
		case 1:
			if (lbl_8042C388) {
				fn_800B52E8(lbl_8042C388, 0xe009, 0, 0);
			}
			self->state = 0xb;
			break;
	}
}

// 0xCBA8 - poll the option controller; latch the pending index on match.
void fn_1_CBA8(Adv* self)
{
	fn_800A8194(self);
	if (self->unk_1B0 == self->unk_1AC) {
		if (self->unk_1B4 <= self->timer) {
			self->unk_1AC = (self->unk_1AC == 0);
		}
	}
}

// 0xCC08 - navigate the entry ring, resolving the selected item.
void fn_1_CC08(Adv* self)
{
	int idx;
	self->timer = lbl_1_data_4B50.p08[lbl_1_data_4D90[self->unk_198][self->unk_19C].a].b;
	idx         = fn_1_11FFC(&self->unk_10C, -1);
	if (idx != -1 && self->unk_19C != idx) {
		if (lbl_8042C388) {
			fn_800B52E8(lbl_8042C388, 0xe007, 0, 0);
		}
		if (idx == 0 && self->unk_19C == self->unk_1E0 - 1) {
			self->state  = 1;
			self->unk_6C = 1;
			self->unk_60 = 8;
			fn_1_7B24(&self->unk_64, &lbl_1_data_4DA0[self->unk_198][self->unk_19C]);
		} else if (self->unk_19C == 0 && idx == self->unk_1E0 - 1) {
			self->state  = 1;
			self->unk_6C = 1;
			self->unk_60 = 8;
			fn_1_7B24(&self->unk_64, &lbl_1_data_4D90[self->unk_198][self->unk_19C]);
		} else if (self->unk_19C < idx) {
			self->state  = 1;
			self->unk_6C = 1;
			self->unk_60 = 8;
			fn_1_7B24(&self->unk_64, &lbl_1_data_4DA0[self->unk_198][self->unk_19C]);
		} else {
			self->state  = 1;
			self->unk_6C = 1;
			self->unk_60 = 8;
			fn_1_7B24(&self->unk_64, &lbl_1_data_4D90[self->unk_198][self->unk_19C]);
		}
		self->unk_19C = idx;
	}
	switch (fn_800A9398(lbl_80303EC8, -1)) {
		case 0:
			break;
		case 1:
			if (lbl_8042C388) {
				fn_800B52E8(lbl_8042C388, 0xe009, 0, 0);
			}
			self->state  = 9;
			self->unk_60 = 5;
			fn_1_7B24(&self->unk_64, &lbl_1_rodata_10D8[self->unk_198]);
			self->unk_1B4 = lbl_1_data_4B50.p08[lbl_1_rodata_1108[self->unk_198]].b;
			break;
		case 2:
			if (lbl_1_data_5934[self->unk_198][self->unk_19C].f24 != 0) {
				if (lbl_8042C388) {
					fn_800B52E8(lbl_8042C388, 0xe008, 0, 0);
				}
				self->state  = 1;
				self->unk_60 = 0xa;
				fn_1_7B24(&self->unk_64, &lbl_1_rodata_13B8[self->unk_198]);
			}
			break;
	}
}

// 0xCF38 - commit the current page selection and fade out.
void fn_1_CF38(Adv* self)
{
	int idx = fn_1_11FFC(&self->unk_80, -1);
	if (idx != -1 && self->unk_198 != idx) {
		if (lbl_8042C388) {
			fn_800B52E8(lbl_8042C388, 0xe007, 0, 0);
		}
		self->unk_198 = idx;
		fn_800A80E0(self, lbl_1_rodata_1068, idx);
	} else {
		fn_800A8120(self);
		switch (fn_800A9398(lbl_80303EC8, -1)) {
			case 0:
				break;
			case 1:
				if (lbl_8042C388) {
					fn_800B52E8(lbl_8042C388, 0xe009, 0, 0);
				}
				self->state = 2;
				break;
			case 2:
				if (lbl_8042C388) {
					fn_800B52E8(lbl_8042C388, 0xe008, 0, 0);
				}
				self->state  = 1;
				self->unk_60 = 6;
				fn_1_7B24(&self->unk_64, &lbl_1_rodata_1098[self->unk_198]);
				break;
		}
	}
}

} // extern "C"
