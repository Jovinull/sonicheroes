#include "types.h"

// ADV_FILESELECT - the save/load file-select advertise object (REL module 1).
//
// Semantic reference is the PS2 debug build's ADV_FILESELECT class (28
// methods); the GameCube release inlines a couple of helper sub-objects into
// this same translation unit, so ~31 functions are emitted here. Names are
// taken from the PS2 mangled symbols where the mapping is clear; the module's
// own symbol table is unmangled, so everything links extern "C".
//
// Struct offsets are GameCube ground truth (the PS2 layout differs); the PS2
// reference only supplies logic and names. The vtable is emitted into .data at
// 0x87C and installed at object+0x18 by the constructor.
//
// Field access is written through offset macros because the object is large
// (>0x700 bytes) with many still-unnamed fields; the codegen is identical to a
// named struct member. Every method names its object pointer `t`.

struct Entry350 {
	u32 a, b, c;
};

// Only the two index-addressed arrays are given real member types so their
// element accesses emit the this-based (add base,index / lwz disp) form the
// original uses; every scalar field is still reached through the offset macros.
struct FS {
	char _pad00[0x80];
	s32 arr80[4];              // 0x80
	char _pad90[0x350 - 0x90]; // 0x90 onward
	Entry350 arr350[16];       // 0x350
	char _tail[0x400];
};

#define w(o)  (*(s32*)((char*)t + (o)))
#define uw(o) (*(u32*)((char*)t + (o)))
#define fl(o) (*(f32*)((char*)t + (o)))
#define pp(o) (*(void**)((char*)t + (o)))

struct Pair {
	u32 a, b;
};
struct FPair {
	f32 x, y;
};

// Tables that live outside this translation unit's range.
extern u32 lbl_1_rodata_E4[]; // {u32,u32} pairs indexed by menu index
extern u32 lbl_1_rodata_C4[]; // {u32,u32} pairs indexed by menu index
extern f32 lbl_1_rodata_17C[];
extern u32 lbl_1_data_F70[]; // per-menu pointer table
extern u32 lbl_1_data_F0C[]; // per-menu pointer table
extern u8 lbl_1_data_DF4[];  // array of 0x68-byte slots
extern void* lbl_1_data_87C; // vtable

// View of a lbl_1_data_DF4 slot. Indexing this array (rather than
// `&lbl_1_data_DF4[idx * 0x68]`) makes MWCC materialise the table base first,
// then compute the element index, matching the original's addressing order.
struct DF4Slot {
	u8 _0[8];
	void* p8; // 0x8: pointer to a float table
	u8 _rest[0x68 - 0xc];
};

extern "C" void fn_800A8264(FS*);
extern "C" FS* advE3Rom_resume(s32 size);
extern "C" FS* fn_1_3714(FS* obj, void* parent, int mode);

// ---------------------------------------------------------------------------

extern "C" void fn_1_4058(FS* t, int idx, u32 val);
extern "C" void fn_1_4028(FS* t, int idx);
extern "C" void fn_1_42D8(FS* t, int idx);
extern "C" void fn_1_3F3C(FS* t);
extern "C" void fn_1_3FDC(FS* t);
extern "C" int fn_1_11FFC(void* p, int a);
extern "C" void fn_800B52E8(void* snd, u32 id, int a, int b);
extern "C" int fn_800A9398(void* obj, int a);
extern "C" void fn_800A8174(FS* t, u32 arg);
extern void* lbl_8042C388;
extern u32 lbl_1_rodata_12C[];
extern u8 lbl_80303EC8;

// 0x4360 - selection controller: read the pad, dispatch the current sub-menu.

extern "C" int fn_1_11C8C(void* p, int a);
extern "C" void fn_80014154(void);
extern u32 lbl_1_rodata_134[];
extern "C" void fn_1_3F0C(FS* t);
extern "C" void fn_1_3EDC(FS* t);
extern "C" void fn_1_3C40(FS* t);

// 0x45A4 - load-slot controller: read the pad, dispatch the current sub-menu.

extern "C" void fn_1_11704(void);
extern "C" void fn_1_11750(int i);
extern u32 lbl_1_rodata_10C[];
extern u32 lbl_1_rodata_11C[];
extern u32 lbl_1_rodata_B0[];

// 0x47D8 - save-slot controller: read the pad, dispatch the current sub-menu.

// 0x4344 - set state (48=1, 40=7, 2c=2).

