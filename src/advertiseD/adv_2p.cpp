#include "types.h"

// ADV_2P - the advertise/attract-mode 2-player character-select object
// (REL module 1). Two classes: ADV_2P_Tag (a per-slot tag widget) and ADV_2P
// (the menu controller). Semantic reference is the PS2 debug build's ADV_2P /
// ADV_2P_Tag classes (grep ADV_2P ps2_funcs_sz.txt).
//
// Struct offsets are GameCube ground truth; the PS2 reference only supplies
// logic and names. Vtables live at lbl_1_data_79B0 (ADV_2P_Tag) and
// lbl_1_data_79DC (ADV_2P). The module symbol table is unmangled, so every
// function links extern "C" and objdiff pairs by the dtk fn_1_<addr> name.
//
// Unmatched large functions are stubbed and kept at the END of the TU so MWCC
// cannot auto-inline them into their (earlier-defined) callers.

struct TObject {
};
extern "C" void fn_1_120C4(void* self, s32 value);
struct ADV_MENU {
	s32 values[32];
	s32 count;
	s32 index;
	s32 wrap;
	inline void Add(s32 value) { fn_1_120C4(this, value); }
};
struct ADV_2P {
	u8 pad_00[0x84];
	ADV_MENU menus[3];
	u8 pad_228[0x234 - 0x228];
	s32 selected[2];
	ADV_MENU playerMenus[2];
	s32 tags[2];
	u8 pad_35c[0x368 - 0x35c];
	s32 players[2];
	ADV_2P(TObject* parent);
};

#define w(o)  (*(s32*)((u8*)t + (o)))
#define uw(o) (*(u32*)((u8*)t + (o)))
#define fl(o) (*(f32*)((u8*)t + (o)))
#define pp(o) (*(void**)((u8*)t + (o)))

// --- data/rodata living in the module's auto sections ---
extern "C" u8 lbl_1_data_79B0[]; // ADV_2P_Tag vtable
extern "C" u8 lbl_1_data_79DC[]; // ADV_2P vtable
extern "C" u8 lbl_1_data_6408[];
extern "C" u8 lbl_1_data_75FC[];
extern "C" u8 lbl_1_data_7820[];
extern "C" u8 lbl_1_data_7838[];
extern "C" u8 lbl_1_data_7960[];
extern "C" u8 lbl_1_data_79A8[];
extern "C" u8 lbl_1_data_7A7C[];
extern "C" s32 lbl_1_data_11A4[];

extern "C" s32 lbl_1_rodata_14E8[];
extern "C" s32 lbl_1_rodata_153C[];
extern "C" s32 lbl_1_rodata_1558[];
extern "C" s32 lbl_1_rodata_1574[];
extern "C" s32 lbl_1_rodata_1590[];
extern "C" u8 lbl_1_rodata_15A0[];
extern "C" u8 lbl_1_rodata_15F4[];
extern "C" u8 lbl_1_rodata_162C[];
extern "C" u8 lbl_1_rodata_1664[];
extern "C" u8 lbl_1_rodata_169C[];
extern "C" u8 lbl_1_rodata_17EC[];
extern "C" u8 lbl_1_rodata_1824[];
extern "C" u8 lbl_1_rodata_1904[];
extern "C" u8 lbl_1_rodata_193C[];
extern "C" u32 lbl_1_rodata_1944[];
extern "C" s32 lbl_1_rodata_19A8[];
extern "C" s32 lbl_1_rodata_19B4[];
extern "C" s32 lbl_1_rodata_19C0[];
extern "C" const f32 lbl_1_rodata_19A4;

extern "C" u32 lbl_1_bss_738[];
extern "C" u32 lbl_1_bss_770[];
extern "C" u32 lbl_1_bss_7A8[];
extern "C" s32 lbl_1_bss_7BC;

extern "C" u32 lbl_802408F8;
extern "C" u8 lbl_8029BBD0[];
extern "C" u8 lbl_8029C310[];
extern "C" u8 lbl_80303EC8[];
extern "C" u8 lbl_803E774C[];
extern "C" void* lbl_8042C388;

