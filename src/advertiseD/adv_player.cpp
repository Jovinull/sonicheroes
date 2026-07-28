#include "types.h"

// ADV_PLAYER - the advertise/attract-mode player object (REL module 1).
//
// Semantic reference is the PS2 debug build's ADV_PLAYER class (14 methods);
// the GameCube release additionally emits ~7 file-scope helpers into this same
// translation unit, for ~21 functions total. The module's own symbol table is
// unmangled, so every function links extern "C" and objdiff pairs by the
// dtk fn_1_<addr> name.
//
// Struct offsets are GameCube ground truth (the PS2 layout differs); the PS2
// reference only supplies logic and names. The vtable data is at
// lbl_1_data_1BE4 and installed at object+0x18 by the constructor.
//
// Fields are reached through offset macros (identical codegen to a named
// struct member) because the object is large (0x19c bytes) with many
// still-unnamed fields. Every method names its object pointer `t`.

typedef void TObject;

// Constructor parameter block (sADV_PLAYER). Only the read fields are typed.
struct sADV_PLAYER {
	s32 code;  // 0x00
	f32 x;     // 0x04
	f32 y;     // 0x08
	f32 z;     // 0x0c
	s32 mode;  // 0x10
	f32 scale; // 0x14
};

#define w(o)     (*(s32*)((u8*)t + (o)))
#define uw(o)    (*(u32*)((u8*)t + (o)))
#define fl(o)    (*(f32*)((u8*)t + (o)))
#define pp(o)    (*(void**)((u8*)t + (o)))
#define pa(o, i) (((void**)((u8*)t + (o)))[(i)])

// --- data/rodata living in the module's auto sections (outside this TU) ---
extern "C" u8 lbl_1_data_1BE4[]; // vtable
extern "C" u32 lbl_1_data_11A4[];
extern "C" u8 lbl_1_data_11AC[];
extern "C" u32 lbl_1_data_1BB4[]; // 12 name pointers
extern "C" void* lbl_1_data_1CD0[];
extern "C" u8 lbl_1_data_1C40[];

extern "C" f32 lbl_1_rodata_498[];
extern "C" f32 lbl_1_rodata_528[];
extern "C" f32 lbl_1_rodata_558[];
extern "C" f32 lbl_1_rodata_438[];
extern "C" f32 lbl_1_rodata_3A8[];
extern "C" u32 lbl_1_rodata_3D8[];
extern "C" f32 lbl_1_rodata_748;

extern "C" u8 lbl_1_bss_140[];
extern "C" u8 lbl_1_bss_200[];
struct Blk470 { // lbl_1_bss_470 element, stride 0x14
	u32 w[5];
};
struct Blk230 { // lbl_1_bss_230 element, stride 0x30
	u32 w[12];
};
extern "C" u8 lbl_1_bss_230[];
extern "C" u8 lbl_1_bss_470[];

// The attract-mode asset tables are contiguous fixed-stride arrays walked by
// the loops below. Viewing them as element arrays (rather than open-coded
// pointer advances) lets MWCC's strength reduction build the induction pointer
// straight into a callee-saved register, matching the original codegen.
struct Slot140 { // lbl_1_bss_140 element, stride 0x10
	u8 _0[4];
	void* p; // 0x4
	u8 _8[4];
	u32 size; // 0xc
};
typedef s32 Row2[2];
typedef s32 Row5[5];

extern "C" u8 lbl_80303EC8[];
struct E4C {
	u8 d[0x4c];
};
extern "C" E4C lbl_8029BBD0[];
extern "C" s32 lbl_802408F8;