// 0x4294

// 0x423C

// 0x4200

extern "C" void fn_1_3FDC(FS* t);

// 0x3EDC

// 0x3F0C

// 0x4028

extern "C" void fn_1_40FC(u32* dst, u32* src);

// 0x4058

// 0x40FC - three-word copy (Vec3-style). Defined after its caller so MWCC
// emits a real bl at the call site instead of inlining it.

extern "C" int fn_1_146C0(void*);

// 0x4118

// 0x354C - Disp: draw unless the selection is idle.

// 0x3884 - Create: allocate and construct (auto mode).

// 0x38C8 - CreateNoAuto: allocate and construct (no-auto mode).

// 0x42D8 - advance the highlighted value toward a target.

// Base-class helpers and sibling exec handlers (defined elsewhere in module 1).
extern "C" void fn_800A8C00(void* obj, u8 val);
extern "C" void* fn_80116D2C(void* arg);
extern "C" void fn_800A8620(FS* t, int flag);
extern "C" void advE3Rom_pause(void* t);
extern u8 lbl_803E774C;
extern u8 lbl_80303EC8;

// 0x368C - deleting destructor.

extern "C" void fn_1_131C(FS* t, int i);
extern "C" void fn_1_30A8(FS* t);
extern "C" void fn_1_2F40(FS* t);
extern "C" void fn_1_2AC8(FS* t);
extern "C" void fn_1_293C(FS* t);
extern "C" void fn_1_2884(FS* t);
extern "C" void fn_1_27C4(FS* t);
extern "C" void fn_1_2760(FS* t);
extern "C" void fn_1_2688(FS* t);
extern "C" void fn_1_24FC(FS* t);
extern "C" void fn_1_2390(FS* t);
extern "C" void fn_1_2234(FS* t);
extern "C" void fn_1_2164(FS* t);

// 0x358C - OnExec: tick sub-tasks then dispatch on the current state.

extern "C" void fn_800A8828(FS* t, void* parent);
extern "C" void fn_800A80DC(FS* t, int i);
extern "C" void fn_1_11750(int i);
extern "C" void* fn_80126200(FS* t);
extern "C" void fn_80124898(void* h);
extern "C" int fn_80116B68(void* arg);
extern "C" void fn_1_2158(FS* t);
extern void* lbl_1_data_878;
extern u8 lbl_1_data_6A4;

// 0x3714 - constructor (parent object, file-select mode).

extern "C" void fn_800A96B0(void* obj, int a, int b);
extern "C" void fn_800191F8(void* obj, int a, int b);
extern "C" void fn_8001938C(void* obj);
extern "C" void fn_8001934C(void* obj, int a, int b);
extern "C" void fn_8001936C(void* obj, int a, int b);
extern u8 lbl_8029C310;

// 0x3C40

extern s32 lbl_1_rodata_144[];

// 0x3D30 - commit the chosen slot and rebuild the selection window.

// 0x3FDC - refresh the option strings for the current menu (defined last so
// no caller inlines it).

extern u32 lbl_802408F8[];
extern s32 lbl_8029BBD0[];

// 0x3AC0 - count how many of two save slots are occupied; flag >= 2.

// 0x3F3C

// 0x4588 - set state (48=1, 40=0xb, 2c=2).

extern "C" void fn_1_3D30(FS* t, int flag);
extern "C" void fn_80014158(void);

// 0x416C - react to the memory-card query result.

extern u32 lbl_1_bss_48[];
extern void* lbl_1_bss_20[];
extern u32 lbl_1_bss_34[];
extern u8 lbl_1_data_730;
extern "C" void fn_801A45A0(void* a, u32 b);
extern "C" void fn_8012CA94(void* p);

// 0x390C - reset the module's shared file handle table.

extern "C" void fn_8012CB70(void* p);
extern "C" void* fn_801A4BBC(void* h, u32 arg);
extern u32 lbl_1_data_798[];
extern u32 lbl_1_data_82C[];

struct H730 {
	u8 _pad[0xc];
	void* handle;
};

// 0x39D0 - (re)load the shared file handles from the memory card.

