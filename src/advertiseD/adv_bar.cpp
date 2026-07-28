#include "types.h"

// ADV_BAR translation unit (advertise progress/help bar helper objects).
//
// Reference-guided from the Sonic Heroes PS2 Sep-28-2003 debug prototype:
// classes TAdvBar / TAdvHelp (and the head of TAdvBg) from
// D:\Tsonic\Tsonic\src\advertise\adv_bar.cpp. The GameCube retail REL bytes are
// ground truth; the PS2 build only supplies names/types/signatures/logic shape.
//
// vtable -> class map (from ctor typename/config stores; note the campaign
// brief's TAdvHelp/TAdvBar labels were swapped; data proves the mapping):
//   lbl_1_data_7D6C = TAdvBar  (name "TAdvBar",  ./advertise/%s/adv_bar.one)
//   lbl_1_data_7D98 = TAdvHelp (name "TAdvHelp", ./advertise/adv_help.one)

// A shared sprite/font bank object. Field 0x8 is a positioned-value array
// (indexed as raw f32 words here).
struct Bank {
	/* 0x00 */ u8 pad_0x00[0x8];
	/* 0x08 */ f32* pos;
	/* 0x0c */ u8 pad_0x0c[0x5c];
}; // 0x68

// Common layout of TAdvBar / TAdvHelp (derive from the engine base
// fn_80018818 / dtor_800186D0).
struct TAdvBar {
	/* 0x00 */ void* name;
	/* 0x04 */ u8 pad_0x04[0x14];
	/* 0x18 */ void* vtable;
	/* 0x1c */ u8 pad_0x1c[0x2];
	/* 0x1e */ u16 size;
	/* 0x20 */ u8 pad_0x20[0x8];
	/* 0x28 */ Bank* sub;
	/* 0x2c */ f32 value;
};

// The TAdvBg background object (only SetMode + the singleton getter live in
// this slice; the rest of the class is beyond the split range).
struct TAdvBg {
	/* 0x00 */ u8 pad_0x00[0x28];
	/* 0x28 */ Bank* bankA;
	/* 0x2c */ Bank* bankB;
	/* 0x30 */ Bank* bankC;
	/* 0x34 */ f32 f34;
	/* 0x38 */ f32 f38;
	/* 0x3c */ f32 f3c;
	/* 0x40 */ u8 pad_0x40[0xc];
	/* 0x4c */ s32 mode;
	/* 0x50 */ s32 f50;
	/* 0x54 */ s32 f54;
	/* 0x58 */ f32 f58;
	/* 0x5c */ f32 f5c;
	/* 0x60 */ f32 f60;
	/* 0x64 */ s32 f64;
	/* 0x68 */ s32 f68;
	/* 0x6c */ f32 f6c;
};