// --- functions in other TUs of this module (or base class) ---
extern "C" void advE3Rom_setFlag(void* t);
extern "C" void advE3Rom_pause(void* t);
extern "C" void* advE3Rom_resume(u32 size);
extern "C" void fn_1_EC2C(void* t);
extern "C" void fn_1_EC70(void* t);
extern "C" void fn_1_EC74(void* t);
extern "C" void fn_1_ECC0(void* t, s32 v);
extern "C" void fn_1_ECD0(void* t);
extern "C" void fn_1_55A4(void* t, s32 v);
extern "C" void fn_1_5994(void* a, void* b);
extern "C" void fn_1_63A8(void* a, void* b);
extern "C" void fn_1_64E0(void);
extern "C" void fn_1_65BC(void);
extern "C" void fn_1_6ABC(void* a);
extern "C" void fn_1_7B24(void* a, void* b);
extern "C" s32 fn_1_86B0(void* a, s32 b);
extern "C" void fn_1_119E0(void* a, s32 v);
extern "C" void fn_1_11750(s32 v);
extern "C" s32 fn_1_11AA8(void* a, s32 b, s32 c, s32 d);
extern "C" s32 fn_1_11E48(void* a, s32 b);
extern "C" s32 fn_1_11F00(void* a);
extern "C" void fn_1_120B4(void* a);
extern "C" void fn_1_120C4(void* a, s32 i);
extern "C" void fn_1_120E0(void);
extern "C" void fn_1_12124(void);
extern "C" void* fn_1_10F40(void* a, void* b);

extern "C" void __dt__7TObjectFv(void* t, s32 f);
extern "C" void fn_8001867C(void* a);
extern "C" void* __ct__7TObjectFP7TObject(void* obj, void* parent);
extern "C" void fn_80018D98(void* a);
extern "C" void fn_800191F8(void* a, s32 b, s32 c);
extern "C" void fn_8001934C(void* a, s32 b, s32 c);
extern "C" void fn_8001936C(void* a, s32 b, s32 c);
extern "C" void fn_8001938C(void* a);
extern "C" void fn_8006642C(void* a, s32 b, s32 c);
extern "C" void __ct__10DAnimClassFv(void* t, s32 v);
extern "C" void fn_800A80E0(void* t, void* tbl, s32 idx);
extern "C" void fn_800A8120(void* t);
extern "C" void fn_800A8174(void* t, s32 v);
extern "C" void fn_800A8264(void* t);
extern "C" void fn_800A8620(void* t, s32 v);
extern "C" void fn_800A8828(void* t, void* parent);
extern "C" s32 fn_800A8C0C(void* t);
extern "C" void fn_800A8C50(void* t, s32 v);
extern "C" void fn_800A8C7C(void* t);
extern "C" void fn_800A8C9C(void* t, void* a);
extern "C" s32 fn_800A9398(void* t, s32 v);
extern "C" void fn_800A96B0(void* t, s32 a, s32 b);
extern "C" void fn_800B52E8(void* a, s32 b, s32 c, s32 d);
extern "C" void* fn_80116D2C(void* a);
extern "C" void fn_8012CA94(void* a);
extern "C" void fn_8012CB70(void* a);
extern "C" void fn_8012CC20(void* a);
extern "C" void fn_8012CEF0(void* a, f32 f);
extern "C" void fn_801A45A0(void* a, s32 b);
extern "C" void* fn_801A4BBC(void* a, void* b);
extern "C" void __destroy_arr(void* a, void* dtor, s32 size, s32 n);
extern "C" void __construct_array(void* a, void* ctor, void* dtor, s32 size, s32 n);
extern "C" u32 fn_801D5D54(void);

// forward decls for intra-TU callees (defined later => real out-of-line bl)
extern "C" void* fn_1_EEE4(void* t, void* parent, s32 arg);
extern "C" void __ct__6ADV_2PFP7TObject(void* self, TObject* parent);
extern "C" void fn_1_EF8C(void* t);
extern "C" void fn_1_F06C(void* t, s32 i);
extern "C" void fn_1_F118(void* t, s32 i);
extern "C" void fn_1_F358(void* t, s32 i);
extern "C" void fn_1_F38C(void* t, s32 i);
extern "C" void fn_1_F454(void* t);
extern "C" s32 fn_1_F610(void* t, s32 mode);
extern "C" void fn_1_F758(void* t);
extern "C" void fn_1_F81C(void* t);
extern "C" void fn_1_FAA8(void* t);
extern "C" void fn_1_FFD8(void* t, s32 v);

struct S298 {
	u8 _00[0x234];
	s32 f234; // 0x234
	s32 f238; // 0x238
	u8 _23c[0x2c8 - 0x23c];
	u8 sub2c8[0x8c]; // 0x2c8
};

struct SPad4C {
	u8 _00[0x48];
	u32 f48; // 0x48
};

// ---------------------------------------------------------------------------
// Stubs (unmatched; kept last so they never auto-inline into callers)
// ---------------------------------------------------------------------------

// refresh selectable flags from the save-file completion state
struct EF8CView {
	u8 _pad370[0x370];
	s32 flags[7];
};
struct F38CNode {
	s32 a;       // +0x00
	u8 sub[0xc]; // +0x04
	s32 c;       // +0x10
};