extern "C" void advE3Rom_setFlag(void* h);
extern "C" int fn_80125708(void* win);
extern "C" int fn_801257D0(void* win);
extern "C" int fn_80125990(void* win);
extern "C" int fn_80125900(void* win);
extern "C" int fn_801255DC(void* win);
extern "C" int fn_8012554C(void* win);
extern "C" char* fn_8012ECA8(int a, int id);
extern "C" void fn_8012EC18(char* buf, char* fmt, ...);
extern "C" void fn_1_1E2C(FS* t, char* msg);
extern "C" void fn_1_1F70(FS* t, char* a, char* b, char* c, int d, int e, int f, int g, int h);
extern "C" void* fn_1_150AC(FS* t, void* m);
extern "C" void fn_1_152C0(void* m);
extern "C" void fn_80116B60(void* p, int a);
extern "C" void fn_800A8C78(void* p);

extern const f32 lbl_1_rodata_74; // 0
extern const f32 lbl_1_rodata_78; // 93
extern const f32 lbl_1_rodata_80; // 454
extern const f32 lbl_1_rodata_84; // 160
extern const f32 lbl_1_rodata_AC; // 100

// The message-window descriptor that cases 16/17 build on the stack and hand
// to fn_1_150AC; case 19 uses a scratch string buffer instead.
struct Msg {
	/*0x00*/ u32 f00; // constructed by fn_1_152C0
	/*0x04*/ char* f04;
	/*0x08*/ char* f08;
	/*0x0c*/ char* f0c;
	/*0x10*/ s32 f10;
	/*0x14*/ f32 f14;
	/*0x18*/ f32 f18;
	/*0x1c*/ f32 f1c;
	/*0x20*/ f32 f20;
	/*0x24*/ f32 f24;
	/*0x28*/ char pad28[0x18];
	/*0x40*/ s32 f40;
};

// 0x3130 - result-window dispatcher: tear down the pending window, then act on
// the exec state (5..21) via a jumptable. States 7/13/14/18 (and anything out
// of range) fall through to the shared exit.

extern "C" int fn_80117274(void* p, int n);
extern void* lbl_1_bss_90[];
extern u32 lbl_1_bss_130[];

// 0x3B28 - initialize per-slot status flags and free stale handles.

#pragma force_active on
#pragma dont_inline on

extern "C" void fn_1_3130(FS* t, int state)
{
	Msg mi;
	Msg mj;
	char buf[0x3fc];

	void* h = pp(0x8c);
	if (h != NULL) {
		advE3Rom_setFlag(h);
		pp(0x8c) = NULL;
	}
	w(0xa8) = 0;

	switch (state) {
		case 6:
			if (fn_80125708(pp(0x84)) == 0) {
				w(0x28) = 0x12;
			}
			break;
		case 8:
			if (fn_801257D0(pp(0x84)) == 0) {
				w(0x28) = 0x12;
			}
			fn_1_1E2C(t, fn_8012ECA8(0, 6));
			break;
		case 9:
			if (fn_80125990(pp(0x84)) == 0) {
				w(0x28) = 0x12;
			}
			fn_1_1E2C(t, fn_8012ECA8(0, 0x33));
			pp(0xac) = fn_8012ECA8(0, 0x36);
			break;
		case 10:
			if (fn_80125990(pp(0x84)) == 0) {
				w(0x28) = 0x12;
			}
			fn_1_1E2C(t, fn_8012ECA8(0, 0x33));
			pp(0xac) = NULL;
			break;
		case 11:
			if (fn_80125900(pp(0x84)) == 0) {
				w(0x28) = 0x12;
			}
			fn_1_1E2C(t, fn_8012ECA8(0, 0x33));
			pp(0xac) = NULL;
			break;
		case 12:
			fn_1_1F70(
			    t, fn_8012ECA8(0, 0x46), fn_8012ECA8(0, 0x50), fn_8012ECA8(0, 0x51), 0, 0, 0, 0, 0);
			w(0x2c) = 0xc;
			break;
		case 15:
			if (fn_801255DC(pp(0x84)) == 0) {
				w(0x28) = 0x12;
			}
			fn_1_1E2C(t, fn_8012ECA8(0, 0x1b));
			break;
		case 19:
			if (fn_8012554C(pp(0x84)) == 0) {
				w(0x28) = 0x12;
			}
			{
				int slot = fn_80116B68(&lbl_803E774C);
				fn_8012EC18(buf, fn_8012ECA8(0, 0xe), slot + 1);
				fn_1_1E2C(t, buf);
				pp(0xac) = fn_8012ECA8(0, 0x11);
			}
			break;
		case 16:
			fn_1_152C0(&mi);
			mi.f04   = fn_8012ECA8(0, 0x5c);
			mi.f08   = fn_8012ECA8(0, 0x5d);
			mi.f0c   = fn_8012ECA8(0, 0x5e);
			mi.f10   = 2;
			mi.f14   = lbl_1_rodata_78;
			mi.f18   = lbl_1_rodata_AC;
			mi.f1c   = lbl_1_rodata_74;
			mi.f20   = lbl_1_rodata_80;
			mi.f24   = lbl_1_rodata_84;
			mi.f40   = 0;
			pp(0x8c) = fn_1_150AC(t, &mi);
			break;
		case 17:
			fn_1_152C0(&mj);
			mj.f04   = fn_8012ECA8(0, 0x5c);
			mj.f08   = fn_8012ECA8(0, 0x5e);
			mj.f10   = 0;
			mj.f14   = lbl_1_rodata_78;
			mj.f18   = lbl_1_rodata_AC;
			mj.f1c   = lbl_1_rodata_74;
			mj.f20   = lbl_1_rodata_80;
			mj.f24   = lbl_1_rodata_84;
			mj.f40   = 0;
			pp(0x8c) = fn_1_150AC(t, &mj);
			break;
		case 5:
			fl(0x34) = lbl_1_rodata_74;
			break;
		case 20:
			w(0x48) = 0;
			w(0x2c) = 2;
			fn_80116B60(&lbl_803E774C, -2);
			break;
		case 21:
			w(0x48) = 0;
			w(0x2c) = 2;
			fn_800A8C78(&lbl_80303EC8);
			break;
	}
}

