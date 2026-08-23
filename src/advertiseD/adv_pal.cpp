#include "types.h"

// ADV_PAL translation unit (advertise PAL / deflicker setup object).
//
// Reference-guided from the Sonic Heroes PS2 Sep-28-2003 debug prototype:
// class ADV_PAL from D:\Tsonic\Tsonic\src\advertise\adv_pal.cpp. The GameCube
// retail REL bytes are ground truth; the PS2 build only supplies
// names/types/signatures/logic shape.
//
// vtable lbl_1_data_7B8C (name "ADV_PAL" @ data 0x7B80):
//   slot 0x08 = fn_1_109FC (deleting dtor)
//   slot 0x2C = fn_1_1086C (SetMode)
//   slot 0x30 = fn_1_1098C (OnExec)

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

// The embedded child object held at ADV_PAL::0x5c.
// Polymorphic child: an 0x18-byte non-virtual header precedes the vptr, so
// c->dt(1) is a real C++ virtual dispatch with the vptr materialized at 0x18
// (dt is the first virtual, landing at vtable +0x8 after CW's 8-byte header).
struct ObjHdr {
	u8 pad_0x00[0x18];
};
struct Obj : ObjHdr {
	virtual void dt(s32 flag);
};

struct ADV_PAL {
	/* 0x000 */ void* name;
	/* 0x004 */ u8 pad_0x04[0x14];
	/* 0x018 */ void* vtable;
	/* 0x01c */ u8 pad_0x1c[0x2];
	/* 0x01e */ u16 size;
	/* 0x020 */ u8 pad_0x20[0x8];
	/* 0x028 */ s32 f28;
	/* 0x02c */ s32 f2c;
	/* 0x030 */ u8 pad_0x30[0x4];
	/* 0x034 */ f32 f34;
	/* 0x038 */ Bank* f38;
	/* 0x03c */ u8 pad_0x3c[0x4];
	/* 0x040 */ s32 f40;
	/* 0x044 */ s32 f44;
	/* 0x048 */ u8 pad_0x48[0x14];
	/* 0x05c */ Obj* f5c;
	/* 0x060 */ s32 f60;
	/* 0x064 */ s32 f64;
	/* 0x068 */ s32 f68;
	/* 0x06c */ u8 pad_0x6c[0x14];
	/* 0x080 */ u8 unk_0x80[0x8c];
	/* 0x10c */ s32 f10c;
	/* 0x110 */ s32 f110;
};