struct SMenu {
	u8 _00[0x80];
	u8 sub80[4]; // 0x80
};
struct S1944 {
	u32 a;
	u32 b;
	u32 c;
};

// ADV_2P selection input handler
struct SF8 {
	u8 _00[4];
	f32 f4; // 0x04
};

// Forward declarations for the reverse textual definition order.
extern "C" void fn_1_EDB8(void* t);
extern "C" void fn_1_EDE4(void* t);
extern "C" void* fn_1_EE7C(void* t, short f);
extern "C" void* fn_1_EEE4(void* t, void* parent, s32 arg);
extern "C" void fn_1_F06C(void* t, s32 i);
extern "C" void fn_1_F298(void* t);
extern "C" void fn_1_FF70(void* t);
extern "C" void fn_1_10054(void* t);
extern "C" void* fn_1_10104(void* t, short f);
extern "C" void fn_1_103F0(void* t);
extern "C" void fn_1_10634(void* t);
extern "C" void fn_1_10698(void* t);
extern "C" void fn_1_106A4(void* t);
extern "C" void fn_1_107F8(void* t);
extern "C" void fn_1_EF8C(void* t);
extern "C" void fn_1_F118(void* t, s32 i);
extern "C" void fn_1_F38C(void* t, s32 i);
extern "C" void fn_1_F358(void* t, s32 i);
extern "C" void fn_1_F454(void* t);
extern "C" void fn_1_F758(void* t);
extern "C" s32 fn_1_F610(void* t, s32 mode);
extern "C" void fn_1_F81C(void* t);

extern "C" void fn_1_FFD8(void* t, s32 v);
extern "C" void fn_1_FAA8(void* t);
extern "C" void fn_1_FCB0(void* t, s32 mode);
extern "C" void fn_1_10430(void);
extern "C" void fn_1_104E8(void);
extern "C" void fn_1_106E8(void* t);

// ADV_2P start check
extern "C" void fn_1_107F8(void* t)
{
	SPad4C* p = (SPad4C*)lbl_8029BBD0;
	if ((p[lbl_802408F8].f48 & 0x200) == 0 && fn_801D5D54() != 1)
		w(0x2c) = 2;
	else
		w(0x2c) = 1;
}

extern "C" void fn_1_106E8(void* t)
{
	s32 r = fn_1_11E48((u8*)t + 0x80, -1);
	if (r != -1 && w(0x10c) != r) {
		w(0x10c)  = r;
		SF8* base = (SF8*)*(void**)(lbl_1_data_7A7C + 0x8);
		fl(0x34)  = base[lbl_1_rodata_19C0[r]].f4;
	} else {
		switch (fn_800A9398(lbl_80303EC8, -1)) {
			case 3:
				fn_800A8174(t, lbl_1_rodata_19A8[w(0x10c)]);
				break;
			case 2:
				if (w(0x10c) != 2) {
					w(0x2c) = lbl_1_rodata_19B4[w(0x10c)];
				} else {
					fn_800A8C7C(lbl_80303EC8);
					lbl_1_bss_7BC = 1;
					w(0x2c)       = 2;
				}
				break;
			case 0:
			case 1:
				break;
		}
	}
}

extern "C" void fn_1_106A4(void* t)
{
	if (fn_800A8C0C(lbl_80303EC8))
		w(0x2c) = 2;
}

extern "C" void fn_1_10698(void* t)
{
	w(0x2c) = 2;
}

// ADV_2P timeout tick
extern "C" void fn_1_10634(void* t)
{
	if (w(0x110) > 0x168) {
		fn_800A8C7C(lbl_80303EC8);
		lbl_1_bss_7BC = 0;
		w(0x2c)       = 2;
	} else {
		w(0x110)++;
	}
}

extern "C" void fn_1_104E8(void)
{
	fn_1_11750(3);
	fn_8012CB70(lbl_1_data_7820);
	fn_1_65BC();
	if (*(u32*)((u8*)lbl_1_data_7820 + 0xc) != 0) {
		u32* aa;
		void** bb;
		u32* cc;
		s32 i;
		s32 j;
		for (i = 0; i != 7; i++) {
			j  = 0;
			aa = ((u32(*)[2])lbl_1_data_7960)[i];
			bb = ((void*(*)[2])lbl_1_bss_738)[i];
			cc = ((u32(*)[2])lbl_1_bss_770)[i];
			for (; j != 2; j++) {
				bb[j] = fn_801A4BBC(*(void**)((u8*)lbl_1_data_7820 + 0xc), (void*)aa[j]);
				if (bb[j])
					cc[j] = *(u32*)bb[j];
			}
		}
		for (i = 0; i != 2; i++) {
			void* h = fn_801A4BBC(
			    *(void**)((u8*)lbl_1_data_7820 + 0xc), (void*)((u32*)lbl_1_data_79A8)[i]);
			if (h)
				((u32*)lbl_1_bss_7A8)[i] = *(u32*)h;
		}
	}
	S1944 s = *(S1944*)lbl_1_rodata_1944;
	fn_800A8C9C(lbl_80303EC8, &s);
}