extern "C" void fn_1_354C(FS* t)
{
	if (t->arr80[0] != 0 || (w(0x28) != 5 && w(0x28) != 0xb)) {
		fn_800A8264(t);
	}
}

extern "C" void fn_1_358C(FS* t)
{
	int i = 0;
	do {
		fn_1_131C(t, i);
		i++;
	} while (i != 5);

	switch (w(0x28)) {
		case 5:
			fn_1_30A8(t);
			break;
		case 6:
			fn_1_2F40(t);
			break;
		case 7:
			fn_1_2AC8(t);
			break;
		case 8:
			fn_1_293C(t);
			break;
		case 12:
			fn_1_2884(t);
			break;
		case 13:
			fn_1_27C4(t);
			break;
		case 14:
			fn_1_2760(t);
			break;
		case 15:
			fn_1_2688(t);
			break;
		case 9:
		case 10:
		case 11:
			fn_1_24FC(t);
			break;
		case 19:
			fn_1_2390(t);
			break;
		case 16:
			fn_1_2234(t);
			break;
		case 17:
			fn_1_2164(t);
			break;
	}
}

extern "C" FS* fn_1_368C(FS* t, s16 free)
{
	if (t != NULL) {
		u8 v;
		pp(0x18) = &lbl_1_data_87C;
		v        = *((u8*)fn_80116D2C(&lbl_803E774C) + 0x22);
		fn_800A8C00(&lbl_80303EC8, v);
		fn_800A8620(t, 0);
		if (free > 0) {
			advE3Rom_pause(t);
		}
	}
	return t;
}

extern "C" FS* fn_1_3714(FS* t, void* parent, int mode)
{
	fn_800A8828(t, parent);
	pp(0x18)                 = &lbl_1_data_87C;
	pp(0x0)                  = lbl_1_data_878;
	*(u16*)((char*)t + 0x1e) = 0xb0;
	if (mode == 0) {
		w(0x40) = 4;
		w(0x44) = 1;
		w(0x48) = 1;
		fn_800A80DC(t, 1);
		fn_800A80DC(t, 4);
	} else {
		w(0x40) = 7;
		w(0x44) = 7;
		w(0x48) = 1;
		fn_800A80DC(t, 7);
		fn_1_11750(5);
	}
	w(0x28)     = 0;
	w(0x2c)     = 5;
	pp(0x38)    = &lbl_1_data_6A4;
	t->arr80[0] = mode;
	pp(0x84)    = fn_80126200(t);
	if (pp(0x84) != NULL) {
		fn_80124898(pp(0x84));
	}
	w(0x88) = 0;
	w(0x90) = 0;
	w(0x94) = 0;
	w(0x98) = 0;
	w(0xa8) = 0;
	w(0x8c) = 0;
	w(0xac) = 0;
	w(0xa4) = fn_80116B68(&lbl_803E774C);
	{
		int r = fn_80116B68(&lbl_803E774C);
		switch (r) {
			case -2:
			case -1:
				w(0xa0) = 0;
				break;
			default:
				w(0xa0) = fn_80116B68(&lbl_803E774C);
				break;
		}
	}
	fn_1_2158(t);
	return t;
}

