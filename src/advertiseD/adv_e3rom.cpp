#include "types.h"

// advertiseD module (REL, module 1) - the ADV_E3ROM attract-mode base/title
// task class. This is the first translation unit in the module, .text
// 0x00000-0x0101C. The class name string "ADV_E3ROM" lives at data 0x10 and
// the class loads "./advertise/adv_e3rom.one" (data 0x1DC). Its vtable is the
// run of function pointers at data 0x210.
//
// PS2 reference: the semantically-nearest class is ADV_TITLE in advertise.cpp
// (ExecTitle/SetMode/OnExec/Create/__ct/Initialize/Finalize). The GC build is
// more elaborate; the names below are inspired by that class, not proven.
//
// The five one-instruction `blr` methods advBase_nullVirt0..4 are the shared
// base's empty default virtuals: the exact same five pointers appear in every
// class vtable across the module.
//
// Object is NonMatching while the TU is carved; do not flip to Matching here.

extern "C" {

// ---- module data (dtk labels; paired by name) --------------------------
extern void* lbl_1_data_210[]; // the ADV_E3ROM vtable
extern void* lbl_1_data_1C;    // -> "ADV_E3ROM" (class name pointer)
extern char lbl_1_data_244[];  // "TITLE.ADX"
extern u8 lbl_1_data_1F8[];    // .one load descriptor
extern void* lbl_8042C148;     // DOL task-manager handle
extern void* lbl_1_bss_8;
extern s32 lbl_1_bss_C;
extern const f32 lbl_1_rodata_0;
extern const f32 lbl_1_rodata_4;
extern const f32 lbl_1_rodata_8;
extern const f32 lbl_1_rodata_10;
extern const f32 lbl_1_rodata_14;

// ---- external functions (DOL / other modules) --------------------------
void fn_800CCC6C(char*);
void fn_8012CC20(void*);
void fn_8012CFA4(void*);
void fn_8012D3A4(void*);
void fn_800189A4(void*, void*);
void* fn_80018A34(void*, void*);
void fn_80204144(void*, void*, void*);
f32 fn_802012B0(void*);
f32 fn_802012B8(void*);
void fn_800CC280(void);
void fn_800A8620(void*, int);
void fn_800A8828(void*);
// disp/exec externs
extern void* lbl_8042C180;    // manager handle (loaded then passed)
extern void* lbl_8042C388;    // sound/system handle (loaded)
extern s32 lbl_1_data_20;     // module state flag
extern s32 lbl_803EC340[];    // scene param block
extern u8 lbl_8029C310[];     // draw/anim object
extern u8 lbl_80303EC8[];     // task/effect object
extern u8 lbl_803E774C[];     // path/name buffer
extern u8 lbl_1_data_A4[];    // clip endpoint table
extern u8 lbl_8029BBD0[];     // per-slot descriptor table
extern s32 lbl_802408F8;      // current slot index
extern char lbl_1_data_250[]; // "TITLE" script name

extern u8 lbl_8029C310[];
void fn_8001934C(void*, int, int);
void fn_8001936C(void*, int, int);
void fn_8001938C(void*);
void fn_800A96B0(void*, int, int);
void fn_800B52E8(void*, int, int, int);
int fn_80116B68(void*);
int fn_800A92E0(void*, int, int);
int fn_800158A0(void*, int);
int fn_800158EC(void*, int);
void fn_8012CEF0(void*, f32);
int fn_1_12A0(void*, int);

// ---- object layout -----------------------------------------------------
struct AdvTimelineInner {
	u8 pad_00[0xC];
	f32 limit; // 0x0C
};
struct AdvTimeline {
	u8 pad_00[0x8];
	AdvTimelineInner* inner; // 0x08
};
struct AdvClip {
	u8 pad_00[0xC];
	f32 f0C; // 0x0C
	u8 pad_10[0x14 - 0x10];
	f32 f14; // 0x14
	u8 pad_18[0x1C - 0x18];
	f32 f1C; // 0x1C
	u8 pad_20[0x24 - 0x20];
	f32 f24; // 0x24
};

struct AdvE3Rom {
	/* 0x00 */ void* name;
	/* 0x04 */ u16 flags;
	/* 0x06 */ u8 pad_06[0x18 - 0x06];
	/* 0x18 */ void* vtable;
	/* 0x1C */ u8 pad_1C[0x1E - 0x1C];
	/* 0x1E */ u16 unk_1E;
	/* 0x20 */ u8 pad_20[0x2C - 0x20];
	/* 0x2C */ s32 unk_2C;
	/* 0x30 */ u8 pad_30[0x34 - 0x30];
	/* 0x34 */ f32 timer;
	/* 0x38 */ AdvTimeline* timeline;
	/* 0x3C */ u8 pad_3C[0x40 - 0x3C];
	/* 0x40 */ s32 unk_40;
	/* 0x44 */ u8 pad_44[0x48 - 0x44];
	/* 0x48 */ s32 unk_48;
	/* 0x4C */ u8 pad_4C[0x80 - 0x4C];
	/* 0x80 */ s32 mode;
	/* 0x84 */ s32 counter;
	/* 0x88 */ void* se;
};

// forward decls (intra-TU calls)
void advE3Rom_setMode(AdvE3Rom* self, s32 mode);
void advE3Rom_setFlag(AdvE3Rom* self);
void advE3Rom_pause(void* obj);
void* advE3Rom_resume(s32 id);
AdvE3Rom* advE3Rom_create(AdvE3Rom* self, void* parent);
void* advE3Rom_cbVolL(void* a, void* b, int c, s32* out);
void* advE3Rom_cbVolR(void* a, void* b, int c, f32* out);

#pragma force_active on
#pragma dont_inline on

// 0x000 - kick the title back to mode 1 unless idle/finished.
void advE3Rom_kick(AdvE3Rom* self)
{
	switch (self->mode) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 6:
			advE3Rom_setMode(self, 1);
			break;
	}
}