// reset all player links / audio for the menu
extern "C" void fn_1_10430(void)
{
	u32* z   = lbl_1_bss_7A8;
	s32 zero = 0;
	s32 n;
	for (n = 0; n != 2; n++) {
		*z = zero;
		z++;
	}
	n = zero;
	for (; n != 7; n++) {
		for (s32 j = 0; j != 2; j++) {
			u32& aa = ((u32(*)[2])lbl_1_bss_770)[n][j];
			u32& bb = ((u32(*)[2])lbl_1_bss_738)[n][j];
			if (aa)
				fn_801A45A0((void*)bb, aa);
			bb = 0;
			aa = 0;
		}
	}
	fn_1_64E0();
	fn_8012CA94(lbl_1_data_7820);
}

// new ADV_2P_Tag
extern "C" void fn_1_103F0(void* t)
{
	void* p = advE3Rom_resume(0x3a0);
	if (p)
		__ct__6ADV_2PFP7TObject(p, (TObject*)t);
}

#pragma opt_common_subs off
#pragma opt_strength_reduction off
ADV_2P::ADV_2P(TObject* parent)
{
	void* t = this;
	fn_800A8828(t, parent);
	pp(0x18) = lbl_1_data_79DC;
	__construct_array((u8*)t + 0x84, (void*)fn_1_12124, (void*)fn_1_120E0, 0x8c, 3);
	__construct_array((u8*)t + 0x23c, (void*)fn_1_12124, (void*)fn_1_120E0, 0x8c, 2);
	uw(0x0)                = *(u32*)lbl_1_data_6408;
	*(u16*)((u8*)t + 0x1e) = 0x3a0;
	w(0x48)                = 0;
	w(0x40)                = 0xf;
	w(0x44)                = 4;
	pp(0x38)               = lbl_1_data_75FC;
	w(0x80)                = 0;
	w(0x28)                = 1;
	w(0x2c)                = 1;
	fl(0x34)               = lbl_1_rodata_19A4;
	w(0x60)                = 5;
	w(0x64)                = 0;
	w(0x68)                = 0;
	fn_1_120C4((u8*)t + 0x84, 0);
	fn_1_120C4((u8*)t + 0x84, 1);
	fn_1_120C4((u8*)t + 0x84, 2);
	fn_1_120C4((u8*)t + 0x84, 3);
	fn_1_120C4((u8*)t + 0x84, 4);
	fn_1_120C4((u8*)t + 0x84, 5);
	fn_1_120C4((u8*)t + 0x84, 6);
	struct Offset {
		s32 value;
	};
	Offset off8c;
	Offset off4;
	s32 i;
	s32 k;
	for (i = 0; i != 4; i++)
		menus[2].Add(i);
	k           = 0;
	off8c.value = 0;
	off4        = off8c;
	do {
		fn_1_120C4((u8*)t + off8c.value + 0x23c, 0);
		fn_1_120C4((u8*)t + off8c.value + 0x23c, 1);
		fn_1_120C4((u8*)t + off8c.value + 0x23c, 2);
		fn_1_120C4((u8*)t + off8c.value + 0x23c, 3);
		*(s32*)((u8*)t + off4.value + 0x234) = 0;
		*(s32*)((u8*)t + off4.value + 0x354) = 0;
		*(s32*)((u8*)t + off4.value + 0x368) = 0;
		off8c.value += 0x8c;
		off4.value += 4;
		k++;
	} while (k != 2);
	pp(0x360) = lbl_1_data_75FC + 0x68;
	pp(0x364) = lbl_1_data_75FC + 0x1a0;
	fl(0x38c) = lbl_1_rodata_19A4;
	w(0x228)  = 0;
	void* p   = advE3Rom_resume(0x30);
	if (p)
		p = fn_1_10F40(p, t);
	pp(0x39c) = p;
	fn_1_EF8C(t);
	__ct__10DAnimClassFv(t, 4);
}
#pragma opt_strength_reduction reset
#pragma opt_common_subs reset

// ADV_2P::ADV_2P (array-element ctor)
extern "C" void* fn_1_10104(void* t, short f)
{
	if (t) {
		pp(0x18) = lbl_1_data_79DC;
		__destroy_arr((u8*)t + 0x23c, (void*)fn_1_120E0, 0x8c, 2);
		__destroy_arr((u8*)t + 0x84, (void*)fn_1_120E0, 0x8c, 3);
		fn_800A8620(t, 0);
		if (f > 0)
			advE3Rom_pause(t);
	}
	return t;
}