#pragma peephole on
#pragma optimization_level 1
extern "C" FS* fn_1_3884(void* parent)
{
	FS* obj = advE3Rom_resume(0xb0);
	return obj ? fn_1_3714(obj, parent, 1) : obj;
}
#pragma optimization_level reset
#pragma peephole reset

#pragma peephole on
#pragma optimization_level 1
extern "C" FS* fn_1_38C8(void* parent)
{
	FS* obj = advE3Rom_resume(0xb0);
	return obj ? fn_1_3714(obj, parent, 0) : obj;
}
#pragma optimization_level reset
#pragma peephole reset

extern "C" void fn_1_390C(void)
{
	int i;
	for (i = 0; i != 15; i++) {
		lbl_1_bss_48[i] = 0;
	}
	for (i = 0; i != 5; i++) {
		if (lbl_1_bss_34[i] != 0) {
			fn_801A45A0(lbl_1_bss_20[i], lbl_1_bss_34[i]);
		}
		lbl_1_bss_20[i] = NULL;
		lbl_1_bss_34[i] = 0;
	}
	fn_8012CA94(&lbl_1_data_730);
}

extern "C" void fn_1_39D0(void)
{
	H730* p;
	fn_1_11750(5);
	fn_8012CB70(&lbl_1_data_730);
	p = (H730*)&lbl_1_data_730;
	if (p->handle != 0) {
		int i;
		for (i = 0; i != 5; i++) {
			lbl_1_bss_20[i] = fn_801A4BBC(p->handle, lbl_1_data_798[i]);
			if (lbl_1_bss_20[i] != 0) {
				lbl_1_bss_34[i] = *(u32*)lbl_1_bss_20[i];
			}
		}
		for (i = 0; i != 15; i++) {
			void* h = fn_801A4BBC(p->handle, lbl_1_data_82C[i]);
			if (h != 0) {
				lbl_1_bss_48[i] = *(u32*)h;
			}
		}
	}
}

extern "C" void fn_1_3AC0(FS* t)
{
	int i;
	int count = 0;
	u32* pf   = lbl_802408F8;
	s32* pb   = lbl_8029BBD0;
	for (i = 0; i < 2; i++, pf++) {
		if (pb[*pf] != 0) {
			count++;
		}
	}
	w(0x3b4) = count >= 2;
}

extern "C" void fn_1_3B28(FS* t)
{
	int i;
	void* a  = fn_80116D2C(&lbl_803E774C);
	u8* q    = (u8*)fn_80116D2C(&lbl_803E774C) + 0x3c;
	w(0x38c) = 1;
	w(0x390) = 1;
	w(0x394) = 1;
	w(0x398) = 1;
	w(0x39c) = 1;
	if (*((u8*)a + 0x22) != 0) {
		w(0x3a0) = 1;
	} else {
		w(0x3a0) = 0;
	}
	if (fn_80117274(q, 5) == 0x8d) {
		w(0x3a4) = 1;
	} else {
		w(0x3a4) = 0;
	}
	w(0x3a8) = 1;
	w(0x3ac) = 1;
	w(0x3b0) = 1;
	for (i = 0; i != 10; i++) {
		// Written `t + i*4 + 0x38c` (not `t + (0x38c + i*4)`) so MWCC
		// strength-reduces `t + i*4` into the induction pointer and folds
		// 0x38c into the load displacement, matching the original.
		if (*(s32*)((char*)t + i * 4 + 0x38c) == 0) {
			fn_801A45A0(lbl_1_bss_90[i * 2], lbl_1_bss_130[0]);
			fn_801A45A0(lbl_1_bss_90[i * 2 + 1], lbl_1_bss_130[0]);
		}
	}
}

extern "C" void fn_1_3C40(FS* t)
{
	fn_800A96B0(&lbl_80303EC8, 0x28, 0);
	fn_800191F8(&lbl_8029C310, 0, 0);
	fn_800A96B0(&lbl_80303EC8, 0x27, 0);
	fn_800A96B0(&lbl_80303EC8, 0x18, 0);
	fn_8001938C(&lbl_8029C310);
	fn_8001934C(&lbl_8029C310, 0, 0);
	fn_8001936C(&lbl_8029C310, 0, 0x19);
	fn_800A96B0(&lbl_80303EC8, 0x27, 0);
	w(0x48)  = 1;
	w(0x40)  = 0xf;
	w(0x3b8) = 1;
	fn_1_3FDC(t);
	fn_800A96B0(&lbl_80303EC8, 0x2a, 4);
}