extern "C" {

// Module-shared data (dtk-named; addresses are ground truth).
extern u8 lbl_1_data_7D6C;          // TAdvBar vtable
extern u8 lbl_1_data_7D98;          // TAdvHelp vtable
extern void* const lbl_1_data_7CBC; // -> "TAdvBar"
extern void* const lbl_1_data_7BF4; // -> "TAdvHelp"
extern Bank lbl_1_data_7CD0;        // TAdvBar sprite bank
extern Bank lbl_1_data_7C18;        // TAdvHelp sprite bank
extern u8 lbl_1_data_7D54;          // TAdvBar config record
extern u8 lbl_1_data_7C9C;          // TAdvHelp config record
extern Bank lbl_1_data_8064[3];     // TAdvBg sprite banks (stride 0x68)
extern TAdvBg* lbl_1_bss_7D0;       // TAdvBg singleton pointer
extern const f32 lbl_1_rodata_19D0; // 1.0
extern const f32 lbl_1_rodata_19F0; // 0.0

// Engine base + render helpers (DOL / other REL objects).
extern void fn_80018818(void* self);
extern void dtor_800186D0(void* self, s32 flag);
extern void advE3Rom_pause(void* self);
extern void fn_8012CA94(void* cfg);
extern void fn_8012CB70(void* cfg);
extern void fn_8012CC20(Bank* b);
extern void fn_8012CEF0(Bank* b, f32 v);

// ---- TAdvBar (vtable 0x7D6C) -------------------------------------------

// Disp: draw the sprite bank.
void fn_1_10C88(TAdvBar* self)
{
	if (self->sub != 0) {
		fn_8012CC20(self->sub);
	}
}

// Exec: step the value toward the bank target, then draw.
void fn_1_10CB4(TAdvBar* self)
{
	f32 y = self->sub->pos[3];
	if (self->value < y) {
		self->value += lbl_1_rodata_19D0;
	} else {
		self->value = y;
	}
	if (self->sub != 0) {
		fn_8012CEF0(self->sub, self->value);
	}
}

// Deleting destructor.
TAdvBar* fn_1_10D1C(TAdvBar* self, s16 flag)
{
	if (self != 0) {
		self->vtable = &lbl_1_data_7D6C;
		dtor_800186D0(self, 0);
		if (flag > 0) {
			advE3Rom_pause(self);
		}
	}
	return self;
}

// Constructor.
TAdvBar* fn_1_10D84(TAdvBar* self, void* parent)
{
	fn_80018818(self);
	self->vtable = &lbl_1_data_7D6C;
	self->name   = lbl_1_data_7CBC;
	self->size   = 0x30;
	self->sub    = &lbl_1_data_7CD0;
	self->value  = self->sub->pos[1];
	return self;
}

// Finalize (static): release resources.
void fn_1_10DF4(void)
{
	fn_8012CA94(&lbl_1_data_7D54);
}

// Initialize (static): load resources.
void fn_1_10E1C(void)
{
	fn_8012CB70(&lbl_1_data_7D54);
}

// ---- TAdvHelp (vtable 0x7D98) ------------------------------------------

// Disp.
void fn_1_10E44(TAdvBar* self)
{
	if (self->sub != 0) {
		fn_8012CC20(self->sub);
	}
}

// Exec.
void fn_1_10E70(TAdvBar* self)
{
	f32 y = self->sub->pos[3];
	if (self->value < y) {
		self->value += lbl_1_rodata_19D0;
	} else {
		self->value = y;
	}
	if (self->sub != 0) {
		fn_8012CEF0(self->sub, self->value);
	}
}

// Deleting destructor.
TAdvBar* fn_1_10ED8(TAdvBar* self, s16 flag)
{
	if (self != 0) {
		self->vtable = &lbl_1_data_7D98;
		dtor_800186D0(self, 0);
		if (flag > 0) {
			advE3Rom_pause(self);
		}
	}
	return self;
}

// Constructor.
TAdvBar* fn_1_10F40(TAdvBar* self, void* parent)
{
	fn_80018818(self);
	self->vtable = &lbl_1_data_7D98;
	self->name   = lbl_1_data_7BF4;
	self->size   = 0x30;
	self->sub    = &lbl_1_data_7C18;
	self->value  = self->sub->pos[1];
	return self;
}

// Finalize (static).
void fn_1_10FB0(void)
{
	fn_8012CA94(&lbl_1_data_7C9C);
}

// Initialize (static).
void fn_1_10FD8(void)
{
	fn_8012CB70(&lbl_1_data_7C9C);
}

// ---- TAdvBg (partial) --------------------------------------------------

// Query whether the TAdvBg singleton is in an active mode.
s32 fn_1_11000(void)
{
	TAdvBg* g = lbl_1_bss_7D0;
	if (g != 0) {
		return g->mode != 0;
	}
	return 0;
}

// SetMode: point the background at the sprite banks for the given mode.
void fn_1_11030(TAdvBg* self, s32 mode)
{
	self->mode = mode;
	self->f50  = mode;
	self->f54  = 0;
	switch (mode) {
		case 0:
			self->bankA = 0;
			self->bankB = 0;
			self->bankC = 0;
			break;
		case 1:
			self->bankA = &lbl_1_data_8064[0];
			self->f34   = self->bankA->pos[0x25];
			self->f58   = self->bankA->pos[0x25];
			self->f5c   = self->bankA->pos[0x27];
			self->bankB = &lbl_1_data_8064[2];
			self->f38   = lbl_1_rodata_19F0;
			self->bankC = 0;
			self->f3c   = lbl_1_rodata_19F0;
			self->f64   = 0;
			self->f68   = 0;
			self->f6c   = lbl_1_rodata_19F0;
			break;
		case 2:
			self->bankA = &lbl_1_data_8064[0];
			self->f34   = self->bankA->pos[1];
			self->f58   = self->bankA->pos[5];
			self->f5c   = self->bankA->pos[7];
			self->bankB = 0;
			self->bankC = 0;
			break;
		case 3:
			self->bankA = &lbl_1_data_8064[0];
			self->f34   = self->bankA->pos[9];
			self->f58   = self->bankA->pos[0xd];
			self->f5c   = self->bankA->pos[0xf];
			self->bankB = 0;
			self->bankC = 0;
			break;
		case 4:
			self->bankA = &lbl_1_data_8064[0];
			self->f34   = self->bankA->pos[0x11];
			self->f58   = self->bankA->pos[0x15];
			self->f5c   = self->bankA->pos[0x17];
			self->bankB = 0;
			self->bankC = 0;
			break;
		case 5:
			self->bankA = &lbl_1_data_8064[0];
			self->f34   = self->bankA->pos[0x19];
			self->f58   = self->bankA->pos[0x1d];
			self->f5c   = self->bankA->pos[0x1f];
			self->bankB = 0;
			self->bankC = 0;
			break;
		case 6:
			self->bankC = &lbl_1_data_8064[1];
			self->f3c   = self->bankC->pos[1];
			self->f60   = self->bankC->pos[3];
			break;
		case 7:
			self->bankC = &lbl_1_data_8064[1];
			self->f3c   = self->bankC->pos[5];
			self->f60   = self->bankC->pos[7];
			break;
		case 8:
			self->bankC = &lbl_1_data_8064[1];
			self->f3c   = self->bankC->pos[9];
			self->f60   = self->bankC->pos[0xb];
			break;
		case 9:
			self->bankC = &lbl_1_data_8064[1];
			self->f3c   = self->bankC->pos[0xd];
			self->f60   = self->bankC->pos[0xf];
			break;
	}
}
}