// 0x048 - SetMode.
void advE3Rom_setMode(AdvE3Rom* self, s32 mode)
{
	switch (mode) {
		case 0:
			self->mode = mode;
			break;
		case 1:
			self->mode = mode;
			fn_800CCC6C(lbl_1_data_244);
			break;
	}
	self->timer = lbl_1_rodata_0;
	lbl_1_bss_C = 0;
}

// 0x0C0 - stop the streamed title SE if playing.
void advE3Rom_stopSe(AdvE3Rom* self)
{
	if (self->se) {
		fn_8012CC20(self->se);
	}
}

// 0x0EC - Exec: the title/logo/select-mode state machine, a 9-way jumptable on
// self->mode (jumptable_1_data_260) advancing self->timer against clip
// endpoints and driving fades/ADX playback. PS2 semantic ref:
// ExecTitle__9ADV_TITLE / Exec__9ADVERTISE. PARKED: 0x81C (519 instrs); stub
// only. Kept out of line (defined before its callees setMode etc).
void advE3Rom_exec(AdvE3Rom* self)
{
	void* h;
	switch (self->mode) {
		case 0:
			self->se = (void*)(lbl_1_data_A4 + 0xD0);
			self->timer += lbl_1_rodata_4;
			if (self->timer >= (*(AdvClip**)(lbl_1_data_A4 + 0xD8))->f0C) {
				self->se   = (void*)(lbl_1_data_A4 + 0x68);
				self->mode = 2;
				fn_800CCC6C(lbl_1_data_250);
				self->timer = lbl_1_rodata_0;
			}
			break;
		case 1:
			self->se = (void*)lbl_1_data_A4;
			self->timer += lbl_1_rodata_4;
			if (fn_800158A0((u8*)lbl_8029BBD0 + lbl_802408F8 * 0x4C + 0x48, 0x1000) != 0
			    || self->timer >= (*(AdvClip**)(lbl_1_data_A4 + 0x8))->f0C) {
				self->se    = (void*)(lbl_1_data_A4 + 0x68);
				self->mode  = 2;
				self->timer = lbl_1_rodata_0;
			}
			break;
		case 2: {
			u8* a4   = lbl_1_data_A4;
			self->se = (void*)(a4 + 0x68);
			self->timer += lbl_1_rodata_4;
			if (self->timer >= (*(AdvClip**)(a4 + 0x70))->f0C) {
				fn_8001938C(lbl_8029C310);
				if (lbl_1_data_20 != 0) {
					fn_8001936C(lbl_8029C310, 0, 8);
					lbl_1_data_20 = 0;
				} else {
					fn_8001936C(lbl_8029C310, 0, 2);
					lbl_1_data_20 = 1;
				}
				fn_8001934C(lbl_8029C310, 0, 0);
				fn_800A96B0(lbl_80303EC8, 0x18, 2);
				self->mode = 8;
			} else if (fn_800158A0((u8*)lbl_8029BBD0 + lbl_802408F8 * 0x4C + 0x48, 0x1000) != 0) {
				h = lbl_8042C388;
				if (h) {
					fn_800B52E8(h, 0xE008, 0, 0);
				}
				self->mode  = 3;
				self->timer = (*(AdvClip**)(a4 + 0x70))->f0C;
			}
			break;
		}
		case 3:
			self->timer += lbl_1_rodata_4;
			if (self->timer >= (*(AdvClip**)(lbl_1_data_A4 + 0x70))->f14) {
				self->mode    = 4;
				self->timer   = (*(AdvClip**)(lbl_1_data_A4 + 0x70))->f14;
				self->counter = 0x708;
			}
			break;
		case 4:
			self->timer = (*(AdvClip**)(lbl_1_data_A4 + 0x70))->f14;
			self->counter -= 1;
			if (self->counter == 0) {
				self->mode  = 2;
				self->timer = lbl_1_rodata_0;
			} else if (fn_800158EC((u8*)lbl_8029BBD0 + lbl_802408F8 * 0x4C + 0x48, 4) != 0
			    || ((s16*)(lbl_8029BBD0 + 0x226))[lbl_802408F8 * 0x26] > 0x32) {
				h = lbl_8042C388;
				if (h) {
					fn_800B52E8(h, 0xE007, 0, 0);
				}
				self->mode    = 6;
				self->counter = 0x708;
			} else if (fn_800158A0((u8*)lbl_8029BBD0 + lbl_802408F8 * 0x4C + 0x48, 0x1000) != 0
			    || fn_800158A0((u8*)lbl_8029BBD0 + lbl_802408F8 * 0x4C + 0x48, 0x100) != 0) {
				h = lbl_8042C388;
				if (h) {
					fn_800B52E8(h, 0xE008, 0, 0);
				}
				self->mode = 5;
			} else if (fn_800158A0((u8*)lbl_8029BBD0 + lbl_802408F8 * 0x4C + 0x48, 0x200) != 0) {
				h = lbl_8042C388;
				if (h) {
					fn_800B52E8(h, 0xE009, 0, 0);
				}
				self->mode  = 2;
				self->timer = lbl_1_rodata_0;
			}
			break;
		case 5:
			self->timer += lbl_1_rodata_8;
			if (self->timer >= (*(AdvClip**)(lbl_1_data_A4 + 0x70))->f1C - lbl_1_rodata_8) {
				self->timer -= lbl_1_rodata_4;
				fn_800A96B0(lbl_80303EC8, 0x18, 0);
				fn_8001938C(lbl_8029C310);
				fn_8001936C(lbl_8029C310, 0, 2);
				fn_8001934C(lbl_8029C310, 0, 0);
				self->mode  = 8;
				lbl_1_bss_C = 1;
			}
			break;
		case 6:
			self->timer = (*(AdvClip**)(lbl_1_data_A4 + 0x70))->f1C;
			self->counter -= 1;
			if (self->counter == 0) {
				self->mode  = 2;
				self->timer = lbl_1_rodata_0;
			} else if (fn_800158EC((u8*)lbl_8029BBD0 + lbl_802408F8 * 0x4C + 0x48, 8) != 0
			    || ((s16*)(lbl_8029BBD0 + 0x226))[lbl_802408F8 * 0x26] < -0x32) {
				h = lbl_8042C388;
				if (h) {
					fn_800B52E8(h, 0xE007, 0, 0);
				}
				self->mode    = 4;
				self->counter = 0x708;
			} else if (fn_800158A0((u8*)lbl_8029BBD0 + lbl_802408F8 * 0x4C + 0x48, 0x1000) != 0
			    || fn_800158A0((u8*)lbl_8029BBD0 + lbl_802408F8 * 0x4C + 0x48, 0x100) != 0) {
				h = lbl_8042C388;
				if (h) {
					fn_800B52E8(h, 0xE008, 0, 0);
				}
				self->mode = 7;
			} else if (fn_800158A0((u8*)lbl_8029BBD0 + lbl_802408F8 * 0x4C + 0x48, 0x200) != 0) {
				h = lbl_8042C388;
				if (h) {
					fn_800B52E8(h, 0xE009, 0, 0);
				}
				self->mode  = 2;
				self->timer = lbl_1_rodata_0;
			}
			break;
		case 7:
			self->timer += lbl_1_rodata_4;
			if (self->timer >= (*(AdvClip**)(lbl_1_data_A4 + 0x70))->f24) {
				self->timer -= lbl_1_rodata_8;
				fn_800A96B0(lbl_80303EC8, 0x18, 0);
				fn_8001938C(lbl_8029C310);
				fn_8001936C(lbl_8029C310, 0, 8);
				fn_8001934C(lbl_8029C310, 0, 0);
				self->mode  = 8;
				lbl_1_bss_C = 1;
			}
			break;
		case 8:
			advE3Rom_setFlag(self);
			return;
	}
	if (self->se) {
		fn_8012CEF0(self->se, self->timer);
	}
}

