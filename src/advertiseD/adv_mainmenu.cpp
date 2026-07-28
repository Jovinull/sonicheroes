#include "types.h"

// ADV_MAINMENU - the advertise-module main-menu state machine.
//
// Module-relative .text 0x04A84-0x05CBC (22 functions). Class ADV_MAINMENU
// (name string at .data 0x10C4, vtable at .data 0x10D8). Reference-guided from
// the PS2 debug build's ADV_MAINMENU class (semantic, not byte-identical).
//
// REL symbols are unmangled, so every function is written extern "C".

struct Vec3f {
	f32 x, y, z;
};

struct MenuEntry {
	u8 _pad[0xc];
	void* obj;
}; // 0x10

struct SetupParams {
	/* 0x00 */ void* p0;
	/* 0x04 */ void* p4;
	/* 0x08 */ void* p8;
	/* 0x0C */ void* pc;
	/* 0x10 */ s32 i10;
	/* 0x14 */ f32 f14;
	/* 0x18 */ f32 f18;
	/* 0x1C */ f32 f1c;
	/* 0x20 */ f32 f20;
	/* 0x24 */ f32 f24;
	/* 0x28 */ u8 pad28[0x38 - 0x28];
	/* 0x38 */ s32 i38;
	/* 0x3C */ u8 pad3c[8];
};

struct ADV_MAINMENU {
	/* 0x000 */ u8 pad_0x00[0x18];
	/* 0x018 */ void* vtable;
	/* 0x01C */ u8 pad_0x1C[0x28 - 0x1C];
	/* 0x028 */ s32 mode;
	/* 0x02C */ u8 pad_0x2C[0xc0 - 0x2C];
	/* 0x0C0 */ void* subobjs[16];
	/* 0x100 */ Vec3f vec_0x100;
	/* 0x10C */ Vec3f vec_0x10c;
	/* 0x118 */ Vec3f vec_0x118;
	/* 0x124 */ f32 unk_0x124;
	/* 0x128 */ f32 unk_0x128;
	/* 0x12C */ f32 unk_0x12c;
	/* 0x130 */ u8 pad_0x130[0x13c - 0x130];
	/* 0x13C */ s32 unk_0x13c;
	/* 0x140 */ u8 pad_0x140[0x190 - 0x140];
	/* 0x190 */ s32 idx;
	/* 0x194 */ u8 pad_0x194[0x198 - 0x194];
	/* 0x198 */ s32 counter;
	/* 0x19C */ u8 pad_0x19C[0x3c0 - 0x19C];
}; // size 0x3c0