// --- functions in other TUs of this module ---
extern "C" void fn_80194294(s32 id, u32* out);
extern "C" void fn_80194234(s32 id, s32 val);
extern "C" void fn_8014FF2C(void*);
extern "C" s32 fn_800CF114(void*);
extern "C" void fn_800FE464(void*);
extern "C" void fn_800CF224(void*);
extern "C" void fn_800CF070(void*, void*);
extern "C" void fn_800CF1F0(void*, s32);
extern "C" void fn_800CF1E8(void*, f32);
extern "C" void fn_800CF1D8(void*, s32);
extern "C" void fn_800CF1B8(void*, u32, u32);
extern "C" void* fn_1_5994(void* dst, const void* src);
extern "C" void fn_1_5C1C(void* t, s32 code);
extern "C" void fn_1_5510(void*);
extern "C" void fn_1_5544(void*);
extern "C" void fn_1_59B0(void*);
extern "C" void fn_1_5B08(void*);
extern "C" void fn_1_5764(void*);
extern "C" void fn_1_5658(void*);
extern "C" void fn_1_5B9C(void*);
extern "C" void advE3Rom_pause(void*);
extern "C" void* advE3Rom_resume(u32 size);
extern "C" void fn_80018818(void*, void*);
extern "C" void dtor_800186D0(void*, int);
extern "C" void __destroy_arr(void*, void*, s32, s32);
extern "C" void __construct_array(void*, void*, void*, s32, s32);
extern "C" void dtor_800CF564();
extern "C" void dtor_800FE334();
extern "C" void fn_800FE3FC();
extern "C" void fn_800CF5A8();
extern "C" void* memset(void*, int, u32);
extern "C" s32 fn_8005D9A0(s32, s32);
extern "C" void* fn_801471DC(void);
extern "C" void fn_801471C8(void*);
extern "C" void fn_8014705C(void*);
extern "C" void* fn_80041FF4(void*);
extern "C" s32 fn_80192F38(void*, s32, s32, s32);
extern "C" void* fn_80146EA8(void*);
extern "C" void fn_80197ED8(void*, s32);
extern "C" void fn_8020C2D8(void*);
extern "C" void fn_80150958(void*);
extern "C" void fn_801A46D0(void*);
extern "C" void* fn_80057644(s32);
extern "C" void* fn_800BCC84(void*, s32, s32);
extern "C" void* fn_80012994(s32);
extern "C" void fn_800D0624(void*, void*, void*);
extern "C" void fn_800BA7F8(void*, void*, void*);
extern "C" void* fn_800BC580(void*, void*, void*);
extern "C" void fn_801A4C84(void*);
extern "C" void* fn_800BC46C(void*, void*, void*);
extern "C" void* fn_800BBF20(void*, void*, void*);
extern "C" void* fn_8022CF5C(void*);
extern "C" void fn_800BCBD4(void*, s32);
extern "C" void fn_800126C8(void*);
extern "C" void fn_800D075C(void*);
extern "C" void fn_8012C840(void*);
extern "C" void* fn_800426E0(void*, u32*);
extern "C" void* fn_800D082C(u32);
extern "C" void fn_800D06C0(void*, void*, u32);
extern "C" void fn_800426B4(void*);
extern "C" s32 fn_800A8C0C(void*);
extern "C" s32 fn_800A92E0(void*, s32, s32);
extern "C" s32 fn_800A9398(void*, s32);
extern "C" u32 fn_801D5C40(void);

extern "C" void* fn_1_5FBC(void* t, void* parent, const sADV_PLAYER* s);
extern "C" void fn_1_6414(void);
extern "C" void fn_1_6AEC(void* t, s32 v);
extern "C" s32 fn_1_6AF4(void* t);
extern "C" void fn_1_6AFC(void* t, void* v);
extern "C" void fn_1_6B04(void* t, s32 v);

// ---------------------------------------------------------------------------