extern "C" void fn_1_3D30(FS* t, int flag)
{
	int i;
	if (flag != 0) {
		i = 0;
		do {
			if (lbl_1_rodata_144[i] == *(s32*)((char*)fn_80116D2C(&lbl_803E774C) + 0x6f8)) {
				i++;
				break;
			}
			i++;
		} while (i < 0xeU);
		if (*(s32*)((char*)fn_80116D2C(&lbl_803E774C) + 0x6fc) < 0) {
			i = 0;
		}
	} else {
		i = 0;
	}
	if (i >= 0xeU) {
		i = 0;
	}
	if (i == 0) {
		*(s32*)((char*)fn_80116D2C(&lbl_803E774C) + 0x6fc) = 0;
	}
	fn_800A96B0(&lbl_80303EC8, 0x28, 2);
	fn_800191F8(&lbl_8029C310, 0, 0);
	fn_800A96B0(&lbl_80303EC8, 0x27, 0);
	fn_800A96B0(&lbl_80303EC8, 0x18, 0);
	fn_8001938C(&lbl_8029C310);
	fn_8001934C(&lbl_8029C310, 0, 0);
	{
		int j = 0;
		while (i < 0xeU) {
			fn_8001936C(&lbl_8029C310, j++, lbl_1_rodata_144[i]);
			i++;
		}
	}
	w(0x48)  = 1;
	w(0x40)  = 0xf;
	w(0x3b8) = 1;
	fn_1_3FDC(t);
	fn_800A96B0(&lbl_80303EC8, 0x2a, 4);
}

extern "C" void fn_1_3EDC(FS* t)
{
	w(0x48) = 1;
	w(0x40) = 6;
	fn_1_3FDC(t);
}

extern "C" void fn_1_3F0C(FS* t)
{
	w(0x48) = 1;
	w(0x40) = 5;
	fn_1_3FDC(t);
}

extern "C" void fn_1_3F3C(FS* t)
{
	w(0x2c)     = 1;
	w(0x60)     = 0xc;
	w(0x64)     = lbl_1_rodata_E4[uw(0x90) * 2];
	w(0x68)     = lbl_1_rodata_E4[uw(0x90) * 2 + 1];
	t->arr80[0] = 0;
	w(0x88)     = 0;
	switch (w(0x28)) {
		case 8:
			w(0x90) = 2;
			goto mode_set;
		case 6:
		default:
			break;
	}
	w(0x90) = 0;
mode_set:
	fn_1_11750(1);
}

extern "C" void fn_1_3FDC(FS* t)
{
	int i    = uw(0x90);
	u32 sel  = t->arr80[i];
	w(0x2c)  = 1;
	w(0x60)  = 0xb;
	w(0x64)  = ((Pair*)lbl_1_data_F70[i])[sel].a;
	Pair* pr = (Pair*)lbl_1_data_F70[i];
	w(0x68)  = pr[sel].b;
}

extern "C" void fn_1_4028(FS* t, int idx)
{
	void* p = pp(0x38);
	if (p == NULL) {
		return;
	}
	u32 i    = t->arr350[idx].a;
	f32* tbl = *(f32**)((char*)p + 8);
	// Codegen-shaping no-op (decomp-permuter): the short-circuit chain defers
	// the tbl load so it lands in the arr350-address register late, matching
	// the original's schedule; without it MWCC hoists the load into p's reg.
	(void)((t && t) && t);
	fl(0x34) = tbl[i * 2 + 1];
}

extern "C" void fn_1_4058(FS* t, int idx, u32 val)
{
	u8* p = (u8*)lbl_1_data_F0C[idx];
	if (p != NULL) {
		DF4Slot* d = (DF4Slot*)lbl_1_data_DF4;
		f32* tbl   = (f32*)d[uw(0x3c)].p8;
		fl(0x34)   = tbl[((u32*)(p + val * 0xc))[0] * 2 + 1];
		fn_1_40FC((u32*)&t->arr350[idx], (u32*)(p + val * 0xc));
	}
	t->arr80[idx] = val;
}