// 0x908 - __ct.
AdvE3Rom* advE3Rom_ct(AdvE3Rom* self, s16 flag)
{
	if (self) {
		self->vtable = lbl_1_data_210;
		fn_800CC280();
		lbl_1_bss_8 = 0;
		fn_800A8620(self, 0);
		if (flag > 0) {
			advE3Rom_pause(self);
		}
	}
	return self;
}

// 0x988 - Create.
AdvE3Rom* advE3Rom_create(AdvE3Rom* self, void* parent)
{
	(void)parent;
	fn_800A8828(self);
	self->vtable = lbl_1_data_210;
	self->name   = lbl_1_data_1C;
	self->unk_1E = 0x8C;
	if (lbl_1_bss_C) {
		advE3Rom_setMode(self, 0);
	} else {
		advE3Rom_setMode(self, 1);
	}
	lbl_1_bss_8 = self;
	return self;
}

// 0xA18 - OnExec: instantiate once the manager is ready.
void advE3Rom_onExec(AdvE3Rom* self)
{
	AdvE3Rom* obj;
	if (lbl_1_bss_8 == 0) {
		obj = (AdvE3Rom*)advE3Rom_resume(0x8C);
		if (obj) {
			advE3Rom_create(obj, self);
		}
	}
}

// 0xA6C - Initialize: load adv_e3rom.one.
void advE3Rom_initialize(AdvE3Rom* self)
{
	(void)self;
	fn_8012CFA4(lbl_1_data_1F8);
}