// 0x5CBC - save/override input configs, tear down clumps, restore configs.
extern "C" void fn_1_5CBC(void* t)
{
	u32 s8, s6, s9, sc, s14;
	// `v` aliases t; declared mid-locals and used for the later accesses so the
	// object pointer lands in the callee-saved register the target uses (fixes a
	// reg-allocation rotation). Same object, identical semantics.
	u8* v;
	u32 se, sa, sb;
	fn_80194294(8, &s8);
	fn_80194294(6, &s6);
	fn_80194294(9, &s9);
	fn_80194294(0xc, &sc);
	fn_80194294(0x14, &s14);
	fn_80194294(0xe, &se);
	fn_80194294(0xa, &sa);
	fn_80194294(0xb, &sb);
	fn_80194234(8, 1);
	fn_80194234(6, 1);
	fn_80194234(9, 2);
	fn_80194234(0xc, 1);
	fn_80194234(0x14, 2);
	fn_80194234(0xe, 0);
	fn_80194234(0xa, 5);
	fn_80194234(0xb, 6);
	{
		void* c = pp(0xec);
		if (c && w(0x194) > 2)
			fn_8014FF2C(c);
	}
	v = (u8*)t;
	fn_8014FF2C(*(void**)(v + 0xc0));
	if (w(0x134) && *(s32*)(v + 0x194) > 2) {
		fn_8014FF2C(((void**)(v + 0xc4))[fn_800CF114(v + 0x140)]);
		if (((void**)(v + 0xd8))[fn_800CF114((u8*)t + 0x168)])
			fn_8014FF2C(((void**)(v + 0xd8))[fn_800CF114(v + 0x168)]);
	}
	fn_80194234(8, s8);
	fn_80194234(6, s6);
	fn_80194234(9, s9);
	fn_80194234(0xc, sc);
	fn_80194234(0x14, s14);
	fn_80194234(0xe, se);
	fn_80194234(0xa, sa);
	fn_80194234(0xb, sb);
}

// 0x5E8C - per-frame update (Exec).
extern "C" void fn_1_5E8C(void* t)
{
	// `v` aliases t; assigning it after the first three calls parks the object
	// pointer in the callee-saved register the target uses. Same object.
	u8* v;
	w(0x194) = w(0x194) + 1;
	fn_1_5544(t);
	fn_1_59B0(t);
	fn_1_5B08(t);
	v = (u8*)t;
	fn_800FE464(v + 0x28);
	if (*(u32*)(v + 0xec))
		fn_800FE464(v + 0x74);
	fn_800CF224(v + 0x140);
	fn_800CF224(v + 0x168);
	fn_800CF070(v + 0x168, v + 0x140);
	fn_1_5764(t);
	fn_1_5658(t);
}

// 0x5F1C - destructor.
extern "C" void* fn_1_5F1C(void* t, s16 flag)
{
	if (t) {
		pp(0x18) = lbl_1_data_1BE4;
		fn_1_5B9C(t);
		__destroy_arr((u8*)t + 0x140, (void*)dtor_800CF564, 0x28, 2);
		__destroy_arr((u8*)t + 0x28, (void*)dtor_800FE334, 0x4c, 2);
		dtor_800186D0(t, 0);
		if (flag > 0)
			advE3Rom_pause(t);
	}
	return t;
}

