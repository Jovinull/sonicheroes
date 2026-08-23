#include "types.h"

// ADV_PROGRESSIVE translation unit (advertise progressive-scan setup object).
//
// Reference-guided from the Sonic Heroes PS2 Sep-28-2003 debug prototype:
// class ADV_PROGRESSIVE from D:\Tsonic\Tsonic\src\advertise\adv_progressive.cpp.
// The GameCube retail REL bytes are ground truth; the PS2 build only supplies
// names/types/signatures/logic shape.
//
// vtable lbl_1_data_1D74 (name "ADV_PROGRESSIVE" @ data 0x1C50):
//   slot 0x08 = fn_1_6E74 (deleting dtor)
//   slot 0x2C = fn_1_6D08 (SetMode)
//   slot 0x30 = fn_1_6DF0 (OnExec)

// A shared sprite/font bank object. Field 0x8 is a positioned-value array
// (indexed as raw f32 words here).
struct Bank {
	/* 0x00 */ u8 pad_0x00[0x8];
	/* 0x08 */ f32* pos;
	/* 0x0c */ u8 pad_0x0c[0x5c];
}; // 0x68

// The vtable of the embedded child object (only its deleting dtor is used).
struct ObjVtbl {
	/* 0x00 */ void* slot_0x0;
	/* 0x04 */ void* slot_0x4;
	/* 0x08 */ void (*dt)(void* self, s32 flag);
};

// The embedded child object held at ADV_PROGRESSIVE::0x5c. The polymorphic
// part begins at 0x18 (an 0x18-byte non-virtual header precedes the vptr), so
// the call c->dt(1) is a real C++ virtual dispatch with the vptr at 0x18.
struct ObjHdr {
	u8 pad_0x00[0x18];
};
struct Obj : ObjHdr {
	virtual void dt(s32 flag);
};

struct ADV_PROGRESSIVE {
	/* 0x00 */ u8 pad_0x00[0x18];
	/* 0x18 */ void* vtable;
	/* 0x1c */ u8 pad_0x1c[0xc];
	/* 0x28 */ s32 f28;
	/* 0x2c */ s32 f2c;
	/* 0x30 */ s32 f30;
	/* 0x34 */ f32 f34;
	/* 0x38 */ Bank* f38;
	/* 0x3c */ u8 pad_0x3c[0x4];
	/* 0x40 */ s32 f40;
	/* 0x44 */ s32 f44;
	/* 0x48 */ s32 f48;
	/* 0x4c */ u8 pad_0x4c[0x10];
	/* 0x5c */ Obj* f5c;
	/* 0x60 */ u8 pad_0x60[0x20];
	/* 0x80 */ s32 f80;
	/* 0x84 */ s32 f84;
};