// ADV_2P::Exec dispatch by mode
extern "C" void fn_1_10054(void* t)
{
	switch (w(0x28)) {
		case 5:
			fn_1_FAA8(t);
			break;
		case 6:
			fn_1_F81C(t);
			break;
		case 8:
			fn_1_F758(t);
			break;
	}
	if (pp(0x360))
		fn_8012CEF0(pp(0x360), fl(0x34));
	if (pp(0x364)) {
		fn_8012CEF0(pp(0x364), fl(0x38c));
		if (fl(0x38c) < *(f32*)((u8*)*(void**)(lbl_1_data_75FC + 0x1a8) + 0xc))
			fl(0x38c) = *(f32*)((u8*)*(void**)(lbl_1_data_75FC + 0x1a8) + 0xc);
	}
}

// defined after fn_1_F81C so its two calls stay real bl
extern "C" void fn_1_FFD8(void* t, s32 v)
{
	void* p = ((void**)((u8*)t + 0x354))[v];
	if (p) {
		void* n = *(void**)((u8*)p + 0x14);
		while (n) {
			if (fn_1_86B0(n, lbl_1_data_11A4[0]))
				fn_1_55A4(n, 1);
			n = *(void**)((u8*)n + 0xc);
		}
	}
}

// ADV_2P::Off - stop sounds
extern "C" void fn_1_FF70(void* t)
{
	fn_800A8264(t);
	if (((s32*)((u8*)t + 0x370))[w(0x228)] == 0) {
		if (pp(0x364))
			fn_8012CC20(pp(0x364));
	} else {
		if (pp(0x360))
			fn_8012CC20(pp(0x360));
	}
}

#pragma opt_common_subs off
extern "C" void fn_1_FCB0(void* t, s32 mode)
{
	w(0x354) = 0;
	w(0x358) = 0;
	w(0x368) = 0;
	w(0x36c) = 0;
	fn_800A8C50(lbl_80303EC8, 0);
	switch (mode) {
		case 5:
			if (pp(0x39c) == 0) {
				void* p = advE3Rom_resume(0x30);
				if (p)
					p = fn_1_10F40(p, t);
				pp(0x39c) = p;
			}
			fn_1_119E0((u8*)t + 0x84, w(0x228));
			fn_800A80E0(t, lbl_1_rodata_15A0 + w(0x228) * 0xc, 0);
			fl(0x38c) = lbl_1_rodata_19A4;
			break;
		case 7:
			w(0x2c) = 1;
			w(0x60) = 6;
			fn_1_7B24((u8*)t + 0x64, lbl_1_rodata_162C + w(0x228) * 8);
			break;
		case 6:
			if (pp(0x39c)) {
				advE3Rom_setFlag(pp(0x39c));
				pp(0x39c) = 0;
			}
			w(0x35c) = 0;
			for (s32 k = 0; k != 2; k++) {
				u8* pk  = (u8*)t + k * 4;
				void* p = advE3Rom_resume(0x48);
				if (p)
					p = fn_1_EEE4(p, pp(0x4c), k);
				*(void**)(pk + 0x368) = p;
			}
			for (s32 j = 0; j != 2; j++) {
				u8* p              = (u8*)t + j * 4;
				u8* q              = (u8*)t + j * 0x8c;
				*(s32*)(p + 0x394) = 0;
				*(s32*)(p + 0x234) = j;
				void* o            = advE3Rom_resume(0x28);
				if (o)
					o = __ct__7TObjectFP7TObject(o, pp(0x4c));
				*(void**)(p + 0x354) = o;
				fn_1_119E0(q + 0x23c, *(s32*)(p + 0x234));
				fn_1_F38C(t, j);
			}
			fn_1_F06C(t, 1);
			fn_1_F06C(t, 0);
			break;
		case 8:
			if (pp(0x39c) == 0) {
				void* p = advE3Rom_resume(0x30);
				if (p)
					p = fn_1_10F40(p, t);
				pp(0x39c) = p;
			}
			w(0x230) = 0;
			fn_1_119E0((u8*)t + 0x19c, w(0x230));
			fn_800A80E0(t, lbl_1_rodata_169C + w(0x228) * 0x30, w(0x230));
			fn_800A8C50(lbl_80303EC8, 1);
			break;
		case 9:
			w(0x2c) = 1;
			w(0x60) = 0xa;
			fn_1_7B24((u8*)t + 0x64, lbl_1_rodata_17EC + w(0x228) * 8);
			break;
		case 10:
			fn_1_F454(t);
			break;
	}
}
#pragma opt_common_subs reset