// 0x5FBC - constructor.
#pragma opt_common_subs off
extern "C" void* fn_1_5FBC(void* t, void* parent, const sADV_PLAYER* s)
{
	fn_80018818(t, parent);
	pp(0x18) = lbl_1_data_1BE4;
	__construct_array((u8*)t + 0x28, (void*)fn_800FE3FC, (void*)dtor_800FE334, 0x4c, 2);
	__construct_array((u8*)t + 0x140, (void*)fn_800CF5A8, (void*)dtor_800CF564, 0x28, 2);
	uw(0)                  = lbl_1_data_11A4[0];
	*(s16*)((u8*)t + 0x1e) = 0x19c;
	memset((u8*)t + 0xc0, 0, 0x40);
	fl(0x124) = s->scale;
	switch (s->mode) {
		case 3:
			fn_1_5994((u8*)t + 0x100, &lbl_1_rodata_498[s->code * 3]);
			fl(0x124) = lbl_1_rodata_528[s->code];
			fl(0x100) = fl(0x100) + s->x;
			fl(0x104) = fl(0x104) + s->y;
			fl(0x108) = fl(0x108) + s->z;
			if (s->y < lbl_1_rodata_748)
				fl(0x104) = fl(0x104) - lbl_1_rodata_558[s->code];
			break;
		case 1:
			fn_1_5994((u8*)t + 0x100, &lbl_1_rodata_498[s->code * 3]);
			fl(0x124) = lbl_1_rodata_528[s->code];
			break;
		default:
			fn_1_5994((u8*)t + 0x100, &s->x);
			break;
	}
	w(0x190) = s->code;
	{
		f32 zero  = lbl_1_rodata_748;
		fl(0x118) = zero;
		fl(0x11c) = zero;
		fl(0x120) = zero;
	}
	fn_1_5994((u8*)t + 0x10c, (u8*)t + 0x100);
	fl(0x128) = fl(0x124);
	fl(0x12c) = lbl_1_rodata_748;
	w(0x130)  = 0;
	switch (s->code) {
		case 5:
			w(0x134) = 2;
			break;
		case 6:
		case 8:
			w(0x134) = 1;
			break;
		default:
			w(0x134) = 0;
			break;
	}
	{
		u32* table = (u32*)lbl_1_rodata_438;
		w(0x13c)   = table[s->code * 2 + 1];
	}
	fn_1_5C1C(t, s->code);
	fn_1_6B04((u8*)t + 0x28, w(0xc0));
	fn_1_6AFC((u8*)t + 0x28, lbl_1_data_11AC);
	if (s->mode == 2)
		fn_1_6AEC((u8*)t + 0x28, s->code + 0x18);
	else
		fn_1_6AEC((u8*)t + 0x28, s->code);
	if (uw(0xec)) {
		fn_1_6B04((u8*)t + 0x74, w(0xec));
		fn_1_6AFC((u8*)t + 0x74, lbl_1_data_11AC);
		fn_1_6AEC((u8*)t + 0x74, s->code + 0x30);
	}
	switch (s->code) {
		case 0:
		case 1:
		case 3:
		case 4:
		case 7:
		case 9:
		case 10: {
			w(0x138) = fn_8005D9A0(fn_1_6AF4((u8*)t + 0x28), 1);
			break;
		}
		case 2:
		case 5:
		case 6:
		case 8:
		case 11:
			w(0x138) = 0x1f;
			break;
	}
	{
		s32 i;
		u32* pair;
		for (i = 0; i != 2; i++) {
			s32 offset = i * 0x28;
			if (w(0x134))
				fn_800CF1F0((u8*)t + 0x140 + offset, w(0x134) - 1);
			else
				fn_800CF1F0((u8*)t + 0x140 + offset, 0);
			fn_800CF1E8((u8*)t + 0x140 + offset, lbl_1_rodata_3A8[s->code]);
			fn_800CF1B8(
			    (pair = (u32*)((u8*)lbl_1_rodata_3D8 + s->code * 8), (u8*)t + 0x140 + offset),
			    pair[0], pair[1]);
			offset += 0x28;
		}
	}
	fn_800CF1D8((u8*)t + 0x168, 3);
	w(0x194) = 0;
	w(0x198) = -1;
	return t;
}
#pragma opt_common_subs reset

// 0x63A8 - allocate + construct (Create).
extern "C" void* fn_1_63A8(void* parent, const sADV_PLAYER* s)
{
	if (parent) {
		void* obj = advE3Rom_resume(0x19c);
		if (obj)
			obj = fn_1_5FBC(obj, parent, s);
		return obj;
	}
	return 0;
}

// 0x6414 - release the shared loader handle.
#pragma dont_inline on
extern "C" void fn_1_6414(void)
{
	void* p = fn_801471DC();
	if (p) {
		fn_801471C8(0);
		fn_8014705C(p);
	}
}