extern "C" void fn_1_40FC(u32* dst, u32* src)
{
	dst[0] = src[0];
	dst[1] = src[1];
	dst[2] = src[2];
}

extern "C" void fn_1_4118(FS* t)
{
	void* p = pp(0x3bc);
	if (p != NULL) {
		if (fn_1_146C0(p) == 1) {
			w(0x2c) = 5;
		}
	} else {
		w(0x2c) = 5;
	}
}

extern "C" void fn_1_416C(FS* t)
{
	void* p = pp(0x3bc);
	if (p != NULL) {
		switch (fn_1_146C0(p)) {
			case 1:
				fn_1_3D30(t, 0);
				break;
			case 2:
				fn_1_3D30(t, 1);
				break;
			case 3:
				fn_80014158();
				w(0x2c) = 6;
				break;
		}
	} else {
		w(0x2c) = 6;
	}
}

extern "C" void fn_1_4200(FS* t)
{
	w(0x3c)  = 0;
	pp(0x38) = &lbl_1_data_DF4[uw(0x3c) * 0x68];
	w(0x2c)  = 1;
	w(0x60)  = 5;
	w(0x64)  = 0;
	w(0x68)  = 1;
}

extern "C" void fn_1_423C(FS* t)
{
	w(0x2c) = 1;
	if (w(0x3b8) != 0) {
		w(0x60) = 3;
	} else {
		w(0x60) = 2;
	}
	w(0x64) = lbl_1_rodata_E4[uw(0x90) * 2];
	w(0x68) = lbl_1_rodata_E4[uw(0x90) * 2 + 1];
}

extern "C" void fn_1_4294(FS* t)
{
	w(0x2c) = 1;
	w(0x60) = uw(0x90) + 6;
	w(0x64) = lbl_1_rodata_C4[uw(0x90) * 2];
	w(0x68) = lbl_1_rodata_C4[uw(0x90) * 2 + 1];
}

extern "C" void fn_1_42D8(FS* t, int idx)
{
	DF4Slot* d = (DF4Slot*)lbl_1_data_DF4;
	fl(0x34)   = fl(0x34) + lbl_1_rodata_17C[0];
	f32* p     = (f32*)d[uw(0x3c)].p8 + 1;
	if (p[t->arr350[idx].c * 2] <= fl(0x34)) {
		fl(0x34) = p[t->arr350[idx].b * 2];
	}
}

extern "C" void fn_1_4344(FS* t)
{
	w(0x48) = 1;
	w(0x40) = 7;
	w(0x2c) = 2;
}

extern "C" void fn_1_4360(FS* t)
{
	int r = fn_1_11FFC((char*)t + 0x1ac, -1);
	if (r != -1 && r != w(0x88)) {
		if (lbl_8042C388 != NULL) {
			fn_800B52E8(lbl_8042C388, 0xE007, 0, 0);
		}
		fn_1_4058(t, 2, r);
		fn_1_4028(t, 2);
	} else {
		fn_1_42D8(t, 2);
		switch (fn_800A9398(&lbl_80303EC8, -1)) {
			case 0:
				break;
			case 3:
				if (((s32*)((char*)t + 0x3ac))[uw(0x88)] != 0) {
					fn_800A8174(t, lbl_1_rodata_12C[uw(0x88)]);
				} else {
					if (lbl_8042C388 != NULL) {
						fn_800B52E8(lbl_8042C388, 0xE018, 0, 0);
					}
				}
				break;
			case 1:
				if (lbl_8042C388 != NULL) {
					fn_800B52E8(lbl_8042C388, 0xE009, 0, 0);
				}
				fn_1_3F3C(t);
				break;
			case 2:
				if (((s32*)((char*)t + 0x3ac))[uw(0x88)] != 0) {
					if (lbl_8042C388 != NULL) {
						fn_800B52E8(lbl_8042C388, 0xE008, 0, 0);
					}
					switch (w(0x88)) {
						case 1:
							w(0x48) = 1;
							w(0x40) = 9;
							fn_1_3FDC(t);
							break;
						case 0:
							w(0x48) = 1;
							w(0x40) = 0xa;
							fn_1_3FDC(t);
							break;
					}
				} else {
					if (lbl_8042C388 != NULL) {
						fn_800B52E8(lbl_8042C388, 0xE018, 0, 0);
					}
				}
				break;
		}
	}
}