// 0xA94 - Finalize: release adv_e3rom.one.
void advE3Rom_finalize(AdvE3Rom* self)
{
	(void)self;
	fn_8012D3A4(lbl_1_data_1F8);
}

// 0xABC / 0xAC0 - E3ROM-specific empty virtuals.
void advE3Rom_nullVirt5(void) { }
void advE3Rom_nullVirt6(void) { }

// 0xAC4..0xAD4 - shared base empty virtuals (present in every class vtable).
void advBase_nullVirt0(void) { }
void advBase_nullVirt1(void) { }
void advBase_nullVirt2(void) { }
void advBase_nullVirt3(void) { }
void advBase_nullVirt4(void) { }

// 0xAD8 - set the "started" flag bit.
void advE3Rom_setFlag(AdvE3Rom* self)
{
	self->flags |= 1;
}

// 0xAEC - register this task with the manager.
void advE3Rom_pause(void* obj)
{
	fn_800189A4(lbl_8042C148, obj);
}

// 0xB1C - look a task up by id.
void* advE3Rom_resume(s32 id)
{
	return fn_80018A34(lbl_8042C148, (void*)id);
}

// 0xB4C - find the min stream L-volume flag.
s32 advE3Rom_getVolL(AdvE3Rom* self)
{
	s32 out = 1;
	fn_80204144(self, (void*)advE3Rom_cbVolL, &out);
	return out;
}

