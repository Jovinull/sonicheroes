#include "types.h"

// ADV_AUDIO - the advertise/attract-mode audio-menu object (REL module 1).
//
// Semantic reference is the PS2 debug build's ADV_AUDIO class (grep ADV_AUDIO
// ps2_funcs_sz.txt). The GameCube release emits ~12 functions into this same
// translation unit. The module's own symbol table is unmangled, so every
// function links extern "C" and objdiff pairs by the dtk fn_1_<addr> name.
//
// Struct offsets are GameCube ground truth; the PS2 reference only supplies
// logic and names. The vtable data is at lbl_1_data_5964 (name "ADV_AUDIO" at
// lbl_1_data_5954) and installed at object+0x18 by the constructor.
//
// Fields are reached through offset macros (identical codegen to a named
// struct member) because the object is large (0x1e4 bytes). Every method names
// its object pointer `t`.

typedef void TObject;

struct ADV_AUDIO {
	s32 SetMode(s32 mode);
	void Exec();
	void Disp();
};

#define w(o)  (*(s32*)((u8*)t + (o)))
#define uw(o) (*(u32*)((u8*)t + (o)))
#define fl(o) (*(f32*)((u8*)t + (o)))
#define pp(o) (*(void**)((u8*)t + (o)))

// One SNG_*.adx table record (0x28 bytes). lbl_1_data_5934[i] points at an
// array of these; lbl_1_data_5944[i] is that array's length.
struct SND {
	s32 f0;      // 0x00 - index into the pitch/rate table
	void* f4;    // 0x04
	void* f8;    // 0x08
	u8 _0c[0x8]; // 0x0c
	void* f14;   // 0x14
	u32 f18;     // 0x18
	void* f1c;   // 0x1c
	u32 f20;     // 0x20
	s32 f24;     // 0x24
};

// An {index, float} pair table entry (8 bytes).
struct SF {
	s32 a; // 0x00
	f32 f; // 0x04
};

// The shared audio-bank object.
struct S4B50 {
	u8 _00[0x08];
	void* _08; // 0x08
	u8 _0c[0x134];
	void* _140; // 0x140
	u8 _144[0x64];
	void* _1a8; // 0x1a8
	u8 _1ac[0x5c];
};

// The audio descriptor block.
struct S4D78 {
	void* _00;
	void* _04;
	u32 _08;
	void* _0c;
	u32 _10;
	u32 _14;
};

// --- data/rodata living in the module's auto sections (outside this TU) ---
extern "C" u8 lbl_1_data_5964[];  // vtable
extern "C" u32 lbl_1_data_5960[]; // name pointer -> obj[0]
extern "C" S4B50 lbl_1_data_4B50;
extern "C" S4D78 lbl_1_data_4D78;
extern "C" SND* lbl_1_data_5934[];
extern "C" u32 lbl_1_data_5944[];
extern "C" char lbl_1_data_5784[];
extern "C" char lbl_1_data_59B4[];
extern "C" char lbl_1_data_59C4[];
extern "C" char lbl_1_data_59D4[];
extern "C" char lbl_1_data_59E4[];
extern "C" char lbl_1_data_5604[];
extern "C" char lbl_1_data_5620[];
extern "C" char lbl_1_data_563C[];
extern "C" char lbl_1_data_5658[];
extern "C" char lbl_1_data_59F4[];

extern "C" u32 lbl_1_rodata_1068[];
extern "C" u32 lbl_1_rodata_10B8[];
extern "C" u32 lbl_1_rodata_10F8[];
extern "C" f32 lbl_1_rodata_13F8;
extern "C" f32 lbl_1_rodata_1400;
extern "C" f32 lbl_1_rodata_1404;
extern "C" f32 lbl_1_rodata_1408;

extern "C" u8 lbl_80303EC8[];
extern "C" u8 lbl_8042C7E0[];
extern "C" u8 lbl_803E774C[];