extern "C" {

// Module-shared data (dtk-named; addresses are ground truth).
extern u8 lbl_1_data_7B8C;          // ADV_PAL vtable
extern Bank lbl_1_data_7A7C[2];     // sprite banks (stride 0x68)
extern void* const lbl_1_data_7B88; // -> "ADV_PAL"
extern u8 lbl_1_data_7B68;          // resource config record
extern u8 lbl_80303EC8;
extern const s32 lbl_1_rodata_19C0[2];
extern const f32 lbl_1_rodata_19C8;
extern s32 lbl_1_bss_7B8; // resource-loaded flag
extern s32 lbl_1_bss_7BC; // deflicker-mode flag
extern void* lbl_8042C180;

// Engine helpers (DOL / other REL objects).
extern void __ct__10EasySelectFP7TObject(ADV_PAL* self, void* parent);
extern void fn_800A8620(ADV_PAL* self, s32 flag);
extern void advE3Rom_pause(void* self);
extern void fn_800A8C7C(void* p);
extern void fn_801D5DC4(s32 flag);
extern void fn_1_12124(void* sub);
extern void fn_1_120E0(void* sub, s32 flag);
extern void fn_1_120C4(void* sub, s32 flag);
extern void fn_1_119E0(void* sub, s32 flag);
extern void fn_1_11750(s32 arg);
extern void* advE3Rom_resume(s32 size);
extern void fn_800A960C(void* p, s32 code);
extern void fn_8012CA94(void* cfg);
extern void fn_8012CB70(void* cfg);
extern s32 fn_1_12A0(void* obj, s32 x);

// Exec sub-states (defined earlier in the module, out of this slice).
extern void fn_1_10634(ADV_PAL* self);
extern void fn_1_10698(ADV_PAL* self);
extern void fn_1_106A4(ADV_PAL* self);
extern void fn_1_106E8(ADV_PAL* self);
extern void fn_1_107F8(ADV_PAL* self);

// SetMode: configure the object for the requested PAL/deflicker mode.
void fn_1_1086C(ADV_PAL* self, int mode)
{
	self->f110 = 0;
	switch (mode) {
		case 0:
			break;
		case 1:
			self->f60 = 6;
			self->f64 = 0;
			self->f68 = 1;
			self->f38 = &lbl_1_data_7A7C[0];
			break;
		case 6:
			self->f38 = &lbl_1_data_7A7C[0];
			self->f34 = lbl_1_data_7A7C[0].pos[lbl_1_rodata_19C0[self->f10c] * 2 + 1];
			break;
		case 9:
			self->f38 = &lbl_1_data_7A7C[1];
			self->f34 = lbl_1_rodata_19C8;
			break;
		case 7:
			fn_800A8C7C(&lbl_80303EC8);
			fn_801D5DC4(1);
			self->f38 = &lbl_1_data_7A7C[0];
			self->f34 = lbl_1_data_7A7C[0].pos[7];
			break;
		case 8:
			fn_801D5DC4(0);
			self->f38 = &lbl_1_data_7A7C[0];
			self->f34 = lbl_1_data_7A7C[0].pos[0xb];
			break;
	}
}

// OnExec: dispatch on the current sub-state.
void fn_1_1098C(ADV_PAL* self)
{
	switch (self->f28) {
		case 5:
			fn_1_107F8(self);
			break;
		case 6:
			fn_1_106E8(self);
			break;
		case 7:
			fn_1_106A4(self);
			break;
		case 8:
			fn_1_10698(self);
			break;
		case 9:
			fn_1_10634(self);
			break;
	}
}

// Deleting destructor.
ADV_PAL* fn_1_109FC(ADV_PAL* self, s16 flag)
{
	if (self != 0) {
		self->vtable = &lbl_1_data_7B8C;
		fn_1_120E0(&self->unk_0x80, -1);
		fn_800A8620(self, 0);
		if (flag > 0) {
			advE3Rom_pause(self);
		}
	}
	return self;
}

// Constructor.
#pragma dont_inline on
ADV_PAL* fn_1_10A74(ADV_PAL* self, void* parent)
{
	Obj* c;

	__ct__10EasySelectFP7TObject(self, parent);
	self->vtable = &lbl_1_data_7B8C;
	fn_1_12124(&self->unk_0x80);
	self->name = lbl_1_data_7B88;
	self->size = 0x114;
	self->f40  = 1;
	self->f44  = 1;
	if (lbl_1_bss_7BC == 0) {
		self->f28 = 0;
		self->f2c = 5;
	} else {
		self->f28 = 0;
		self->f2c = 9;
	}
	self->f38 = 0;
	fn_1_120C4(&self->unk_0x80, 0);
	fn_1_120C4(&self->unk_0x80, 1);
	fn_1_119E0(&self->unk_0x80, 1);
	self->f10c = 1;
	self->f110 = 0;
	fn_1_11750(0);
	c = self->f5c;
	if (c != 0) {
		c->dt(1);
	}
	self->f5c = 0;
	return self;
}
#pragma dont_inline reset

// Create: allocate and construct the object when resources are loaded.
void fn_1_10B80(void* parent)
{
	ADV_PAL* p;

	if (lbl_1_bss_7B8 != 0) {
		p = (ADV_PAL*)advE3Rom_resume(0x114);
		if (p != 0) {
			fn_1_10A74(p, parent);
		}
	} else {
		fn_800A960C(&lbl_80303EC8, 1);
	}
}

// Finalize (static): release resources.
void fn_1_10BE8(void)
{
	if (lbl_1_bss_7B8 != 0) {
		fn_8012CA94(&lbl_1_data_7B68);
	}
}

// Initialize (static): load resources when PAL mode is active.
void fn_1_10C24(void)
{
	lbl_1_bss_7B8 = fn_1_12A0(lbl_8042C180, 0xf) == 2 ? 1 : 0;
	if (lbl_1_bss_7B8 != 0) {
		fn_8012CB70(&lbl_1_data_7B68);
	}
}
}