extern "C" void fn_1_FAA8(void* t)
{
	s32 sel = fn_1_11AA8((u8*)t + 0x84, 4, 3, -1);
	if (sel != -1 && w(0x228) != sel) {
		if (lbl_8042C388)
			fn_800B52E8(lbl_8042C388, 0xe007, 0, 0);
		w(0x228) = sel;
		fn_800A80E0(t, lbl_1_rodata_15A0 + w(0x228) * 0xc, 0);
		fl(0x38c) = lbl_1_rodata_19A4;
	}
	fn_800A8120(t);
	switch (fn_800A9398(lbl_80303EC8, -1)) {
		case 0:
			break;
		case 3:
			if (((s32*)((u8*)t + 0x370))[w(0x228)] != 0)
				fn_800A8174(t, lbl_1_rodata_1558[w(0x228)]);
			else
				fn_800A8174(t, lbl_1_rodata_1574[w(0x228)]);
			break;
		case 1:
			if (lbl_8042C388)
				fn_800B52E8(lbl_8042C388, 0xe009, 0, 0);
			w(0x2c) = 2;
			break;
		case 2:
			if (((s32*)((u8*)t + 0x370))[w(0x228)] != 0) {
				if (lbl_8042C388)
					fn_800B52E8(lbl_8042C388, 0xe008, 0, 0);
				w(0x2c) = 1;
				w(0x60) = 7;
				fn_1_7B24((u8*)t + 0x64, lbl_1_rodata_15F4 + w(0x228) * 8);
			} else {
				if (lbl_8042C388)
					fn_800B52E8(lbl_8042C388, 0xe018, 0, 0);
			}
			break;
	}
}

#pragma opt_common_subs off
extern "C" void fn_1_F81C(void* t)
{
	if (w(0x35c) == 2) {
		if (w(0x390)++ > 0x12c) {
			w(0x390) = 0;
			w(0x35c) = 3;
			fn_1_FFD8(t, 1);
		}
	} else if (w(0x35c) == 3) {
		if (w(0x390)++ > 0x12c) {
			w(0x2c) = 1;
			w(0x60) = 8;
			fn_1_7B24((u8*)t + 0x64, lbl_1_rodata_1904 + w(0x228) * 8);
		}
	} else {
		for (s32 i = 0; i != 2; i++) {
			u8* p = (u8*)t + i * 4;
			u8* q = (u8*)t + i * 0x8c;
			if (*(s32*)(p + 0x394) == 0) {
				s32 r = fn_1_11E48(q + 0x23c, i);
				if (r != -1 && *(s32*)(p + 0x234) != r) {
					if (lbl_8042C388)
						fn_800B52E8(lbl_8042C388, 0xe007, 0, 0);
					*(s32*)(p + 0x234) = r;
					fn_1_F38C(t, i);
				}
			}
			switch (fn_800A9398(lbl_80303EC8, i)) {
				case 1:
					if (lbl_8042C388)
						fn_800B52E8(lbl_8042C388, 0xe009, 0, 0);
					if (*(s32*)(p + 0x394) == 0)
						*(s32*)(p + 0x394) = -1;
					if (*(s32*)(p + 0x394) == 1) {
						*(s32*)(p + 0x394) = 0;
						fn_1_F06C(t, i);
					}
					break;
				case 2:
					if (*(s32*)(p + 0x394) == 0) {
						if (lbl_8042C388)
							fn_800B52E8(lbl_8042C388, 0xe008, 0, 0);
						*(s32*)(p + 0x394) = 1;
						fn_1_F118(t, i);
					}
					break;
			}
		}
		if (w(0x394) == -1 || w(0x398) == -1) {
			w(0x2c) = 1;
			w(0x60) = 5;
			fn_1_7B24((u8*)t + 0x64, lbl_1_rodata_1664 + w(0x228) * 8);
		}
		if (w(0x394) == 1 && w(0x398) == 1) {
			w(0x35c) = 2;
			w(0x390) = 0;
			fn_1_FFD8(t, 0);
		}
	}
}
#pragma opt_common_subs reset

// ExecTo-style: poll input, retarget selection
extern "C" void fn_1_F758(void* t)
{
	s32 r = fn_1_11F00((u8*)t + 0x19c);
	if (r != -1 && w(0x230) != r) {
		if (lbl_8042C388)
			fn_800B52E8(lbl_8042C388, 0xe007, 0, 0);
		w(0x230) = r;
		fn_800A80E0(t, lbl_1_rodata_169C + w(0x228) * 0x30, w(0x230));
	}
	fn_800A8120(t);
	if (fn_1_F610(t, 0) == 0)
		fn_1_F610(t, 1);
}