// 0x6458 - open the archive and pull one entry.
extern "C" void fn_1_6458(void)
{
	void* h;
	void* r = 0;
	h       = fn_80041FF4(lbl_1_data_1C40);
	if (h) {
		if (fn_80192F38(h, 0x21, 0, 0))
			r = fn_80146EA8(h);
		fn_80197ED8(h, 0);
	}
	if (r)
		fn_801471C8(r);
}
#pragma dont_inline reset

// 0x64E0 - free all cached clumps/textures/anim data.
extern "C" void fn_1_64E0(void)
{
	Blk470* a470 = (Blk470*)lbl_1_bss_470;
	Blk230* a230 = (Blk230*)lbl_1_bss_230;
	u32* a200    = (u32*)lbl_1_bss_200;
	s32 i, j, val;
	for (i = 0; i != 12; i++) {
		val = 0;
		for (j = 0; j != 5; j++) {
			if (a470[i].w[j]) {
				fn_8020C2D8((void*)a470[i].w[j]);
				a470[i].w[j] = val;
			}
		}
		val = 0;
		for (j = 0; j != 12; j++) {
			if (a230[i].w[j]) {
				fn_80150958((void*)a230[i].w[j]);
				a230[i].w[j] = val;
			}
		}
		if (a200[i]) {
			fn_801A46D0((void*)a200[i]);
			a200[i] = 0;
		}
	}
	fn_1_6414();
}
extern "C" u32 lbl_1_rodata_588[];
extern "C" u32 lbl_1_rodata_198[];
extern "C" s32 lbl_1_rodata_1C8[];
extern "C" s32 lbl_1_rodata_2B8[];
extern "C" s32 lbl_1_rodata_5B8[];
extern "C" void* fn_800BC580(void*, void*, void*);

static inline u32* advPlayerIdentity(u32* p)
{
	return p;
}