extern "C" void fn_1_4588(FS* t)
{
	w(0x48) = 1;
	w(0x40) = 0xb;
	w(0x2c) = 2;
}

extern "C" void fn_1_45A4(FS* t)
{
	int r = fn_1_11C8C((char*)t + 0x94, -1);
	if (r != -1 && r != w(0x80)) {
		if (lbl_8042C388 != NULL) {
			fn_800B52E8(lbl_8042C388, 0xE007, 0, 0);
		}
		fn_1_4058(t, 0, r);
		fn_1_4028(t, 0);
	} else {
		fn_1_42D8(t, 0);
		switch (fn_800A9398(&lbl_80303EC8, -1)) {
			case 0:
				break;
			case 3:
				if (((s32*)((char*)t + 0x39c))[uw(0x80)] != 0) {
					fn_800A8174(t, lbl_1_rodata_134[uw(0x80)]);
				} else {
					if (lbl_8042C388 != NULL) {
						fn_800B52E8(lbl_8042C388, 0xE018, 0, 0);
					}
				}
				break;
			case 1:
				if (lbl_8042C388 != NULL) {
					fn_800B52E8(lbl_8042C388, 0xE009, 0, 0);
				}
				fn_1_3F3C(t);
				break;
			case 2:
				if (((s32*)((char*)t + 0x39c))[uw(0x80)] != 0) {
					if (lbl_8042C388 != NULL) {
						fn_800B52E8(lbl_8042C388, 0xE008, 0, 0);
					}
					switch (w(0x80)) {
						case 0:
							fn_1_3F0C(t);
							break;
						case 1:
							fn_1_3EDC(t);
							break;
						case 2:
							w(0x2c) = 0xd;
							break;
						case 3:
							fn_80014154();
							fn_1_3C40(t);
							break;
					}
				} else {
					if (lbl_8042C388 != NULL) {
						fn_800B52E8(lbl_8042C388, 0xE018, 0, 0);
					}
				}
				break;
		}
	}
}

extern "C" void fn_1_47D8(FS* t)
{
	int r = fn_1_11C8C((char*)t + 0x2c4, -1);
	if (r != -1 && r != w(0x90)) {
		if (lbl_8042C388 != NULL) {
			fn_800B52E8(lbl_8042C388, 0xE007, 0, 0);
		}
		fn_1_4058(t, 4, r);
		fn_1_4028(t, 4);
		fn_1_11704();
	} else {
		fn_1_42D8(t, 4);
		switch (fn_800A9398(&lbl_80303EC8, -1)) {
			case 0:
				break;
			case 3:
				if (((s32*)((char*)t + 0x38c))[uw(0x90)] != 0) {
					if (w(0x3b4) != 0) {
						fn_800A8174(t, lbl_1_rodata_10C[uw(0x90)]);
					} else {
						fn_800A8174(t, lbl_1_rodata_11C[uw(0x90)]);
					}
				} else {
					if (lbl_8042C388 != NULL) {
						fn_800B52E8(lbl_8042C388, 0xE018, 0, 0);
					}
				}
				break;
			case 1:
				if (lbl_8042C388 != NULL) {
					fn_800B52E8(lbl_8042C388, 0xE009, 0, 0);
				}
				w(0x48) = 0;
				w(0x2c) = 2;
				break;
			case 2:
				if (((s32*)((char*)t + 0x38c))[uw(0x90)] != 0) {
					if (w(0x90) == 1 && w(0x3b4) == 0) {
						if (lbl_8042C388 != NULL) {
							fn_800B52E8(lbl_8042C388, 0xE018, 0, 0);
						}
						w(0x2c) = 0xe;
					} else {
						if (lbl_8042C388 != NULL) {
							fn_800B52E8(lbl_8042C388, 0xE008, 0, 0);
						}
						w(0x2c) = 1;
						w(0x60) = 0xa;
						w(0x64) = ((Pair*)lbl_1_data_F70[4])[uw(0x90)].a;
						{
							Pair* pr = (Pair*)lbl_1_data_F70[4];
							w(0x68)  = pr[uw(0x90)].b;
						}
						fn_1_11750(lbl_1_rodata_B0[uw(0x90)]);
					}
				} else {
					if (lbl_8042C388 != NULL) {
						fn_800B52E8(lbl_8042C388, 0xE018, 0, 0);
					}
				}
				break;
		}
	}
}

#pragma dont_inline reset
#pragma force_active reset