// ExecSelect-style dispatch (defined after fn_1_F758 so it is not inlined)
extern "C" s32 fn_1_F610(void* t, s32 mode)
{
	s32 ret = 1;
	switch (fn_800A9398(lbl_80303EC8, mode)) {
		case 3:
			fn_800A8174(t, lbl_1_rodata_1590[w(0x230)]);
			break;
		case 0:
			ret = 0;
			break;
		case 1:
			if (lbl_8042C388)
				fn_800B52E8(lbl_8042C388, 0xe009, 0, 0);
			w(0x2c) = 1;
			w(0x60) = 6;
			fn_1_7B24((u8*)t + 0x64, lbl_1_rodata_17EC + w(0x228) * 8);
			break;
		case 2:
			if (lbl_8042C388)
				fn_800B52E8(lbl_8042C388, 0xe008, 0, 0);
			w(0x2c) = 1;
			w(0x60) = 9;
			fn_1_7B24((u8*)t + 0x64, lbl_1_rodata_1824 + w(0x228) * 32 + w(0x230) * 8);
			break;
	}
	return ret;
}

// ADV_2P::MakeMenu - build the character grid UI
extern "C" void fn_1_F454(void* t)
{
	fn_8001938C(lbl_8029C310);
	fn_800A96B0(lbl_80303EC8, 0x28, 0);
	fn_800A96B0(lbl_80303EC8, 0x27, 0);
	fn_800A96B0(lbl_80303EC8, 0x18, 0);
	fn_8001934C(lbl_8029C310, 0, w(0x234));
	fn_8001934C(lbl_8029C310, 1, w(0x238));
	fn_8006642C((void*)((SMenu*)t)->sub80, 0, 0);
	fn_8006642C((char*)((SMenu*)t) + 0x80, 1, 0);
	s32 st = w(0x230);
	if (st == 0) {
		for (s32 i = 0; i != 3; i++)
			fn_8001936C(lbl_8029C310, i, *(s32*)((u8*)lbl_1_rodata_14E8 + w(0x228) * 0xc + i * 4));
		fn_80018D98(lbl_8029C310);
		fn_800191F8(lbl_8029C310, 2, lbl_1_rodata_153C[w(0x228)]);
	} else {
		struct MenuRow {
			s32 item[3];
		};
		MenuRow* base = (MenuRow*)lbl_1_rodata_14E8;
		s32 page      = w(0x228);
		fn_8001936C(lbl_8029C310, 0, base[page].item[st - 1]);
		fn_800191F8(lbl_8029C310, 1, lbl_1_rodata_153C[w(0x228)]);
	}
	w(0x48) = 1;
	w(0x2c) = 3;
	fn_800A96B0(lbl_80303EC8, 0x2a, 0xb);
}

extern "C" void fn_1_F38C(void* t, s32 i)
{
	s32 idx;
	s32 finalIdx;
	u32* self;
	s32 j;
	F38CNode node;
	fn_1_F358(t, i);
	idx  = i * 4;
	self = (u32*)t;
	if (self[i + 0xd5] != 0) {
		for (j = 0; j != 3; j++) {
			fn_1_6ABC(&node.a);
			node.a = j + ((s32*)t)[i + 0x8d] * 3;
			fn_1_5994(node.sub, ((u8(*)[0x24])lbl_1_data_7838)[i] + j * 0xc);
			node.c = 3;
			fn_1_63A8(((void**)t)[i + 0xd5], &node.a);
		}
	}
	finalIdx = i * 4;
	void* p  = *(void**)((u8*)t + finalIdx + 0x368);
	if (p)
		fn_1_ECC0(p, *(s32*)((u8*)t + finalIdx + 0x234) + 1);
}

// ADV_2P_Tag::On (defined after fn_1_F38C so it stays a real call there)
extern "C" void fn_1_F358(void* t, s32 i)
{
	void** p = (void**)((u8*)t + 0x354);
	if (p[i])
		fn_8001867C(p[i]);
}

// per-frame tag refresh
extern "C" void fn_1_F298(void* t)
{
	S298* o = (S298*)t;
	s32 v   = o->f234;
	fn_1_120B4(o->sub2c8);
	if (v != 0)
		fn_1_120C4(o->sub2c8, 0);
	if (v != 1)
		fn_1_120C4(o->sub2c8, 1);
	if (v != 2)
		fn_1_120C4(o->sub2c8, 2);
	if (v != 3)
		fn_1_120C4(o->sub2c8, 3);
	if (v == 0) {
		fn_1_119E0(o->sub2c8, 1);
		o->f238 = 1;
	} else {
		fn_1_119E0(o->sub2c8, 0);
		o->f238 = 0;
	}
}