// 0x65BC - load all attract-mode player assets.
extern "C" void fn_1_65BC(void)
{
	struct Handle {
		void* value;
	};
	struct SlotCursor {
		Slot140* value;
	};
	struct WordCursor {
		u32* value;
	};
	struct SignedCursor {
		s32* value;
	};
	struct DstRow {
		u32 value;
		u8 pad[0x20];
	};
	struct DestCursor {
		DstRow* value;
	};
	u32* a588;
	u32* a198;
	s32 i;
	Row5* b1C8;
	Handle obj;
	SignedCursor w5b8;
	WordCursor w470;
	SlotCursor p140;
	WordCursor p200;
	Row5* b2B8;
	Row5* b5B8;

	fn_1_6458();

	obj.value  = 0;
	w5b8.value = 0;
	w470.value = 0;
	i          = 0;
	p140.value = (Slot140*)lbl_1_bss_140;
	a588       = lbl_1_rodata_588;
	p200.value = (u32*)lbl_1_bss_200;
	a198       = lbl_1_rodata_198;
	do {
		s32* w1c8;
		u32* w230;
		s32* w2b8;
		s32 j;
		s32 k;
		void* d18;
		void* d17;
		obj.value = fn_80057644(0x58);
		if (obj.value)
			obj.value = fn_800BCC84(obj.value, 0, 0);
		d18 = fn_80012994(0x7d000);
		d17 = fn_80012994(p140.value->size + 0x40);
		if (d17)
			fn_800D0624(d17, p140.value->p, (void*)p140.value->size);
		if (obj.value && d18 && d17) {
			fn_800BA7F8(obj.value, d17, (void*)p140.value->size);
			*p200.value = (u32)fn_800BC580(obj.value, (void*)*a588, d18);
			if (*p200.value) {
				fn_801A4C84((void*)*p200.value);
				((Blk230*)lbl_1_bss_230)[i].w[0] = (u32)fn_800BC46C(obj.value, (void*)*a198, d18);
				{
					b1C8 = (Row5*)lbl_1_rodata_1C8;
					b2B8 = (Row5*)lbl_1_rodata_2B8;
					j    = 0;
					w1c8 = b1C8[i];
					w230 = ((Blk230*)lbl_1_bss_230)[i].w;
					w2b8 = b2B8[i];
					do {
						if (*w1c8 != -1)
							w230[1] = (u32)fn_800BC46C(obj.value, (void*)*w1c8, d18);
						if (*w2b8 != -1)
							w230[6] = (u32)fn_800BC46C(obj.value, (void*)*w2b8, d18);
						w1c8++;
						w230++;
						w2b8++;
						j++;
					} while (j != 5);
				}
				{
					s32* w438 = ((Row2*)lbl_1_rodata_438)[i];
					if (*w438 != -1)
						((Blk230*)lbl_1_bss_230)[i].w[11]
						    = (u32)fn_800BC46C(obj.value, (void*)*w438, d18);
				}
				{
					b5B8       = (Row5*)lbl_1_rodata_5B8;
					k          = 0;
					w5b8.value = b5B8[i];
					w470.value = ((Blk470*)lbl_1_bss_470)[i].w;
					do {
						if (*w5b8.value != -1) {
							void* tex = fn_800BBF20(obj.value, (void*)*w5b8.value, d18);
							if (tex) {
								void* alt = fn_8022CF5C(tex);
								fn_8020C2D8(tex);
								tex = alt;
							}
							*w470.value = (u32)tex;
						}
						w5b8.value++;
						w470.value++;
						k++;
					} while (k != 5);
				}
			}
		}
		if (obj.value)
			fn_800BCBD4(obj.value, 1);
		if (d18)
			fn_800126C8(d18);
		if (d17)
			fn_800126C8(d17);
		p140.value++;
		a588++;
		p200.value++;
		a198++;
		i++;
	} while (i != 0xc);

	{
		WordCursor s4;
		WordCursor d4;
		DestCursor dst;
		u32* cond;
		s32 m;
		s32 row_idx;
		s32 n;
		s4.value  = 0;
		d4.value  = 0;
		m         = 0;
		row_idx   = 0;
		dst.value = (DstRow*)lbl_1_data_11AC;
		cond      = (u32*)lbl_1_bss_470 + 0x14;
		do {
			u32* s0;
			u32* s1;
			u32* d1;
			u32* s2;
			u32* d2;
			u32* s3;
			u32* d3;
			n        = 0;
			s0       = ((Blk470*)lbl_1_bss_470)[row_idx].w;
			s1       = advPlayerIdentity(((Blk470*)lbl_1_bss_470)[row_idx].w + 1);
			d1       = advPlayerIdentity(&dst.value[12].value);
			s2       = advPlayerIdentity(((Blk470*)lbl_1_bss_470)[row_idx].w + 2);
			d2       = advPlayerIdentity(&dst.value[24].value);
			s3       = advPlayerIdentity(((Blk470*)lbl_1_bss_470)[row_idx].w + 3);
			d3       = advPlayerIdentity(&dst.value[36].value);
			s4.value = ((Blk470*)lbl_1_bss_470)[row_idx].w + 4;
			d4.value = &dst.value[48].value;
			for (; n < 4; n++) {
				dst.value->value = *s0;
				*d1              = *s1;
				if (*s2)
					*d2 = *s2;
				else
					*d2 = *s0;
				if (*s3)
					*d3 = *s3;
				else
					*d3 = *s1;
				if (cond)
					*d4.value = *s4.value;
			}
			row_idx++;
			dst.value++;
			m++;
		} while (m != 0xc);
	}

	{
		u32* e;
		s32 cm = 0;
		do {
			s32 cn = 0;
			e      = ((Blk230*)lbl_1_bss_230)[cm].w;
			do {
				fn_1_5510((void*)*e);
				e++;
				cn++;
			} while (cn != 0xc);
			cm++;
		} while (cm != 0xc);
	}
}

