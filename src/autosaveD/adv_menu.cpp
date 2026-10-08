#include "types.h"

// ADV_MENU - the menu-cursor helper shared with advertiseD (PS2: class ADV_MENU,
// SetSelect/OnLoop/Set/Commit/UpdateQUAD2/UpdateQUAD/UpdateLR/UpdateUD2/UpdateUD/
// Clr/Add/destructor/constructor, in this order). autosaveD .text 0x4074-0x47F0.
//
// advertiseD carries the same thirteen functions inside its adv_bg.cpp split
// (.text 0x119BC-0x12138); autosaveD has them on their own, which is why they
// form a unit here. The bodies below are that matching source, unchanged except
// for module-local names (fn_1_X there, fn_2_(X-0xD948) here); every function is
// byte-identical to its advertiseD counterpart with relocations masked. Taken
// over from the abandoned PR #116 (ThePlayerRolo), which proposed this ADV_MENU
// unit from PS2 symbols and identified the method of each function (noted above
// each definition; the GameCube symbols keep their fn_2_ names until both
// modules are renamed together). Keep both copies in sync.

extern "C" {

// menu-cursor helper (array of ids at 0, counters at 0x80..).
struct Cursor {
	/* 0x00 */ s32 arr[32];
	/* 0x80 */ s32 count;
	/* 0x84 */ s32 index;
	/* 0x88 */ s32 wrap;
};

extern u8 lbl_80303EC8[]; // pad/edge controller object

int fn_800A92E0(void*, int, int);
void __dl__FPv(void*);

// forward declaration for the clamp helper defined below
void fn_2_40F0(Cursor* self);

// ---- cursor: set a small in-range value --------------------------------
// PS2: ADV_MENU::SetSelect
void fn_2_4074(Cursor* self, s32 n)
{
	if (n > 0 && n < 3) {
		self->index = n;
	}
}

// ---- cursor: enable wrap ------------------------------------------------
// PS2: ADV_MENU::OnLoop
void fn_2_408C(Cursor* self)
{
	self->wrap = 1;
}

// ---- cursor: select by value -------------------------------------------
// PS2: ADV_MENU::Set
void fn_2_4098(Cursor* self, s32 val)
{
	s32* p;
	s32 i;
	for (i = 0, p = self->arr; i != self->count; p++, i++) {
		if (val == *p) {
			self->index = i;
			fn_2_40F0(self);
			break;
		}
	}
}

// ---- cursor: clamp/wrap the index --------------------------------------
// PS2: ADV_MENU::Commit
void fn_2_40F0(Cursor* self)
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
// PS2: ADV_MENU::UpdateQUAD2
s32 fn_2_4160(Cursor* self, s32 col, s32 rowlen, s32 port)
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
	fn_2_40F0(self);
	if (self->index == -1) {
		return -1;
	}
	return self->arr[self->index];
}
#pragma opt_propagation reset
#pragma opt_common_subs reset

// ---- cursor: 4-way ring navigation -------------------------------------
// PS2: ADV_MENU::UpdateQUAD
s32 fn_2_4344(Cursor* self, s32 port)
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
	fn_2_40F0(self);
	if (self->index == -1) {
		return -1;
	}
	return self->arr[self->index];
}

// ---- cursor: left/right navigation -------------------------------------
// PS2: ADV_MENU::UpdateLR
s32 fn_2_4500(Cursor* self, s32 port)
{
	if (port == -1) {
		port = 0;
	}
	if (fn_800A92E0(lbl_80303EC8, 1, port)) {
		self->index--;
	} else if (fn_800A92E0(lbl_80303EC8, 2, port)) {
		self->index++;
	}
	fn_2_40F0(self);
	if (self->index == -1) {
		return -1;
	}
	return self->arr[self->index];
}

// ---- cursor: up/down navigation for both players -----------------------
// PS2: ADV_MENU::UpdateUD2
s32 fn_2_45B8(Cursor* self)
{
	if (fn_800A92E0(lbl_80303EC8, 8, 0)) {
		self->index--;
	} else if (fn_800A92E0(lbl_80303EC8, 4, 0)) {
		self->index++;
	}
	fn_2_40F0(self);
	if (fn_800A92E0(lbl_80303EC8, 8, 1)) {
		self->index--;
	} else if (fn_800A92E0(lbl_80303EC8, 4, 1)) {
		self->index++;
	}
	fn_2_40F0(self);
	if (self->index == -1) {
		return -1;
	}
	return self->arr[self->index];
}

// ---- cursor: up/down navigation ----------------------------------------
// PS2: ADV_MENU::UpdateUD
s32 fn_2_46B4(Cursor* self, s32 port)
{
	if (port == -1) {
		port = 0;
	}
	if (fn_800A92E0(lbl_80303EC8, 8, port)) {
		self->index--;
	} else if (fn_800A92E0(lbl_80303EC8, 4, port)) {
		self->index++;
	}
	fn_2_40F0(self);
	if (self->index == -1) {
		return -1;
	}
	return self->arr[self->index];
}
#pragma dont_inline reset

// ---- cursor: reset index/count -----------------------------------------
// PS2: ADV_MENU::Clr
void fn_2_476C(Cursor* self)
{
	self->index = 0;
	self->count = 0;
}

// ---- cursor: append id --------------------------------------------------
// PS2: ADV_MENU::Add
void fn_2_477C(Cursor* self, s32 v)
{
	self->arr[self->count] = v;
	self->count++;
}

// ---- another __dt-style cleanup ----------------------------------------
// PS2: ADV_MENU::~ADV_MENU
void* fn_2_4798(void* self, s32 flag)
{
	if (self != 0) {
		if ((s16)flag > 0) {
			__dl__FPv(self);
		}
	}
	return self;
}

// ---- cursor: full reset -------------------------------------------------
// PS2: ADV_MENU::ADV_MENU
void fn_2_47DC(Cursor* self)
{
	self->count = 0;
	self->index = 0;
	self->wrap  = 0;
}

} // extern "C"