// 0xB84 - cbVolL.
void* advE3Rom_cbVolL(void* a, void* b, int c, s32* out)
{
	f32 v1;
	(void)c;
	v1 = fn_802012B0(b);
	if (fn_802012B8(b) > v1) {
		*out = 0;
	}
	return a;
}

// 0xBF4 - accumulate the max stream R-volume.
f32 advE3Rom_getVolR(AdvE3Rom* self)
{
	f32 out = lbl_1_rodata_10;
	fn_80204144(self, (void*)advE3Rom_cbVolR, &out);
	return out;
}

// 0xC34 - cbVolR.
void* advE3Rom_cbVolR(void* a, void* b, int c, f32* out)
{
	f32 v;
	(void)c;
	v = fn_802012B8(b);
	if (*out < v) {
		*out = v;
	}
	return a;
}

// 0xC84 - Disp: per-frame draw/advance using self->timeline (0x38) clip
// endpoints, structurally like advanceTimer but with the full render path. PS2
// semantic ref: Disp__9ADVERTISE. PARKED: 0x358 (214 instrs); stub only.
void advE3Rom_disp(AdvE3Rom* self)
{
	void* h;
	self->timer += lbl_1_rodata_14;
	if (self->timer >= self->timeline->inner->limit) {
		s32 state;
		self->timer -= lbl_1_rodata_14;
		fn_8001938C(lbl_8029C310);
		state = fn_1_12A0(lbl_8042C180, 0x19);
		switch (state) {
			case 0:
			case 3:
				if (fn_1_12A0(lbl_8042C180, 0x14) == 0) {
					lbl_803EC340[1] = 0x1A;
				} else {
					lbl_803EC340[1] = 0x19;
				}
				fn_800A96B0(lbl_80303EC8, 0x31, 5);
				break;
			case 1:
				fn_8001934C(lbl_8029C310, 0, 0);
				fn_8001936C(lbl_8029C310, 0, 2);
				fn_800A96B0(lbl_80303EC8, 0x31, 2);
				break;
			case 2:
				fn_8001934C(lbl_8029C310, 0, 1);
				fn_8001936C(lbl_8029C310, 0, 8);
				fn_800A96B0(lbl_80303EC8, 0x31, 2);
				break;
			case 4:
				fn_8001934C(lbl_8029C310, 0, 2);
				fn_8001936C(lbl_8029C310, 0, 6);
				fn_800A96B0(lbl_80303EC8, 0x31, 2);
				break;
			case 5:
				fn_8001934C(lbl_8029C310, 0, 3);
				fn_8001936C(lbl_8029C310, 0, 0xA);
				fn_800A96B0(lbl_80303EC8, 0x31, 2);
				break;
		}
		{
			s32 nx = state + 1;
			if (nx >= 6) {
				nx = 0;
			}
			fn_800A96B0(lbl_80303EC8, 0x19, nx);
		}
		fn_800A96B0(lbl_80303EC8, 0x18, 2);
		fn_800A96B0(lbl_80303EC8, 0x27, 0);
		fn_800A96B0(lbl_80303EC8, 0x1E, 0);
		self->unk_48 = 0;
		self->unk_2C = 2;
		fn_800A96B0(lbl_80303EC8, 0x2A, -1);
	} else if (self->mode != 0) {
		if (self->counter > 0x78) {
			self->timer -= lbl_1_rodata_14;
			h = lbl_8042C388;
			if (h) {
				fn_800B52E8(h, 0xE008, 0, 0);
			}
			if (fn_80116B68(lbl_803E774C) == -2) {
				self->unk_48 = 1;
				self->unk_40 = 4;
			} else {
				self->unk_48 = 1;
				self->unk_40 = 3;
			}
			self->unk_2C = 3;
		}
	} else {
		if (fn_800A92E0(lbl_80303EC8, 0x1000, -1) != 0) {
			self->mode = 1;
		}
	}
	self->counter += 1;
}

// 0xFDC - advance the title timer, flag done at end of clip.
void advE3Rom_advanceTimer(AdvE3Rom* self)
{
	self->timer += lbl_1_rodata_14;
	if (self->timer >= self->timeline->inner->limit) {
		self->unk_2C = 6;
	}
}

#pragma dont_inline reset
#pragma force_active reset

} // extern "C"