// 0x69AC - free the loaded asset table.
extern "C" void fn_1_69AC(void)
{
	Slot140* slot = (Slot140*)lbl_1_bss_140;
	s32 i;
	for (i = 0; i != 12; i++) {
		if (slot[i].p)
			fn_800D075C(slot[i].p);
		fn_8012C840(&slot[i]);
	}
}

// 0x6A0C - decompress each asset blob into a fresh buffer.
extern "C" void fn_1_6A0C(void)
{
	u32* names    = lbl_1_data_1BB4;
	Slot140* slot = (Slot140*)lbl_1_bss_140;
	s32 i;
	for (i = 0; i != 12; i++) {
		u32 size;
		void* f = fn_800426E0((void*)names[i], &size);
		if (f) {
			size      = (size + 0x1f) & ~0x1f;
			void* buf = fn_800D082C(size);
			if (buf) {
				fn_800D06C0(f, buf, size);
				slot[i].size = size;
				slot[i].p    = buf;
			}
			fn_800426B4(f);
		}
	}
}

// 0x6ABC - reset a wing sub-state to defaults.
extern "C" void fn_1_6ABC(void* t)
{
	f32 z;
	w(0)     = 0;
	z        = lbl_1_rodata_748;
	fl(4)    = z;
	fl(8)    = z;
	fl(0xc)  = z;
	w(0x10)  = 0;
	fl(0x14) = z;
}

// 0x6AE8 - empty virtual.
extern "C" void fn_1_6AE8(void* t) { }

// 0x6AEC - setter.
extern "C" void fn_1_6AEC(void* t, s32 v)
{
	w(0x1c) = v;
}

// 0x6AF4 - getter.
extern "C" s32 fn_1_6AF4(void* t)
{
	return w(0x34);
}

// 0x6AFC - setter.
extern "C" void fn_1_6AFC(void* t, void* v)
{
	pp(0x2c) = v;
}

// 0x6B04 - setter.
extern "C" void fn_1_6B04(void* t, s32 v)
{
	w(0x30) = v;
}

// 0x6B0C - commit staged value once past threshold.
extern "C" void fn_1_6B0C(void* t)
{
	if (w(0x30) >= 0xb4)
		w(0x2c) = w(0x80);
}

// 0x6B24 - trigger on a button.
extern "C" void fn_1_6B24(void* t)
{
	if (fn_800A8C0C(lbl_80303EC8)) {
		w(0x2c) = 0xa;
		w(0x80) = 2;
	}
}

// 0x6B70 - analog/dpad state machine.
extern "C" void fn_1_6B70(void* t)
{
	if (fn_800A92E0(lbl_80303EC8, 1, -1)) {
		w(0x84)  = 1;
		fl(0x34) = ((f32*)lbl_1_data_1CD0[2])[5];
	} else if (fn_800A92E0(lbl_80303EC8, 2, -1)) {
		w(0x84)  = 0;
		fl(0x34) = ((f32*)lbl_1_data_1CD0[2])[9];
	} else if (fn_800A9398(lbl_80303EC8, -1) == 1) {
		w(0x84) = 0;
		w(0x2c) = 9;
	} else if (fn_800A9398(lbl_80303EC8, -1) == 2) {
		if (w(0x84) == 0)
			w(0x2c) = 9;
		else
			w(0x2c) = 7;
	}
}

// 0x6C74 - start/idle decision.
extern "C" void fn_1_6C74(void* t)
{
	u8* e = (u8*)lbl_8029BBD0;
	e += lbl_802408F8 * 0x4c;
	if (!(*(u32*)(e + 0x48) & 0x200) && fn_801D5C40() != 1) {
		w(0x40) = 0xc;
		w(0x44) = 0xc;
		w(0x2c) = 2;
	} else {
		w(0x2c) = 1;
		w(0x60) = 6;
		w(0x64) = 0;
		w(0x68) = 1;
	}
}