extern "C" {

// Module-shared data (dtk-named; addresses are ground truth).
extern u8 lbl_1_data_1D74;   // ADV_PROGRESSIVE vtable
extern Bank lbl_1_data_1CD0; // sprite bank
extern u8 lbl_1_data_1D5C;   // resource config record
extern u8 lbl_80303EC8;
extern s32 lbl_1_bss_568; // progressive-scan available flag
extern void* lbl_8042C180;

// Engine helpers (DOL / other REL objects).
extern void __ct__10EasySelectFP7TObject(ADV_PROGRESSIVE* self, void* parent);
extern void fn_800A8620(ADV_PROGRESSIVE* self, s32 flag);
extern void advE3Rom_pause(void* self);
extern void fn_801D5CB0(s32 flag);
extern void fn_800A8C8C(void* p);
extern void fn_1_11750(s32 arg);
extern void* advE3Rom_resume(s32 size);
extern void fn_800A960C(void* p, s32 code);
extern void fn_8012CA94(void* cfg);
extern void fn_8012CB70(void* cfg);
extern s32 fn_1_12A0(void* obj, s32 x);
extern u32 VIGetDTVStatus(void);

// Exec sub-states (defined earlier in the module, out of this slice).
extern void fn_1_6C74(ADV_PROGRESSIVE* self);
extern void fn_1_6B70(ADV_PROGRESSIVE* self);
extern void fn_1_6B24(ADV_PROGRESSIVE* self);
extern void fn_1_6B0C(ADV_PROGRESSIVE* self);

// SetMode: configure the object for the requested progressive-scan mode.
void fn_1_6D08(ADV_PROGRESSIVE* self, int mode)
{
	self->f30 = 0;
	switch (mode) {
		case 1:
			self->f38 = &lbl_1_data_1CD0;
			break;
		case 9:
			fn_801D5CB0(0);
			self->f38 = &lbl_1_data_1CD0;
			self->f34 = lbl_1_data_1CD0.pos[0xb];
			self->f28 = 0xa;
			self->f2c = 0xa;
			self->f80 = 2;
			break;
		case 7:
			fn_801D5CB0(1);
			fn_800A8C8C(&lbl_80303EC8);
			self->f38 = &lbl_1_data_1CD0;
			self->f34 = lbl_1_data_1CD0.pos[7];
			self->f28 = 0xa;
			self->f80 = 8;
			self->f2c = 0xa;
			break;
		case 6:
			self->f38 = &lbl_1_data_1CD0;
		case 10:
			break;
	}
}

// OnExec: dispatch on the current sub-state, then advance the frame counter.
void fn_1_6DF0(ADV_PROGRESSIVE* self)
{
	switch (self->f28) {
		case 5:
			fn_1_6C74(self);
			break;
		case 6:
			fn_1_6B70(self);
			break;
		case 8:
			fn_1_6B24(self);
			break;
		case 10:
			fn_1_6B0C(self);
			break;
	}
	self->f30++;
}

// Deleting destructor.
ADV_PROGRESSIVE* fn_1_6E74(ADV_PROGRESSIVE* self, s16 flag)
{
	if (self != 0) {
		self->vtable = &lbl_1_data_1D74;
		fn_800A8620(self, 0);
		if (flag > 0) {
			advE3Rom_pause(self);
		}
	}
	return self;
}

// Constructor.
#pragma dont_inline on
ADV_PROGRESSIVE* fn_1_6EDC(ADV_PROGRESSIVE* self, void* parent)
{
	Obj* c;

	__ct__10EasySelectFP7TObject(self, parent);
	self->vtable = &lbl_1_data_1D74;
	self->f28    = 0;
	self->f2c    = 5;
	self->f80    = 0;
	self->f48    = 1;
	self->f40    = 1;
	self->f44    = 1;
	self->f84    = 1;
	fn_1_11750(0);
	c = self->f5c;
	if (c != 0) {
		c->dt(1);
	}
	self->f5c = 0;
	return self;
}
#pragma dont_inline reset

// Create: allocate and construct the object when progressive scan is available.
void fn_1_6F70(void* parent)
{
	ADV_PROGRESSIVE* p;

	if (lbl_1_bss_568 != 0) {
		p = (ADV_PROGRESSIVE*)advE3Rom_resume(0x88);
		if (p != 0) {
			fn_1_6EDC(p, parent);
		}
	} else {
		fn_800A960C(&lbl_80303EC8, 0xc);
	}
}

// Finalize (static): release resources.
void fn_1_6FD8(void)
{
	if (lbl_1_bss_568 != 0) {
		fn_8012CA94(&lbl_1_data_1D5C);
	}
}

// Initialize (static): detect progressive-scan support and load resources.
void fn_1_7014(void)
{
	if (fn_1_12A0(lbl_8042C180, 0xf) != 2) {
		if (VIGetDTVStatus() == 0) {
			lbl_1_bss_568 = 0;
		} else {
			lbl_1_bss_568 = 1;
		}
	} else {
		lbl_1_bss_568 = 0;
	}
	if (lbl_1_bss_568 != 0) {
		fn_8012CB70(&lbl_1_data_1D5C);
	}
}
}
