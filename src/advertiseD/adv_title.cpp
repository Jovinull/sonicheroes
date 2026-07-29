#include "types.h"

// advertiseD module (REL, module 1) - the ADV_TITLE attract-mode title task
// class. Second translation unit in the module, .text 0x0101C-0x03130. Its
// vtable is the run of function pointers at data 0x3E0; the class name pointer
// lives at data 0x294 and it loads "adv_title_us.one" (data 0x3C8).
//
// PS2 reference: the semantically-nearest class is ADV_TITLE in advertise.cpp
// plus the shared ADVERTISE base's Init/Loop/End/Disp/SearchTable/GetButton
// helpers. The GC build is more elaborate; names are inspired, not proven.
// Shares the ADVERTISE base object layout with ADV_E3ROM (adv_e3rom.cpp): this
// TU calls advE3Rom_advanceTimer/disp/pause/resume/setFlag on that base.
//
// Object is NonMatching while the TU is carved; do not flip to Matching here.

extern "C" {

// ---- shared ADVERTISE base object layout ------------------------------
struct Adv {
	/* 0x00 */ void* name;
	/* 0x04 */ u8 pad_04[0x18 - 0x04];
	/* 0x18 */ void* vtable;
	/* 0x1C */ u8 pad_1C[0x1E - 0x1C];
	/* 0x1E */ s16 unk_1E;
	/* 0x20 */ u8 pad_20[0x28 - 0x20];
	/* 0x28 */ s32 mode;
	/* 0x2C */ s32 state;
	/* 0x30 */ u8 pad_30[0x34 - 0x30];
	/* 0x34 */ f32 timer;
	/* 0x38 */ void* timeline;
	/* 0x3C */ u8 pad_3C[0x40 - 0x3C];
	/* 0x40 */ s32 unk_40;
	/* 0x44 */ s32 unk_44;
	/* 0x48 */ s32 unk_48;
	/* 0x4C */ u8 pad_4C[0x60 - 0x4C];
	/* 0x60 */ s32 unk_60;
	/* 0x64 */ s32 unk_64;
	/* 0x68 */ s32 unk_68;
	/* 0x6C */ u8 pad_6C[0x80 - 0x6C];
	/* 0x80 */ s32 unk_80;
	/* 0x84 */ void* unk_84;
	/* 0x88 */ s32 unk_88;
	/* 0x8C */ void* unk_8C;
	/* 0x90 */ s32 unk_90;
	/* 0x94 */ s32 unk_94;
	/* 0x98 */ s32 unk_98;
	/* 0x9C */ s32 unk_9C;
	/* 0xA0 */ s32 unk_A0;
	/* 0xA4 */ u8 pad_A4[0xA8 - 0xA4];
	/* 0xA8 */ s32 unk_A8;
	/* 0xAC */ void* unk_AC;
};

// on-stack text-layout descriptor passed to fn_1_150AC.
struct TextLayout {
	/* 0x00 */ u16* str;
	/* 0x04 */ void* a;
	/* 0x08 */ void* b;
	/* 0x0C */ void* c;
	/* 0x10 */ s32 flag;
	/* 0x14 */ f32 f14;
	/* 0x18 */ f32 f18;
	/* 0x1C */ f32 f1C;
	/* 0x20 */ f32 f20;
	/* 0x24 */ f32 f24;
	/* 0x28 */ u8 pad_28[0x48 - 0x28];
};

// ---- module data ------------------------------------------------------
extern void* lbl_1_data_3E0[]; // ADV_TITLE vtable
extern void* lbl_1_data_294;   // -> class name ("ADV_TITLE")
extern u8 lbl_1_data_2D8[];    // timeline table base
extern u8 lbl_1_data_3C8[];    // .one load descriptor
extern char lbl_1_data_414[];  // title BGM name
extern u8 lbl_1_data_500[];
extern u8 lbl_1_data_6A4[];
extern u8 lbl_1_data_8B0[];
extern u8 lbl_1_data_8B8[];
extern u8 lbl_1_data_8BC[];
extern u8 lbl_1_data_8C0[];
extern u8 lbl_1_data_8C4[];
extern u8 lbl_1_data_8CC[];
extern u8 lbl_1_bss_20[];
extern u8 lbl_1_bss_48[];
extern const f32 lbl_1_rodata_10;
extern u8 lbl_1_rodata_18[];
extern u8 lbl_1_rodata_54[];
extern u8 lbl_1_rodata_60[];
extern const f32 lbl_1_rodata_74;
extern const f32 lbl_1_rodata_78;
extern const f32 lbl_1_rodata_7C;
extern const f32 lbl_1_rodata_80;
extern const f32 lbl_1_rodata_84;
extern const f32 lbl_1_rodata_88;
extern const f32 lbl_1_rodata_8C;
extern const f32 lbl_1_rodata_98;
extern const f32 lbl_1_rodata_9C;
extern const f32 lbl_1_rodata_A0;
extern const f32 lbl_1_rodata_A4;
extern const f32 lbl_1_rodata_A8;
extern u8 lbl_80303EC8[];  // input/pad state object
extern void* lbl_8042C388; // optional debug/log sink pointer
extern u8 lbl_803E774C[];  // global sound/anim controller object

// ---- sibling-TU (adv_e3rom.cpp) shared base methods -------------------
void advE3Rom_advanceTimer(void*);
void advE3Rom_disp(void*);
void advE3Rom_pause(void*);
void* advE3Rom_resume(s32);
void advE3Rom_setFlag(void*);

// ---- external functions (DOL / other modules) -------------------------
void __ct__10DAnimClassFv(void*, int);
void fn_800A8620(void*, int);
void fn_800A8828(void*);
int fn_800A92E0(void*, int, int);
int fn_800A9398(void*, int);
void fn_800B52E8(void*, int, int, int);
int fn_80116AE4(void*);
int fn_80117274(void*, int);
int fn_801185E4(void*);
int fn_80118608(void*);
int fn_80118634(void*);
int fn_80118674(void*);
void* fn_80124860(void*, int);
void fn_8012C858(void*, void*, ...);
void fn_801A45A0(void*, void*);
void fn_800CC280(void);
void fn_800CCC6C(char*);
void fn_80116B60(void*, int);
int fn_80116B68(void*);
void fn_80116C50(void*);
void fn_80116D2C(void*);
void fn_80117080(void);
int fn_801248E8(void*, int);
int fn_801248F8(void*);
int fn_80124924(void*);
void fn_80125664(void*, int);
int fn_8012491C(void*);
int fn_80125530(void*);
void fn_8012EC18(void*, u16*, ...);
void fn_8012CA94(void*);
void fn_8012CB70(void*);
u16* fn_8012ECA8(int, int);

// ---- external functions in later TUs of this module -------------------
void fn_1_11750(int);
int fn_1_146C0(void*);
int fn_1_150AC(Adv*, void*);
void fn_1_152C0(void*);

// ---- forward decls (intra-TU) -----------------------------------------
Adv* fn_1_1154(Adv* self, void* parent);
void fn_1_16E8(Adv* self);
int fn_1_12E4(void* unused, u16* str);
void fn_1_18E0(Adv* self);
void fn_1_17EC(Adv* self);
void fn_1_1840(Adv* self);
void fn_1_27C4(Adv* self);
void fn_1_1F70(
    Adv* self, u16* str, void* arg3, void* arg4, void* arg5, int st0, int st1, int st2, int mode);

// =======================================================================
// 0x101C - set title timeline/timer for the two display modes.

#pragma dont_inline on

void fn_1_101C(Adv* self, int mode)
{
	switch (mode) {
		case 5:
			self->timer    = lbl_1_rodata_10;
			self->timeline = &lbl_1_data_2D8[0];
			break;
		case 6:
			self->timer    = lbl_1_rodata_10;
			self->timeline = &lbl_1_data_2D8[0x68];
			break;
	}
}

void fn_1_1074(Adv* self)
{
	switch (self->mode) {
		case 5:
			advE3Rom_advanceTimer(self);
			break;
		case 6:
			advE3Rom_disp(self);
			break;
		case 7: {
			s32 v        = self->unk_88 + 1;
			self->unk_88 = v;
			if (v > 0x78) {
				self->state = 2;
			}
			break;
		}
	}
}

Adv* fn_1_10E4(Adv* self, s16 flag)
{
	if (self) {
		self->vtable = lbl_1_data_3E0;
		fn_800CC280();
		fn_800A8620(self, 0);
		if (flag > 0) {
			advE3Rom_pause(self);
		}
	}
	return self;
}

Adv* fn_1_1154(Adv* self, void* parent)
{
	(void)parent;
	fn_800A8828(self);
	self->vtable = lbl_1_data_3E0;
	self->name   = lbl_1_data_294;
	self->unk_1E = 0x8C;
	__ct__10DAnimClassFv(self, 3);
	__ct__10DAnimClassFv(self, 4);
	__ct__10DAnimClassFv(self, 0xF);
	self->unk_40   = 3;
	self->unk_44   = 0xF;
	self->timeline = 0;
	self->mode     = 0;
	self->state    = 5;
	fn_1_11750(0);
	fn_800CCC6C(lbl_1_data_414);
	self->unk_84 = 0;
	self->unk_80 = 0;
	return self;
}

void fn_1_1210(Adv* self)
{
	Adv* obj = (Adv*)advE3Rom_resume(0x8C);
	if (obj) {
		fn_1_1154(obj, self);
	}
}

void fn_1_1250(Adv* self)
{
	(void)self;
	fn_8012CA94(lbl_1_data_3C8);
}

void fn_1_1278(Adv* self)
{
	(void)self;
	fn_8012CB70(lbl_1_data_3C8);
}

int fn_1_12A0(s8* self, int idx)
{
	if (idx < 0) {
		return -1;
	}
	if (idx < 0x2C) {
		return self[idx];
	}
	if (idx < 0x33) {
		s32* p = (s32*)(self + idx * 4);
		// Dead no-op (eliminated by the compiler): keeps `idx` live past the
		// multiply so MWCC materialises self+idx*4 in a base register and loads
		// through a -0x88 displacement (matches the target); without it, idx*4
		// and -0x88 fold into a single indexed load. Needed for byte match.
		if ((idx && idx) && idx) {
		}
		return p[-0x22];
	}
	return -1;
}

int fn_1_12E4(void* unused, u16* str)
{
	int n;
	int c;
	(void)unused;
	if (str == 0) {
		return 1;
	}
	n = 1;
	while ((c = *str) != 0) {
		if (c == 0xA) {
			n += 1;
		}
		str += 1;
	}
	return n;
}

void fn_1_131C(Adv* self, int arg)
{
	void* handle;
	int idx;
	idx    = self->unk_A0 + arg;
	idx    = idx - 1;
	handle = 0;
	if (idx < 0) {
		idx += 0x63;
	}
	if (idx >= 0x63) {
		idx -= 0x63;
	}
	if (self->unk_84) {
		handle = fn_80124860(self->unk_84, idx);
	}
	fn_8012C858(&lbl_1_data_500[((s32*)lbl_1_rodata_60)[arg] * 0xc], lbl_1_data_8B0, idx + 1);
	if (handle == 0) {
		if (fn_801248E8(self->unk_84, idx) == 3) {
			fn_801A45A0(((void**)lbl_1_bss_20)[arg],
			    ((void**)lbl_1_bss_48)[((s32*)lbl_1_rodata_54)[(arg != 1) ? 0 : 1]]);
		} else {
			fn_801A45A0(((void**)lbl_1_bss_20)[arg], *(void**)&lbl_1_bss_48[0x30]);
		}
		fn_8012C858(&lbl_1_data_500[(((s32*)lbl_1_rodata_60)[arg] + 1) * 0xc], lbl_1_data_8B8);
		fn_8012C858(&lbl_1_data_500[(((s32*)lbl_1_rodata_60)[arg] + 2) * 0xc], lbl_1_data_8B8);
		fn_8012C858(&lbl_1_data_500[(((s32*)lbl_1_rodata_60)[arg] + 3) * 0xc], lbl_1_data_8B8);
		fn_8012C858(&lbl_1_data_500[(((s32*)lbl_1_rodata_60)[arg] + 4) * 0xc], lbl_1_data_8BC);
		fn_8012C858(&lbl_1_data_500[(((s32*)lbl_1_rodata_60)[arg] + 5) * 0xc], lbl_1_data_8BC);
		fn_8012C858(&lbl_1_data_500[(((s32*)lbl_1_rodata_60)[arg] + 6) * 0xc], lbl_1_data_8C0);
	} else {
		u8* p18  = (u8*)handle + 0x18;
		u8* p624 = (u8*)handle + 0x624;
		u8* p3c  = (u8*)handle + 0x3c;
		int n    = fn_801185E4(p18);
		int k;
		if (arg != 1) {
			k = 0;
		} else if (p18[n + 6] != 0x64) {
			k = 1;
		} else {
			k = 2;
		}
		fn_801A45A0(((void**)lbl_1_bss_20)[arg],
		    ((void**)lbl_1_bss_48)[((s32*)&lbl_1_rodata_18[n * 0xc])[k]]);
		fn_8012C858(&lbl_1_data_500[(((s32*)lbl_1_rodata_60)[arg] + 1) * 0xc], lbl_1_data_8B0,
		    fn_80118674(p18));
		fn_8012C858(&lbl_1_data_500[(((s32*)lbl_1_rodata_60)[arg] + 2) * 0xc], lbl_1_data_8B0,
		    fn_80118634(p18));
		fn_8012C858(&lbl_1_data_500[(((s32*)lbl_1_rodata_60)[arg] + 3) * 0xc], lbl_1_data_8B0,
		    fn_80118608(p18));
		fn_8012C858(
		    &lbl_1_data_500[(((s32*)lbl_1_rodata_60)[arg] + 4) * 0xc], lbl_1_data_8C4, p18[0xa]);
		fn_8012C858(&lbl_1_data_500[(((s32*)lbl_1_rodata_60)[arg] + 5) * 0xc], lbl_1_data_8C4,
		    fn_80117274(p3c, 5));
		fn_8012C858(&lbl_1_data_500[(((s32*)lbl_1_rodata_60)[arg] + 6) * 0xc], lbl_1_data_8CC,
		    fn_80116AE4(p624));
	}
}

void fn_1_16E8(Adv* self)
{
	void* p = (void*)self->unk_88;
	if (p) {
		advE3Rom_setFlag(p);
		self->unk_88 = 0;
	}
}

void fn_1_1728(Adv* self)
{
	int found;
	int i;
	found = -1;
	i     = 0;
	do {
		if (fn_801248E8(self->unk_84, i) == 0) {
			found = i;
			break;
		}
		i++;
	} while (i != 0x63);
	if (found != -1) {
		fn_80116B60(lbl_803E774C, found);
		self->state = 0x11;
	} else {
		u16* msg = fn_8012ECA8(0, 0x31);
		fn_1_1F70(self, msg, 0, 0, 0, 5, 0, 0, 0);
	}
}

void fn_1_17EC(Adv* self)
{
	if (self->unk_80 == 0) {
		self->unk_48 = 0;
		self->state  = 2;
		fn_80116B60(lbl_803E774C, -1);
	} else {
		self->state = 0xC;
	}
}

void fn_1_1840(Adv* self)
{
	int i;
	int idx;
	if (fn_80124924(self->unk_84) != 0) {
		return;
	}
	for (i = 0; i != 5; i++) {
		idx = self->unk_A0 + i;
		idx = idx - 1;
		if (idx < 0) {
			idx += 0x63;
		}
		if (idx >= 0x63) {
			idx -= 0x63;
		}
		if (fn_801248E8(self->unk_84, idx) == 2) {
			fn_80125664(self->unk_84, idx);
			break;
		}
	}
}

void fn_1_18E0(Adv* self)
{
	u16 buf[0x200];
	u16* msg;
	u16* m50;
	u16* m51;
	u16* extra;
	if (self->unk_84 == 0) {
		return;
	}
	switch (fn_801248F8(self->unk_84)) {
		case 3: {
			u16* cmsg;
			u16* c50;
			u16* c51;
			c51  = fn_8012ECA8(0, 0x51);
			c50  = fn_8012ECA8(0, 0x50);
			cmsg = fn_8012ECA8(0, 0x24);
			fn_1_1F70(self, cmsg, c50, c51, 0, 6, 0xc, 0, 0);
			self->timer = lbl_1_rodata_74;
			break;
		}
		case 4: {
			u16* cmsg;
			u16* c50;
			u16* c51;
			c51  = fn_8012ECA8(0, 0x51);
			c50  = fn_8012ECA8(0, 0x50);
			cmsg = fn_8012ECA8(0, 0x26);
			fn_1_1F70(self, cmsg, c50, c51, 0, 6, 0xc, 0, 0);
			break;
		}
		case 2: {
			u16* cmsg;
			u16* c50;
			u16* c51;
			c51  = fn_8012ECA8(0, 0x51);
			c50  = fn_8012ECA8(0, 0x50);
			cmsg = fn_8012ECA8(0, 0x30);
			fn_1_1F70(self, cmsg, c50, c51, 0, 6, 0xc, 0, 0);
			break;
		}
		case 0:
		default:
			switch (fn_8012491C(self->unk_84)) {
				case 11: {
					u16* cmsg;
					u16* c50;
					u16* c51;
					c51  = fn_8012ECA8(0, 0x51);
					c50  = fn_8012ECA8(0, 0x50);
					cmsg = fn_8012ECA8(0, 0x40);
					fn_1_1F70(self, cmsg, c50, c51, 0, 6, 0xc, 0, 0);
					break;
				}
				case 6: {
					m51   = fn_8012ECA8(0, 0x51);
					m50   = fn_8012ECA8(0, 0x50);
					extra = fn_8012ECA8(0, 0x54);
					msg   = fn_8012ECA8(0, 0x15);
					fn_1_1F70(self, msg, extra, m50, m51, 0xf, 6, 0xc, 1);
					break;
				}
				case 12: {
					u16* cmsg;
					u16* c51;
					u16* cextra;
					u16* c50;
					c51    = fn_8012ECA8(0, 0x51);
					c50    = fn_8012ECA8(0, 0x50);
					cextra = fn_8012ECA8(0, 0x54);
					cmsg   = fn_8012ECA8(0, 0x19);
					fn_1_1F70(self, cmsg, cextra, c50, c51, 0xf, 6, 0xc, 1);
					break;
				}
				case 5: {
					m51 = fn_8012ECA8(0, 0x51);
					m50 = fn_8012ECA8(0, 0x50);
					msg = fn_8012ECA8(0, 0x21);
					fn_1_1F70(self, msg, m50, m51, 0, 6, 0xc, 0, 0);
					break;
				}
				case 3: {
					m51 = fn_8012ECA8(0, 0x51);
					m50 = fn_8012ECA8(0, 0x50);
					msg = fn_8012ECA8(0, 0x24);
					fn_1_1F70(self, msg, m50, m51, 0, 6, 0xc, 0, 0);
					self->timer = lbl_1_rodata_74;
					break;
				}
				case 4: {
					m51 = fn_8012ECA8(0, 0x51);
					m50 = fn_8012ECA8(0, 0x50);
					msg = fn_8012ECA8(0, 0x26);
					fn_1_1F70(self, msg, m50, m51, 0, 6, 0xc, 0, 1);
					break;
				}
				case 7: {
					m51 = fn_8012ECA8(0, 0x51);
					m50 = fn_8012ECA8(0, 0x50);
					msg = fn_8012ECA8(0, 0x28);
					fn_1_1F70(self, msg, m50, m51, 0, 6, 0xc, 0, 0);
					break;
				}
				case 8: {
					msg = fn_8012ECA8(0, 0x2b);
					fn_8012EC18(buf, msg, self->unk_A0 + 1);
					m51   = fn_8012ECA8(0, 0x51);
					m50   = fn_8012ECA8(0, 0x50);
					extra = fn_8012ECA8(0, 0x56);
					fn_1_1F70(self, buf, extra, m50, m51, 0x13, 6, 0xc, 0);
					break;
				}
				case 2: {
					msg = fn_8012ECA8(0, 0x51);
					m51 = fn_8012ECA8(0, 0x50);
					m50 = fn_8012ECA8(0, 0x30);
					fn_1_1F70(self, m50, m51, msg, 0, 6, 0xc, 0, 0);
					break;
				}
				default:
					break;
			}
			break;
	}
}

void fn_1_1E2C(Adv* self, u16* str)
{
	TextLayout layout;
	int n;
	fn_1_152C0(&layout);
	layout.str  = str;
	layout.a    = 0;
	layout.b    = 0;
	layout.c    = 0;
	layout.f14  = lbl_1_rodata_78;
	layout.f18  = lbl_1_rodata_7C;
	layout.f1C  = lbl_1_rodata_74;
	layout.f20  = lbl_1_rodata_80;
	layout.f24  = lbl_1_rodata_84;
	layout.flag = 1;
	n           = fn_1_12E4(self, str);
	if (n >= 6) {
		f32 tx     = lbl_1_rodata_88 * (f32)(n - 5);
		layout.f18 = layout.f18 - tx;
		f32 ty     = lbl_1_rodata_8C * (f32)(n - 5);
		layout.f24 = layout.f24 + ty;
	}
	fn_1_16E8(self);
	self->unk_88 = (s32)fn_1_150AC(self, &layout);
}

void fn_1_1F70(
    Adv* self, u16* str, void* arg3, void* arg4, void* arg5, int st0, int st1, int st2, int mode)
{
	TextLayout layout;
	int n;
	fn_1_152C0(&layout);
	layout.str  = str;
	layout.a    = arg3;
	layout.b    = arg4;
	layout.c    = arg5;
	layout.flag = 0;
	layout.f14  = lbl_1_rodata_78;
	layout.f18  = lbl_1_rodata_7C;
	layout.f1C  = lbl_1_rodata_74;
	layout.f20  = lbl_1_rodata_80;
	layout.f24  = lbl_1_rodata_84;
	if (arg3 != 0) {
		layout.f18 = layout.f18 - lbl_1_rodata_98;
	}
	if (layout.b != 0) {
		layout.f18 = layout.f18 - lbl_1_rodata_9C;
	}
	if (layout.c != 0) {
		layout.f18 = layout.f18 - lbl_1_rodata_9C;
	}
	n = fn_1_12E4(self, str);
	if (n >= 6) {
		f32 tx     = lbl_1_rodata_A0 * (f32)(n - 5);
		layout.f18 = layout.f18 - tx;
		f32 ty     = lbl_1_rodata_A4 * (f32)(n - 5);
		layout.f24 = layout.f24 + ty;
	}
	fn_1_16E8(self);
	self->unk_88 = (s32)fn_1_150AC(self, &layout);
	self->unk_90 = st0;
	self->unk_94 = st1;
	self->unk_98 = st2;
	if (mode == 0) {
		self->state = 0xD;
	} else {
		self->state = 0xE;
	}
}

void fn_1_2158(Adv* self)
{
	self->state = 5;
}

void fn_1_2164(Adv* self)
{
	switch (fn_801248F8(self->unk_84)) {
		case 0: {
			void* p = self->unk_8C;
			if (p) {
				switch (fn_1_146C0(p)) {
					case 1:
						fn_80116B60(lbl_803E774C, self->unk_A0);
						self->unk_9C = 0xA;
						self->state  = 8;
						break;
					case 2:
						self->state = 7;
						break;
				}
			} else {
				self->state = 7;
			}
			break;
		}
		case 3:
			self->state = 5;
			break;
		case 2:
		case 4:
		default:
			fn_1_18E0(self);
			break;
	}
}

void fn_1_2234(Adv* self)
{
	u16 buf[0x200];
	switch (fn_801248F8(self->unk_84)) {
		case 0: {
			void* p = self->unk_8C;
			if (p) {
				switch (fn_1_146C0(p)) {
					case 1:
						fn_80116B60(lbl_803E774C, self->unk_A0);
						self->state = 9;
						break;
					case 2: {
						u16* m0c;
						u16* m57;
						fn_80116B60(lbl_803E774C, self->unk_A0);
						m0c = fn_8012ECA8(0, 0xC);
						fn_8012EC18(buf, m0c, self->unk_A0 + 1);
						m57 = fn_8012ECA8(0, 0x57);
						fn_1_1F70(self, buf, fn_8012ECA8(0, 0x56), m57, 0, 0x13, 6, 0, 1);
						break;
					}
					case 3:
						self->state = 7;
						break;
				}
			} else {
				self->state = 7;
			}
			break;
		}
		case 3:
			self->state = 5;
			break;
		case 2:
		case 4:
		default:
			fn_1_18E0(self);
			break;
	}
}

void fn_1_2390(Adv* self)
{
	u16 buf[0x200];
	void* p = (void*)self->unk_88;
	if (p != 0 && fn_1_146C0(p) != 1) {
		return;
	}
	if (fn_80124924(self->unk_84) != 0) {
		return;
	}
	fn_1_16E8(self);
	switch (fn_8012491C(self->unk_84)) {
		case 0: {
			void* fmt = self->unk_AC;
			if (fmt) {
				fn_8012EC18(buf, (u16*)fmt, self->unk_A0 + 1);
				fn_1_1F70(self, buf, 0, 0, 0, 6, 0, 0, 1);
			} else {
				self->state = 2;
			}
			break;
		}
		case 3: {
			u16* msg = fn_8012ECA8(0, 0x4D);
			fn_1_1F70(self, msg, 0, 0, 0, 6, 0, 0, 0);
			self->timer = lbl_1_rodata_74;
			break;
		}
		case 9: {
			u16* msg = fn_8012ECA8(0, 0x4D);
			fn_1_1F70(self, msg, 0, 0, 0, 7, 0, 0, 0);
			break;
		}
		case 0xC:
		default:
			fn_1_18E0(self);
			break;
	}
}

void fn_1_24FC(Adv* self)
{
	u16 buf[0x200];
	void* p = (void*)self->unk_88;
	if (p != 0 && fn_1_146C0(p) != 1) {
		return;
	}
	if (fn_80124924(self->unk_84) != 0) {
		return;
	}
	fn_1_16E8(self);
	switch (fn_8012491C(self->unk_84)) {
		case 0: {
			void* fmt = self->unk_AC;
			if (fmt) {
				int st = (self->mode == 9) ? 2 : 6;
				fn_8012EC18(buf, (u16*)fmt, self->unk_A0 + 1);
				fn_1_1F70(self, buf, 0, 0, 0, st, 0, 0, 0);
			} else {
				self->state = 2;
			}
			break;
		}
		case 9:
			fn_1_1F70(self, fn_8012ECA8(0, 0x2E), fn_8012ECA8(0, 0x50), fn_8012ECA8(0, 0x51), 0,
			    self->mode, 0xC, 0, 0);
			break;
		case 3:
			if (self->unk_AC) {
				self->state = 5;
			} else {
				fn_1_18E0(self);
			}
			break;
		case 0xC:
		default:
			fn_1_18E0(self);
			break;
	}
}

void fn_1_2688(Adv* self)
{
	void* p = (void*)self->unk_88;
	if (p != 0 && fn_1_146C0(p) != 1) {
		return;
	}
	if (fn_80124924(self->unk_84) != 0) {
		return;
	}
	fn_1_16E8(self);
	switch (fn_8012491C(self->unk_84)) {
		case 0: {
			u16* msg = fn_8012ECA8(0, 0x1D);
			fn_1_1F70(self, msg, 0, 0, 0, 6, 0, 0, 0);
			break;
		}
		case 3:
			fn_1_18E0(self);
			/* fallthrough */
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 0xA:
		case 0xC:
		default:
			fn_1_18E0(self);
			break;
	}
}

void fn_1_2760(Adv* self)
{
	switch (fn_801248F8(self->unk_84)) {
		case 0:
			fn_1_27C4(self);
			break;
		case 2:
		case 3:
		case 4:
		default:
			fn_1_18E0(self);
			break;
	}
}

void fn_1_27C4(Adv* self)
{
	void* p = (void*)self->unk_88;
	if (p) {
		switch (fn_1_146C0(p)) {
			case 1:
				if (self->unk_90) {
					self->state = self->unk_90;
					fn_1_16E8(self);
				}
				break;
			case 2:
				if (self->unk_94) {
					self->state = self->unk_94;
					fn_1_16E8(self);
				}
				break;
			case 3:
				if (self->unk_98) {
					self->state = self->unk_98;
					fn_1_16E8(self);
				}
				break;
		}
	} else {
		self->state = self->unk_94;
		fn_1_16E8(self);
	}
}

void fn_1_2884(Adv* self)
{
	void* p = (void*)self->unk_88;
	if (p) {
		switch (fn_1_146C0(p)) {
			case 1:
				fn_80116B60(lbl_803E774C, -1);
				self->state = 5;
				fn_1_16E8(self);
				break;
			case 2:
				fn_80116B60(lbl_803E774C, -2);
				self->state = 2;
				fn_1_16E8(self);
				break;
		}
	} else {
		fn_80116B60(lbl_803E774C, -1);
		self->state = 5;
		fn_1_16E8(self);
	}
}

void fn_1_293C(Adv* self)
{
	void* p = (void*)self->unk_88;
	if (p != 0 && fn_1_146C0(p) != 1) {
		return;
	}
	if (fn_80124924(self->unk_84) != 0) {
		return;
	}
	fn_1_16E8(self);
	switch (fn_8012491C(self->unk_84)) {
		case 0: {
			u16* msg = fn_8012ECA8(0, 9);
			fn_1_1F70(self, msg, 0, 0, 0, self->unk_9C, 0, 0, 1);
			break;
		}
		case 7:
			fn_1_1F70(self, fn_8012ECA8(0, 0x28), fn_8012ECA8(0, 0x50), fn_8012ECA8(0, 0x51), 0, 8,
			    0xC, 0, 1);
			break;
		case 3:
		case 0xA:
			fn_1_1F70(self, fn_8012ECA8(0, 0x3F), fn_8012ECA8(0, 0x50), fn_8012ECA8(0, 0x51), 0, 6,
			    0xC, 0, 0);
			break;
		case 0xC:
		default:
			fn_1_18E0(self);
			break;
	}
}

void fn_1_2AC8(Adv* self)
{
	u16 buf[0x200];
	fn_1_1840(self);
	switch (fn_801248F8(self->unk_84)) {
		case 0:
			self->timer = self->timer + lbl_1_rodata_A8;
			{
				f32* q = *(f32**)(&lbl_1_data_6A4[8]);
				if (q[3] < self->timer) {
					self->timer = q[1];
				}
			}
			switch (self->unk_A8) {
				case 0: {
					f32* q = *(f32**)(&lbl_1_data_6A4[8]);
					if (q[1] <= self->timer) {
						s32 old = self->unk_A0;
						if (fn_800A92E0(lbl_80303EC8, 1, -1)) {
							self->unk_A0 = self->unk_A0 - 1;
						} else if (fn_800A92E0(lbl_80303EC8, 2, -1)) {
							self->unk_A0 = self->unk_A0 + 1;
						}
						if (self->unk_A0 < 0) {
							self->unk_A0 = self->unk_A0 + 0x63;
							if (lbl_8042C388) {
								fn_800B52E8(lbl_8042C388, 0xE007, 0, 0);
							}
							self->state  = 1;
							self->unk_60 = 7;
							self->unk_64 = 4;
							self->unk_68 = 5;
						} else if (self->unk_A0 >= 0x63) {
							self->unk_A0 = self->unk_A0 - 0x63;
							if (lbl_8042C388) {
								fn_800B52E8(lbl_8042C388, 0xE007, 0, 0);
							}
							self->state  = 1;
							self->unk_60 = 7;
							self->unk_64 = 2;
							self->unk_68 = 3;
						} else if (self->unk_A0 < old) {
							if (lbl_8042C388) {
								fn_800B52E8(lbl_8042C388, 0xE007, 0, 0);
							}
							self->state  = 1;
							self->unk_60 = 7;
							self->unk_64 = 4;
							self->unk_68 = 5;
						} else if (old < self->unk_A0) {
							if (lbl_8042C388) {
								fn_800B52E8(lbl_8042C388, 0xE007, 0, 0);
							}
							self->state  = 1;
							self->unk_60 = 7;
							self->unk_64 = 2;
							self->unk_68 = 3;
						}
						self->unk_A8 = fn_800A9398(lbl_80303EC8, -1);
					}
					break;
				}
				case 1:
					if (lbl_8042C388) {
						fn_800B52E8(lbl_8042C388, 0xE009, 0, 0);
					}
					fn_1_17EC(self);
					break;
				case 2:
					switch (fn_801248E8(self->unk_84, self->unk_A0)) {
						case 0:
							if (lbl_8042C388) {
								fn_800B52E8(lbl_8042C388, 0xE008, 0, 0);
							}
							self->state = 0x11;
							break;
						case 1:
							if (lbl_8042C388) {
								fn_800B52E8(lbl_8042C388, 0xE008, 0, 0);
							}
							self->state = 0x10;
							break;
						case 3: {
							u16* m2b;
							u16* m57;
							u16* m56;
							if (lbl_8042C388) {
								fn_800B52E8(lbl_8042C388, 0xE008, 0, 0);
							}
							fn_80116B60(lbl_803E774C, self->unk_A0);
							m2b = fn_8012ECA8(0, 0x2B);
							fn_8012EC18(buf, m2b, self->unk_A0 + 1);
							m57 = fn_8012ECA8(0, 0x57);
							m56 = fn_8012ECA8(0, 0x56);
							fn_1_1F70(self, buf, m56, m57, 0, 0x13, 6, 0, 1);
							break;
						}
						case 2:
						default:
							self->unk_A8 = 0;
							break;
					}
					break;
				case 3:
					self->unk_A8 = 0;
					break;
			}
			break;
		case 3:
			self->timer = lbl_1_rodata_74;
			self->state = 5;
			break;
		case 2:
		case 4:
		default:
			self->timer = lbl_1_rodata_74;
			fn_1_18E0(self);
			break;
	}
}

void fn_1_2F40(Adv* self)
{
	if (fn_80124924(self->unk_84) != 0) {
		return;
	}
	switch (fn_801248F8(self->unk_84)) {
		case 1:
		case 5:
		default:
			fn_1_18E0(self);
			break;
		case 0:
			switch (fn_8012491C(self->unk_84)) {
				case 0:
					if (fn_80125530(self->unk_84) > 0) {
						self->state = 7;
					} else {
						u16* m52;
						u16* m53;
						u16* m3;
						fn_80116B60(lbl_803E774C, 0);
						self->unk_9C = 0xA;
						m53          = fn_8012ECA8(0, 0x53);
						m52          = fn_8012ECA8(0, 0x52);
						m3           = fn_8012ECA8(0, 3);
						fn_1_1F70(self, m3, m52, m53, 0, 8, 0xC, 0, 1);
						self->timer = lbl_1_rodata_74;
					}
					break;
				case 6:
				case 0xC:
					fn_1_18E0(self);
					break;
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 7:
				case 8:
				case 9:
				case 0xA:
					fn_1_18E0(self);
					break;
			}
			break;
	}
}

void fn_1_30A8(Adv* self)
{
	if (self->unk_80 == 0) {
		if (fn_80116B68(lbl_803E774C) == -1) {
			fn_80116D2C(lbl_803E774C);
			fn_80117080();
			fn_80116C50(lbl_803E774C);
		}
		fn_80116B60(lbl_803E774C, -1);
		self->state = 6;
	} else {
		self->state = 6;
	}
}

#pragma dont_inline reset

} // extern "C"