// --- functions in other TUs of this module (or base class) ---
extern "C" void fn_1_119E0(void* a, s32 v);
extern "C" void fn_1_7B24(void* a, void* b);
extern "C" void fn_1_C978(void);
extern "C" void fn_1_CF38(void* t);
extern "C" void fn_1_CC08(void* t);
extern "C" void fn_1_CBA8(void* t);
extern "C" void fn_1_CA80(void* t);
extern "C" void fn_1_C9F4(void* t);
extern "C" void advE3Rom_pause(void* t);
extern "C" void* advE3Rom_resume(u32 size);
extern "C" void fn_1_120C4(void* a, s32 i);
extern "C" void fn_1_120E0(void);
extern "C" void fn_1_12124(void);
extern "C" void fn_1_6A0C(void);
extern "C" void fn_1_69AC(void);
extern "C" void fn_1_10FD8(void);
extern "C" void fn_1_10FB0(void);
extern "C" void fn_1_118E4(void* a);
extern "C" void fn_1_15294(void);
extern "C" void fn_1_15268(void);

extern "C" void fn_800A80E0(void* t, void* tbl, s32 idx);
extern "C" void fn_800A80DC(void* t, s32 v);
extern "C" void fn_800A823C(void);
extern "C" void fn_800A8264(void* t);
extern "C" void fn_800A8620(void* t, s32 v);
extern "C" void fn_800A8828(void* t, void* parent);
extern "C" void fn_800CC9F4(void* a);
extern "C" void fn_8012CC20(void* a);
extern "C" void fn_8012CEF0(void* a, f32 f);
extern "C" void fn_8012CE00(void* a, f32 f1, f32 f2);
extern "C" void* fn_80018818(void* obj, void* parent);
extern "C" void fn_801A45A0(void* a, s32 b);
extern "C" void* fn_801A4BBC(void* a, void* b);
extern "C" void fn_8012CA94(void* a);
extern "C" void fn_800CC280(void);
extern "C" void fn_800CD05C(void);
extern "C" void fn_8013BC78(void);
extern "C" void fn_801262DC(void);
extern "C" void fn_80126254(void);
extern "C" void fn_8013BBE0(void);
extern "C" void fn_80196D00(void);
extern "C" void fn_800CD138(void);
extern "C" s32 fn_80138994(void* a, s32 b, s32 c);
extern "C" void* fn_80116D2C(void* a);
extern "C" void fn_80116E3C(void* h, void* str);
extern "C" s32 fn_80116F5C(void* h, void* v);
extern "C" void fn_8012CB70(void* a);
extern "C" void __destroy_arr(void* a, void* dtor, s32 size, s32 n);
extern "C" void __construct_array(void* a, void* ctor, void* dtor, s32 size, s32 n);

// forward decls for intra-TU callees defined later (so MWCC emits `bl`)
extern "C" void* fn_1_D47C(void* t, void* parent);
extern "C" void fn_1_D6F0(void* t);
extern "C" void fn_1_D9C8(void* t, void* a, s32 b);
extern "C" void fn_1_D9D4(void* t, void* a, s32 b);

// ---------------------------------------------------------------------------

s32 ADV_AUDIO::SetMode(s32 mode)
{
	void* t = this;
	switch (mode) {
		case 5:
			fn_1_119E0((u8*)t + 0x80, w(0x198));
			fn_800A80E0(t, lbl_1_rodata_1068, w(0x198));
			break;
		case 6: {
			SF* sf;
			SF* entry;
			w(0x2c) = 9;
			w(0x60) = 7;
			fn_1_7B24((u8*)t + 0x64, &lbl_1_rodata_10B8[w(0x198) * 2]);
			sf        = (SF*)lbl_1_data_4B50._08;
			entry     = &sf[lbl_1_rodata_10F8[w(0x198)]];
			fl(0x1b4) = entry->f;
			return (s32)entry;
		}
		case 7:
			fn_1_C978();
			w(0x19c) = 0;
			fn_1_119E0((u8*)t + 0x10c, w(0x19c));
			break;
		case 9:
			w(0x1b0) = w(0x1ac);
			fn_800A823C();
			break;
		case 10: {
			SF* sf;
			fl(0x1c0) = lbl_1_rodata_1404;
			w(0x1c8)  = 0;
			w(0x1cc)  = 1;
			sf        = (SF*)lbl_1_data_4B50._1a8;
			fl(0x1c4) = lbl_1_rodata_1400 + sf[lbl_1_data_5934[w(0x198)][w(0x19c)].f0].f;
			w(0x1d0)  = lbl_1_data_5934[w(0x198)][w(0x19c)].f0;
			w(0x1d4)  = lbl_1_data_5934[w(0x198)][w(0x19c)].f0 + 1;
			fn_800CC9F4(lbl_1_data_5934[w(0x198)][w(0x19c)].f4);
			break;
		}
		case 11:
			fl(0x1c0) = *(f32*)((u8*)lbl_1_data_4B50._140 + 0x14);
			w(0x1c8)  = 2;
			w(0x1cc)  = 3;
			fn_800CC9F4(lbl_1_data_5784);
			break;
	}
}