extern "C" void fn_1_F118(void* t, s32 i)
{
	void* sub;
	s32 o;
	s32 v;
	s32 flags[4];
	if (i == 0)
		o = 1;
	if (i == 1)
		o = 0;
	u8* pi = (u8*)t + i * 4;
	v      = *(s32*)(pi + 0x234);
	sub    = (u8*)t + o * 0x8c + 0x23c;
	fn_1_120B4(sub);
	if (v != 0) {
		fn_1_120C4(sub, 0);
		flags[0] = 1;
	} else
		flags[0] = 0;
	if (v != 1) {
		fn_1_120C4(sub, 1);
		flags[1] = 1;
	} else
		flags[1] = 0;
	if (v != 2) {
		fn_1_120C4(sub, 2);
		flags[2] = 1;
	} else
		flags[2] = 0;
	if (v != 3) {
		fn_1_120C4(sub, 3);
		flags[3] = 1;
	} else
		flags[3] = 0;
	s32 a = *(s32*)(pi + 0x234);
	pi    = (u8*)t + o * 4;
	s32 b = *(s32*)(pi + 0x234);
	if (a != b && flags[b] != 0) {
		fn_1_119E0(sub, b);
	} else {
		if (v == 0) {
			fn_1_119E0(sub, 1);
			*(s32*)(pi + 0x234) = 1;
		} else {
			fn_1_119E0(sub, 0);
			*(s32*)(pi + 0x234) = 0;
		}
		fn_1_F38C(t, o);
	}
}

// toggle player i's tag on/off
extern "C" void fn_1_F06C(void* t, s32 i)
{
	void* tag;
	s32 o = 0;
	if (i == 0)
		o = 1;
	if (i == 1)
		o = 0;
	tag = (u8*)t + o * 0x8c + 0x23c;
	fn_1_120B4(tag);
	fn_1_120C4(tag, 0);
	fn_1_120C4(tag, 1);
	fn_1_120C4(tag, 2);
	fn_1_120C4(tag, 3);
	fn_1_119E0(tag, ((s32*)((u8*)t + 0x234))[o]);
}

extern "C" void fn_1_EF8C(void* t)
{
	EF8CView* v = (EF8CView*)t;
	void* h;
	h = fn_80116D2C(lbl_803E774C);
	for (s32 i = 0; i < 7; i++) {
		if (lbl_1_rodata_193C[i] <= *((u8*)h + 0x22))
			v->flags[i] = 1;
		else
			v->flags[i] = 0;
	}
	struct EF8CPtr {
		EF8CView* p;
	};
	EF8CPtr walk;
	u32 i  = 0;
	walk.p = v;
	for (; i != 7; i++) {
		void** q738 = ((void*(*)[2])lbl_1_bss_738)[i];
		u32* q7A8   = lbl_1_bss_7A8;
		if (walk.p->flags[0] == 0) {
			fn_801A45A0(q738[0], q7A8[0]);
			fn_801A45A0(q738[1], q7A8[1]);
		}
		walk.p = (EF8CView*)((u8*)walk.p + 4);
	}
}

// ADV_2P_Tag::ADV_2P_Tag
extern "C" void* fn_1_EEE4(void* t, void* parent, s32 arg)
{
	__ct__7TObjectFP7TObject(t, parent);
	pp(0x18) = lbl_1_data_79B0;
	fl(0x2c) = lbl_1_rodata_19A4;
	w(0x34)  = arg;
	w(0x38)  = 0;
	w(0x3c)  = 1;
	if (arg == 0) {
		pp(0x28) = lbl_1_data_75FC + 0xd0;
		w(0x40)  = 0;
		w(0x44)  = 1;
	} else {
		pp(0x28) = lbl_1_data_75FC + 0x138;
		w(0x40)  = 0;
		w(0x44)  = 0;
	}
	return t;
}

// ADV_2P_Tag::~ADV_2P_Tag
extern "C" void* fn_1_EE7C(void* t, short f)
{
	if (t) {
		pp(0x18) = lbl_1_data_79B0;
		__dt__7TObjectFv(t, 0);
		if (f > 0)
			advE3Rom_pause(t);
	}
	return t;
}

// ADV_2P_Tag::Exec
extern "C" void fn_1_EDE4(void* t)
{
	if (w(0x3c) != w(0x38))
		fn_1_ECD0(t);
	switch (w(0x38)) {
		case 1:
			fn_1_EC74(t);
			break;
		case 2:
			fn_1_EC70(t);
			break;
		case 3:
			fn_1_EC2C(t);
			break;
	}
	if (pp(0x28))
		fn_8012CEF0(pp(0x28), fl(0x2c));
}

// ---------------------------------------------------------------------------
// Matched functions
// ---------------------------------------------------------------------------

// ADV_2P_Tag::Off
extern "C" void fn_1_EDB8(void* t)
{
	if (pp(0x28))
		fn_8012CC20(pp(0x28));
}