extern "C" {

// --- externs to other modules / the DOL ------------------------------------
ADV_MAINMENU* fn_1_B1C(int size);                         // operator new
ADV_MAINMENU* advE3Rom_resume(s32 size);                  // shared allocator (0xB1C)
ADV_MAINMENU* fn_1_4E9C(ADV_MAINMENU* obj, void* parent); // ADV_MAINMENU ctor
void fn_1_4D50(ADV_MAINMENU* obj);
void fn_800A8C08(const char* name);
void fn_8014F1B0(void* obj);
void fn_8014FFBC(void* obj, void (*cb)(void*), int arg);
void* __destroy_arr(void* arr, void (*dtor)(void*), int size, int count);
void fn_800A8620(void* obj, int flag); // base class destructor
void advE3Rom_pause(void* obj);        // operator delete
void fn_1_120E0(void* elem);           // sub-object destructor
int fn_800CB368(void* obj, int a, int b);
void* fn_8015BD78(void* obj);
void fn_8015BBF8(void* a, void* obj);
void fn_80150958(void* obj);
void fn_8019ED68(void* obj, void* mat, f32 f, int mode);
void fn_8019EB94(void* obj, void* vec, int mode);
void* fn_80150588(void* src);
void fn_8003C640(void* obj);
void* fn_800A943C(const char* name);
void fn_8015BB08(void* a, void* obj);
void* fn_1_6AF4(void* p);
void* fn_8019E8EC(void* p);
void fn_8019E880(void* p);
void fn_1_56E0(void* dst, void* src);
void fn_801A45A0(void* a, void* b);
void fn_8012CA94(void* p);

void fn_1_3AC0(void* obj);
void fn_1_47D8(void* obj);
void fn_1_45A4(void* obj);
void fn_1_4588(void* obj);
void fn_1_4360(void* obj);
void fn_1_4344(void* obj);
void fn_1_4294(void* obj);
void fn_1_423C(void* obj);
void fn_1_4200(void* obj);
void fn_1_416C(void* obj);
void fn_1_4118(void* obj);
void fn_8012CB70(void* p);
void* fn_801A4BBC(void* a, void* b);
f32 fn_801991B4(void* v);
void fn_801990E0(void* dst, void* src);
void fn_1_5994(Vec3f* dst, Vec3f* src);
void fn_1_6AEC(void* p, int n);
int fn_1_12A0(void* p, int n);
void advE3Rom_setFlag(void* p);
void fn_1_119E0(void* dst, void* src);
void fn_1_4058(void* obj, int a, void* p);
void fn_1_4028(void* obj, int a);
void fn_1_152C0(void* p);
void* fn_8012ECA8(int a, int b);
void* fn_1_150AC(void* obj, void* params);
void fn_800A8828(void* obj, void* parent);
void __construct_array(void* arr, void (*ctor)(void*), void (*dtor)(void*), int size, int count);
void fn_1_12124(void* p);
void fn_1_120C4(void* p, int i);
void* fn_800A8BF0(void* p);
void fn_1_11750(int n);
void fn_1_10F40(void* p, void* obj);
void fn_1_3B28(void* obj);
void fn_800A80DC(void* obj, int n);

struct MMDataRec {
	u8 _00[8];
	void* data;
	u8 _0c[0x68 - 0x0c];
};
extern MMDataRec lbl_1_data_DF4[];
extern const f32 lbl_1_rodata_180;
extern const f32 lbl_1_rodata_184;
extern const f32 lbl_1_rodata_188;
extern const f32 lbl_1_rodata_18C;
extern const f32 lbl_1_rodata_190;
extern const f32 lbl_1_rodata_194;

extern void* lbl_1_bss_130;
extern void* lbl_1_bss_E0[10][2];
extern void* lbl_1_bss_90[10][2];
extern u8 lbl_1_data_E7C[];
extern void* lbl_1_data_1074[][2];
extern u8 lbl_1_data_118C[];

extern u8 lbl_80303EC8[];
extern u8 lbl_1_data_10D8[]; // ADV_MAINMENU vtable
extern void* lbl_1_data_10D4;
extern void* lbl_1_rodata_6A8[];
extern s32 lbl_1_rodata_6D8[][2];
extern void* lbl_8042C180;
extern u8 lbl_80239984[];
extern void* lbl_1_bss_230[];
extern const f32 lbl_1_rodata_738; // 0.001
extern const f32 lbl_1_rodata_73C; // 5.0
extern const f32 lbl_1_rodata_740; // -0.001
extern const f32 lbl_1_rodata_744; // -5.0
extern const f32 lbl_1_rodata_748; // 0.0

#pragma force_active on
static void* lbl_1_data_1108 = (void*)fn_1_4D50;

// clang-format off

struct MMSel {
	u8 _pad[0x8c];
};
struct MMCtorView {
	u8 _pad0[0x94];
	MMSel sel[5];
};
struct P56 {
	u32 x;
	u32 y;
};
struct Row56 {
	P56 p;
	u32 c;
	u32 d;
};
struct Blk56 {
	Row56 r[4];
};

void fn_1_4A84(ADV_MAINMENU* obj, int arg)
{
	if (*(void**)((char*)obj + 0x3bc) != 0) {
		advE3Rom_setFlag(*(void**)((char*)obj + 0x3bc));
		*(void**)((char*)obj + 0x3bc) = 0;
	}
	switch (arg) {
	case 5:
		*(s32*)((char*)obj + 0x3c) = 0;
		*(void**)((char*)obj + 0x38)
		    = &lbl_1_data_DF4[*(s32*)((char*)obj + 0x3c)];
		fn_1_119E0((char*)obj + 0x2c4, *(void**)((char*)obj + 0x90));
		fn_1_4058(obj, 4, *(void**)((char*)obj + 0x90));
		fn_1_4028(obj, 4);
		break;
	case 6:
		*(s32*)((char*)obj + 0x3c) = 0;
		*(void**)((char*)obj + 0x38)
		    = &lbl_1_data_DF4[*(s32*)((char*)obj + 0x3c)];
		fn_1_119E0((char*)obj + 0x94, *(void**)((char*)obj + 0x80));
		fn_1_4058(obj, 0, *(void**)((char*)obj + 0x80));
		fn_1_4028(obj, 0);
		break;
	case 7:
		*(void**)((char*)obj + 0x38) = 0;
		break;
	case 8:
		*(s32*)((char*)obj + 0x3c) = 0;
		*(void**)((char*)obj + 0x38)
		    = &lbl_1_data_DF4[*(s32*)((char*)obj + 0x3c)];
		fn_1_119E0((char*)obj + 0x1ac, *(void**)((char*)obj + 0x88));
		fn_1_4058(obj, 2, *(void**)((char*)obj + 0x88));
		fn_1_4028(obj, 2);
		break;
	case 9:
		*(void**)((char*)obj + 0x38) = 0;
		break;
	case 1:
		*(void**)((char*)obj + 0x38)
		    = &lbl_1_data_DF4[*(s32*)((char*)obj + 0x3c)];
		break;
	case 13: {
		SetupParams p;
		fn_1_152C0(&p);
		p.p0  = fn_8012ECA8(8, 0);
		p.p4  = fn_8012ECA8(8, 1);
		p.p8  = fn_8012ECA8(8, 2);
		p.pc  = fn_8012ECA8(8, 3);
		p.i10 = 2;
		p.f14 = lbl_1_rodata_180;
		p.f18 = lbl_1_rodata_184;
		p.f1c = lbl_1_rodata_188;
		p.f20 = lbl_1_rodata_18C;
		p.f24 = lbl_1_rodata_190;
		p.i38 = 1;
		*(void**)((char*)obj + 0x3bc) = fn_1_150AC(obj, &p);
		break;
	}
	case 14: {
		SetupParams p;
		fn_1_152C0(&p);
		p.p0  = fn_8012ECA8(6, 2);
		p.p4  = 0;
		p.p8  = 0;
		p.pc  = 0;
		p.i10 = 0;
		p.f14 = lbl_1_rodata_180;
		p.f18 = lbl_1_rodata_194;
		p.f1c = lbl_1_rodata_188;
		p.f20 = lbl_1_rodata_18C;
		p.f24 = lbl_1_rodata_190;
		*(void**)((char*)obj + 0x3bc) = fn_1_150AC(obj, &p);
		break;
	}
	}
}

void fn_1_4D50(ADV_MAINMENU* obj)
{
	fn_1_3AC0(obj);
	switch (obj->mode) {
	case 5:
		fn_1_47D8(obj);
		break;
	case 6:
		fn_1_45A4(obj);
		break;
	case 7:
		fn_1_4588(obj);
		break;
	case 8:
		fn_1_4360(obj);
		break;
	case 9:
		fn_1_4344(obj);
		break;
	case 10:
		fn_1_4294(obj);
		break;
	case 11:
		fn_1_423C(obj);
		break;
	case 12:
		fn_1_4200(obj);
		break;
	case 13:
		fn_1_416C(obj);
		break;
	case 14:
		fn_1_4118(obj);
		break;
	}
}

void* fn_1_4E18(void* obj, s16 flag)
{
	if (obj != 0) {
		*(void**)((char*)obj + 0x18) = (void*)lbl_1_data_10D8;
		__destroy_arr((char*)obj + 0x94, fn_1_120E0, 0x8c, 5);
		fn_800A8620(obj, 0);
		if (flag > 0) {
			advE3Rom_pause(obj);
		}
	}
	return obj;
}

ADV_MAINMENU* fn_1_4E9C(ADV_MAINMENU* obj, void* parent)
{
	MMCtorView* v = (MMCtorView*)obj;
	fn_800A8828(obj, parent);
	*(void**)((char*)obj + 0x18) = lbl_1_data_10D8;
	__construct_array(v->sel, fn_1_12124, fn_1_120E0, 0x8c, 5);
	*(void**)((char*)obj + 0x0)  = lbl_1_data_10D4;
	*(s16*)((char*)obj + 0x1e)   = 0x3c0;
	*(s32*)((char*)obj + 0x40)   = 1;
	*(s32*)((char*)obj + 0x44)   = 1;
	*(s32*)((char*)obj + 0x3c)   = 0;
	*(void**)((char*)obj + 0x38) =
	    &lbl_1_data_DF4[*(s32*)((char*)obj + 0x3c)];
	*(s32*)((char*)obj + 0x3bc)  = 0;
	*(s32*)((char*)obj + 0x3b4)  = 1;
	*(s32*)((char*)obj + 0x3b8)  = 0;
	fn_1_120C4(&v->sel[4], 0);
	fn_1_120C4(&v->sel[4], 1);
	fn_1_120C4(&v->sel[4], 2);
	fn_1_120C4(&v->sel[4], 3);
	fn_1_4058(obj, 4, 0);
	fn_1_120C4(&v->sel[0], 0);
	fn_1_120C4(&v->sel[0], 1);
	fn_1_120C4(&v->sel[0], 2);
	fn_1_120C4(&v->sel[0], 3);
	fn_1_4058(obj, 0, 0);
	fn_1_120C4(&v->sel[2], 0);
	fn_1_120C4(&v->sel[2], 1);
	fn_1_4058(obj, 2, 0);
	fn_1_4058(obj, 1, 0);
	fn_1_4058(obj, 3, 0);
	switch (*(s32*)((char*)fn_800A8BF0(lbl_80303EC8) + 0x4)) {
	case 7:
		*(s32*)((char*)obj + 0x28) = 1;
		*(s32*)((char*)obj + 0x2c) = 1;
		*(s32*)((char*)obj + 0x60) = 5;
		*(s32*)((char*)obj + 0x64) = 0;
		*(s32*)((char*)obj + 0x68) = 0;
		*(f32*)((char*)obj + 0x34) = lbl_1_rodata_188;
		*(s32*)((char*)obj + 0x90) = 3;
		fn_1_11750(1);
		break;
	case 11:
		*(s32*)((char*)obj + 0x28) = 1;
		*(s32*)((char*)obj + 0x2c) = 1;
		*(s32*)((char*)obj + 0x60) = 5;
		*(s32*)((char*)obj + 0x64) = 0;
		*(s32*)((char*)obj + 0x68) = 0;
		*(f32*)((char*)obj + 0x34) = lbl_1_rodata_188;
		*(s32*)((char*)obj + 0x90) = 1;
		fn_1_11750(1);
		break;
	case 5:
		*(s32*)((char*)obj + 0x28) = 1;
		*(s32*)((char*)obj + 0x2c) = 1;
		*(s32*)((char*)obj + 0x60) = 6;
		*(s32*)((char*)obj + 0x64) = 0x17;
		*(s32*)((char*)obj + 0x68) = 0x19;
		*(f32*)((char*)obj + 0x34) =
		    *(f32*)((char*)lbl_1_data_DF4[*(s32*)((char*)obj + 0x3c)]
		                          .data +
		            0xbc);
		*(s32*)((char*)obj + 0x90) = 0;
		*(s32*)((char*)obj + 0x80) = 0;
		fn_1_11750(2);
		break;
	case 6:
		*(s32*)((char*)obj + 0x28) = 1;
		*(s32*)((char*)obj + 0x2c) = 1;
		*(s32*)((char*)obj + 0x60) = 6;
		*(s32*)((char*)obj + 0x64) = 0x17;
		*(s32*)((char*)obj + 0x68) = 0x19;
		*(f32*)((char*)obj + 0x34) =
		    *(f32*)((char*)lbl_1_data_DF4[*(s32*)((char*)obj + 0x3c)]
		                          .data +
		            0xbc);
		*(s32*)((char*)obj + 0x90) = 0;
		*(s32*)((char*)obj + 0x80) = 1;
		fn_1_11750(2);
		break;
	case 10:
		*(s32*)((char*)obj + 0x28) = 1;
		*(s32*)((char*)obj + 0x2c) = 1;
		*(s32*)((char*)obj + 0x60) = 8;
		*(s32*)((char*)obj + 0x64) = 0x3c;
		*(s32*)((char*)obj + 0x68) = 0x30;
		*(f32*)((char*)obj + 0x34) =
		    *(f32*)((char*)lbl_1_data_DF4[*(s32*)((char*)obj + 0x3c)]
		                          .data +
		            0x1e4);
		*(s32*)((char*)obj + 0x90) = 2;
		*(s32*)((char*)obj + 0x88) = 0;
		fn_1_11750(4);
		break;
	case 9:
		*(s32*)((char*)obj + 0x28) = 1;
		*(s32*)((char*)obj + 0x2c) = 1;
		*(s32*)((char*)obj + 0x60) = 8;
		*(s32*)((char*)obj + 0x64) = 0x3c;
		*(s32*)((char*)obj + 0x68) = 0x30;
		*(f32*)((char*)obj + 0x34) =
		    *(f32*)((char*)lbl_1_data_DF4[*(s32*)((char*)obj + 0x3c)]
		                          .data +
		            0x1e4);
		*(s32*)((char*)obj + 0x90) = 2;
		*(s32*)((char*)obj + 0x88) = 1;
		fn_1_11750(4);
		break;
	default:
		*(s32*)((char*)obj + 0x28) = 1;
		*(s32*)((char*)obj + 0x2c) = 1;
		*(s32*)((char*)obj + 0x60) = 5;
		*(s32*)((char*)obj + 0x64) = 0;
		*(s32*)((char*)obj + 0x68) = 0;
		*(f32*)((char*)obj + 0x34) = lbl_1_rodata_188;
		*(s32*)((char*)obj + 0x90) = 0;
		fn_1_11750(1);
		break;
	}
	{
		void* p = advE3Rom_resume(0x30);
		if (p) {
			fn_1_10F40(p, obj);
		}
	}
	fn_1_3B28(obj);
	fn_800A80DC(obj, 5);
	fn_800A80DC(obj, 6);
	fn_800A80DC(obj, 7);
	fn_800A80DC(obj, 0xb);
	fn_800A80DC(obj, 0xa);
	fn_800A80DC(obj, 9);
	fn_800A80DC(obj, 1);
	return obj;
}

#pragma peephole on
#pragma optimization_level 1
ADV_MAINMENU* Create(void* parent)
{
	ADV_MAINMENU* p = advE3Rom_resume(0x3c0);
	if (p) {
		return fn_1_4E9C(p, parent);
	}
	return p;
}
#pragma optimization_level reset
#pragma peephole reset

void fn_1_532C(void)
{
	lbl_1_bss_130 = 0;
	for (int j = 0; j != 10; j++) {
		for (int k = 0; k != 2; k++) {
			void* e = lbl_1_bss_E0[j][k];
			if (e != 0) {
				fn_801A45A0(lbl_1_bss_90[j][k], e);
			}
			lbl_1_bss_90[j][k] = 0;
			lbl_1_bss_E0[j][k] = 0;
		}
	}
	fn_8012CA94(lbl_1_data_E7C);
}

void fn_1_53D8(void)
{
	fn_8012CB70(lbl_1_data_E7C);
	if (*(void**)((char*)lbl_1_data_E7C + 0xc) == 0) {
		return;
	}
	for (int i = 0; i != 10; i++) {
		for (int k = 0; k != 2; k++) {
			lbl_1_bss_90[i][k] = fn_801A4BBC(
			    *(void**)((char*)lbl_1_data_E7C + 0xc), lbl_1_data_1074[i][k]);
			if (lbl_1_bss_90[i][k] != 0) {
				lbl_1_bss_E0[i][k] = *(void**)lbl_1_bss_90[i][k];
			}
		}
	}
	void* r = fn_801A4BBC(*(void**)((char*)lbl_1_data_E7C + 0xc), lbl_1_data_118C);
	if (r != 0) {
		lbl_1_bss_130 = *(void**)r;
	}
}

void* Finalize(void* obj)
{
	fn_800A8C08((const char*)lbl_80303EC8);
	fn_8014F1B0(obj);
	return obj;
}

void fn_1_550C(void) {}

void fn_1_5510(void* obj)
{
	if (obj) {
		fn_8014FFBC(obj, (void (*)(void*))fn_1_550C, 0);
	}
}

void fn_1_5544(void* obj)
{
	int counter = *(int*)((char*)obj + 0x198);
	if (counter > 0) {
		*(int*)((char*)obj + 0x198) = counter - 1;
	} else if (counter == 0) {
		*(int*)((char*)obj + 0x198) = counter - 1;
		int idx                     = *(int*)((char*)obj + 0x190);
		fn_800CB368(lbl_1_rodata_6A8[idx], -1, -1);
	}
}

void fn_1_55A4(ADV_MAINMENU* obj, int arg)
{
	fn_1_6AEC((char*)obj + 0x28, *(s32*)((char*)obj + 0x190) + arg * 0xc);
	switch (arg) {
	case 0:
	case 2:
		break;
	case 1:
	case 3: {
		int idx  = fn_1_12A0(lbl_8042C180, 0x14) == 0 ? 0 : 1;
		int mode = *(s32*)((char*)obj + 0x190);
		*(s32*)((char*)obj + 0x198) = lbl_1_rodata_6D8[mode][idx];
		break;
	}
	}
}

void fn_1_5658(ADV_MAINMENU* obj)
{
	if (*(s32*)((char*)obj + 0x13c) == -1) {
		return;
	}
	MenuEntry* t = *(MenuEntry**)((char*)fn_1_6AF4((char*)obj + 0x28) + 0x10);
	void* src    = fn_8019E8EC(t[*(s32*)((char*)obj + 0x13c)].obj);
	if (src == 0) {
		return;
	}
	void* a = *(void**)((char*)obj + 0xec);
	if (a == 0) {
		return;
	}
	void* b = *(void**)((char*)a + 0x4);
	if (b == 0) {
		return;
	}
	fn_1_56E0((char*)b + 0x10, src);
	fn_8019E880(b);
}

void fn_1_56E0(void* dst, void* src)
{
	Blk56* d = (Blk56*)dst;
	Blk56* s = (Blk56*)src;
	d->r[0]  = s->r[0];
	d->r[1]  = s->r[1];
	d->r[2]  = s->r[2];
	d->r[3]  = s->r[3];
}

void fn_1_5764(ADV_MAINMENU* obj)
{
	ADV_MAINMENU* p;
	if (*(s32*)((char*)obj + 0x138) == -1) {
		return;
	}
	MenuEntry* t = *(MenuEntry**)((char*)fn_1_6AF4((char*)obj + 0x28) + 0x10);
	void* src    = fn_8019E8EC(t[*(s32*)((char*)obj + 0x138)].obj);
	if (src == 0) {
		return;
	}
	int i = 0;
	p     = obj;
	for (; i != *(s32*)((char*)obj + 0x134); i++) {
		void* a = *(void**)((char*)p + 0xc4);
		if (a != 0) {
			void* b = *(void**)((char*)a + 4);
			if (b != 0) {
				fn_1_56E0((char*)b + 0x10, src);
				fn_8019E880(b);
			}
		}
		void* c = *(void**)((char*)p + 0xd8);
		if (c != 0) {
			void* d = *(void**)((char*)c + 4);
			if (d != 0) {
				fn_1_56E0((char*)d + 0x10, src);
				fn_8019E880(d);
			}
		}
		p = (ADV_MAINMENU*)((char*)p + 4);
	}
}

void fn_1_5844(ADV_MAINMENU* obj, f32 rate)
{
	obj->unk_0x128 = rate;
	if (lbl_1_rodata_738 <= rate) {
		obj->unk_0x12c = lbl_1_rodata_73C;
	} else if (rate <= lbl_1_rodata_740) {
		obj->unk_0x12c = lbl_1_rodata_744;
	} else {
		obj->unk_0x12c = lbl_1_rodata_748;
	}
}

void fn_1_58B4(ADV_MAINMENU* obj, Vec3f* v)
{
	Vec3f tmp;
	fn_1_5994(&tmp, v);
	fn_1_5994(&obj->vec_0x10c, &tmp);
	obj->vec_0x118.x = tmp.x - obj->vec_0x100.x;
	obj->vec_0x118.y = tmp.y - obj->vec_0x100.y;
	obj->vec_0x118.z = tmp.z - obj->vec_0x100.z;
	if (fn_801991B4(&obj->vec_0x118) < lbl_1_rodata_738) {
		obj->vec_0x118.x = lbl_1_rodata_748;
		obj->vec_0x118.y = lbl_1_rodata_748;
		obj->vec_0x118.z = lbl_1_rodata_748;
	} else {
		fn_801990E0(&obj->vec_0x118, &obj->vec_0x118);
	}
	obj->vec_0x118.x = lbl_1_rodata_73C * obj->vec_0x118.x;
	obj->vec_0x118.y = lbl_1_rodata_73C * obj->vec_0x118.y;
	obj->vec_0x118.z = lbl_1_rodata_73C * obj->vec_0x118.z;
}

void fn_1_5994(Vec3f* dst, Vec3f* src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

void fn_1_59B0(ADV_MAINMENU* obj)
{
	Vec3f d;
	d.x = obj->vec_0x10c.x - obj->vec_0x100.x;
	d.y = obj->vec_0x10c.y - obj->vec_0x100.y;
	d.z = obj->vec_0x10c.z - obj->vec_0x100.z;
	if (fn_801991B4(&d) <= lbl_1_rodata_73C) {
		fn_1_5994(&obj->vec_0x100, &obj->vec_0x10c);
	} else {
		obj->vec_0x100.x = obj->vec_0x100.x + obj->vec_0x118.x;
		obj->vec_0x100.y = obj->vec_0x100.y + obj->vec_0x118.y;
		obj->vec_0x100.z = obj->vec_0x100.z + obj->vec_0x118.z;
	}
	f32 base = obj->unk_0x124;
	f32 sum  = base + obj->unk_0x12c;
	if (lbl_1_rodata_748 <= obj->unk_0x12c) {
		if (obj->unk_0x128 <= sum
		    && sum <= obj->unk_0x128 + obj->unk_0x12c) {
			obj->unk_0x124 = obj->unk_0x128;
			obj->unk_0x12c = lbl_1_rodata_748;
		} else {
			obj->unk_0x124 = sum;
		}
	} else {
		if (obj->unk_0x128 >= sum
		    && sum >= obj->unk_0x128 + obj->unk_0x12c) {
			if (obj->unk_0x128 <= sum && sum <= base) {
				obj->unk_0x124 = obj->unk_0x128;
				obj->unk_0x12c = lbl_1_rodata_748;
			} else {
				obj->unk_0x124 = sum;
			}
		}
	}
}

void fn_1_5B08(ADV_MAINMENU* obj)
{
	for (int i = 0; i != 5; i++) {
		void* o = obj->subobjs[0];
		if (o != 0) {
			void* c = *(void**)((char*)o + 4);
			if (c != 0) {
				fn_8019ED68(c, (void*)lbl_80239984, obj->unk_0x124, 0);
				fn_8019EB94(c, &obj->vec_0x100, 2);
			}
		}
	}
}

void fn_1_5B9C(ADV_MAINMENU* obj)
{
	void* p;
	for (u32 i = 0; i != 16; i++) {
		p = obj->subobjs[i];
		if (p) {
			fn_8015BBF8(fn_8015BD78(p), p);
			fn_80150958(obj->subobjs[i]);
			obj->subobjs[i] = 0;
		}
	}
}

void fn_1_5C1C(ADV_MAINMENU* obj, int row)
{
	void** tbl = &lbl_1_bss_230[row * 12];
	for (int i = 0; i != 12; i++) {
		void* entry = tbl[i];
		if (entry != 0) {
			obj->subobjs[i] = fn_80150588(entry);
			if (i == 0) {
				fn_8003C640(obj->subobjs[i]);
			}
			fn_8015BB08(fn_800A943C((const char*)lbl_80303EC8), obj->subobjs[i]);
		} else {
			obj->subobjs[i] = 0;
		}
	}
}

#pragma force_active reset

// clang-format on
} // extern "C"