void ADV_AUDIO::Exec()
{
	void* t = this;
	if (w(0x1ac)) {
		fn_800A8264(t);
		if (uw(0x1a8))
			fn_8012CC20(pp(0x1a8));
	} else {
		if (uw(0x1a8))
			fn_8012CC20(pp(0x1a8));
		fn_800A8264(t);
	}
	if (w(0x28) == 0xa || w(0x28) == 0xb) {
		for (s32 i = 0; i != 2; i++) {
			if (uw(0x1b8))
				fn_8012CC20(pp(0x1b8));
			t = (u8*)t + 4;
		}
	}
}

void ADV_AUDIO::Disp()
{
	void* t = this;
	switch (w(0x28)) {
		case 5:
			fn_1_CF38(t);
			break;
		case 6:
			break;
		case 7:
		case 8:
			fn_1_CC08(t);
			break;
		case 9:
			fn_1_CBA8(t);
			break;
		case 10:
			fn_1_CA80(t);
			break;
		case 11:
			fn_1_C9F4(t);
			break;
	}
	if (uw(0x1a8))
		fn_8012CEF0(pp(0x1a8), fl(0x34));
	for (s32 i = 0; i != 2; i++) {
		if (uw(0x1b8))
			fn_8012CE00(pp(0x1b8), fl(0x1c0), fl(0x1d8));
		t = (u8*)t + 4;
	}
}

extern "C" void* fn_1_D3F8(void* t, s16 flag)
{
	if (t) {
		pp(0x18) = lbl_1_data_5964;
		__destroy_arr((u8*)t + 0x80, (void*)fn_1_120E0, 0x8c, 2);
		fn_800A8620(t, 0);
		if (flag > 0)
			advE3Rom_pause(t);
	}
	return t;
}

#pragma opt_common_subs off
extern "C" void* fn_1_D47C(void* t, void* parent)
{
	void* sub;
	f32 z;
	fn_800A8828(t, parent);
	pp(0x18) = lbl_1_data_5964;
	__construct_array((u8*)t + 0x80, (void*)fn_1_12124, (void*)fn_1_120E0, 0x8c, 2);
	uw(0)                  = lbl_1_data_5960[0];
	*(s16*)((u8*)t + 0x1e) = 0x1e4;
	w(0x40)                = 4;
	w(0x44)                = 4;
	w(0x28)                = 1;
	w(0x2c)                = 1;
	pp(0x38)               = &lbl_1_data_4B50;
	pp(0x1a4)              = (u8*)&lbl_1_data_4B50 + 0x68;
	pp(0x1a8)              = (u8*)&lbl_1_data_4B50 + 0xd0;
	pp(0x1b8)              = (u8*)&lbl_1_data_4B50 + 0x138;
	pp(0x1bc)              = (u8*)&lbl_1_data_4B50 + 0x1a0;
	fl(0x1d8)              = lbl_1_rodata_13F8;
	fl(0x1dc)              = lbl_1_rodata_1408;
	sub                    = advE3Rom_resume(0x28);
	if (sub)
		sub = fn_80018818(sub, t);
	pp(0x1a0) = sub;
	w(0x1ac)  = 1;
	w(0x1b0)  = 1;
	z         = lbl_1_rodata_1404;
	fl(0x1b4) = z;
	fl(0x1c0) = z;
	fl(0x1c4) = z;
	w(0x1e0)  = 0;
	w(0x60)   = 5;
	w(0x64)   = 0;
	w(0x68)   = 0;
	w(0x198)  = 0;
	w(0x19c)  = 0;
	fn_1_120C4((u8*)t + 0x80, 0);
	fn_1_120C4((u8*)t + 0x80, 1);
	fn_1_120C4((u8*)t + 0x80, 2);
	fn_1_120C4((u8*)t + 0x80, 3);
	fn_800A80DC(t, 4);
	return t;
}
#pragma opt_common_subs reset

#pragma peephole on
#pragma optimization_level 1
extern "C" void* fn_1_D5F8(void* parent)
{
	void* obj = advE3Rom_resume(0x1e4);
	if (!obj)
		return obj;
	return fn_1_D47C(obj, parent);
}
#pragma optimization_level reset
#pragma peephole reset

extern "C" void fn_1_D638(void)
{
	s32 i;
	s32 j;
	for (i = 0; i != 4; i++) {
		for (j = 0; j != (s32)lbl_1_data_5944[i]; j++) {
			fn_1_D6F0((u8*)lbl_1_data_5934[i] + j * 0x28);
		}
	}
	fn_8012CA94(&lbl_1_data_4D78);
	fn_800CC280();
	fn_800CD05C();
	fn_1_118E4(*(void**)(lbl_80303EC8 + 0x68));
	fn_1_10FD8();
	fn_8013BC78();
	fn_1_15294();
	fn_801262DC();
	fn_1_6A0C();
}

extern "C" void fn_1_D6F0(void* t)
{
	if (uw(0x18))
		fn_801A45A0(pp(0x14), uw(0x18));
	if (uw(0x20))
		fn_801A45A0(pp(0x1c), uw(0x20));
	w(0x14) = 0;
	w(0x18) = 0;
	w(0x1c) = 0;
	w(0x20) = 0;
	w(0x24) = 0;
}

extern "C" void fn_1_D758(void)
{
	fn_1_69AC();
	fn_80126254();
	fn_1_15268();
	fn_8013BBE0();
	fn_1_10FB0();
	fn_80196D00();
	fn_800CD138();
	if (fn_80138994(lbl_8042C7E0, 0, 0) == 0x64)
		fn_80116E3C(fn_80116D2C(lbl_803E774C), lbl_1_data_59B4);
	if (fn_80138994(lbl_8042C7E0, 1, 0) == 0x64)
		fn_80116E3C(fn_80116D2C(lbl_803E774C), lbl_1_data_59C4);
	if (fn_80138994(lbl_8042C7E0, 2, 0) == 0x64)
		fn_80116E3C(fn_80116D2C(lbl_803E774C), lbl_1_data_59D4);
	if (fn_80138994(lbl_8042C7E0, 3, 0) == 0x64)
		fn_80116E3C(fn_80116D2C(lbl_803E774C), lbl_1_data_59E4);
	if (fn_80138994(lbl_8042C7E0, 4, 0) == 0x64) {
		fn_80116E3C(fn_80116D2C(lbl_803E774C), lbl_1_data_5604);
		fn_80116E3C(fn_80116D2C(lbl_803E774C), lbl_1_data_5620);
		fn_80116E3C(fn_80116D2C(lbl_803E774C), lbl_1_data_563C);
		fn_80116E3C(fn_80116D2C(lbl_803E774C), lbl_1_data_5658);
	}
	fn_8012CB70(&lbl_1_data_4D78);
	fn_800CC9F4(lbl_1_data_5784);
	if (lbl_1_data_4D78._0c) {
		s32 handle;
		s32 i;
		s32 j;
		void* h = fn_801A4BBC(lbl_1_data_4D78._0c, lbl_1_data_59F4);
		handle  = 0;
		if (h)
			handle = *(s32*)h;
		for (i = 0; i != 4; i++) {
			for (j = 0; j != (s32)lbl_1_data_5944[i]; j++) {
				SND* r = &lbl_1_data_5934[i][j];
				if (fn_80116F5C(fn_80116D2C(lbl_803E774C), r->f8) == 0)
					fn_1_D9D4(r, lbl_1_data_4D78._0c, handle);
				else
					fn_1_D9C8(r, lbl_1_data_4D78._0c, handle);
			}
		}
	}
}

extern "C" void fn_1_D9C8(void* t, void* a, s32 b)
{
	w(0x24) = 1;
}

extern "C" void fn_1_D9D4(void* t, void* a, s32 b)
{
	w(0x24)  = 0;
	pp(0x14) = fn_801A4BBC(a, pp(0xc));
	if (pp(0x14)) {
		w(0x18) = *(s32*)pp(0x14);
		fn_801A45A0(pp(0x14), b);
	}
	if (uw(0x10)) {
		pp(0x1c) = fn_801A4BBC(a, pp(0x10));
		if (pp(0x1c)) {
			w(0x20) = *(s32*)pp(0x1c);
			fn_801A45A0(pp(0x1c), b);
		}
	}
}

extern "C" void fn_1_DA84(void* t)
{
	w(0x80) = w(0x84);
	w(0x84) = w(0x88);
	w(0x88) = w(0x8c);
	w(0x8c) = w(0x90);
	w(0x90) = -1;
}
