#include "types.h"

// autosaveD carries its own copy of this unit: the same source as
// advertiseD/adv_draw.cpp, linked here at .text 0x2488-0x346C, .rodata 0xA0-0x328. Functions and data are
// byte-identical to the advertiseD objects once relocations are masked; only
// module-local names differ (fn_1_/lbl_1_ there, fn_2_/lbl_2_ here), mapped by
// pairing every relocation at the same offset in both retail objects. Taken
// over from the abandoned PR #116 (ThePlayerRolo), which first identified these
// AutoSaveD classes from PS2 symbols; the reconstruction is CYPRESS's advertiseD
// work. Keep the two copies in sync.
//
// ADV_DRAW - the advertise/attract-mode 2D primitive drawing helper
// (advertiseD, REL module 1). This translation unit sits between adv_staffroll and
// adv_window and has no name string / no vtable: it is a shared low-level
// helper that renders solid and textured 2D quads (RenderWare Im2D) used to
// build the attract-mode UI boxes, panels and window frames.
//
// The GameCube release emits 13 functions here. Semantics are drawn from the
// RwIm2D primitive family (RwRenderStateSet/Get + RwIm2DRenderPrimitive), which
// the module reaches through the unmangled extern "C" wrappers below.
//
// Struct offsets are GameCube ground truth; only logic/names come from the PS2
// reference. Aggregate templates are defined in their original .rodata order;
// the scalar tail is kept in adv_draw_constants.cpp so each named load remains
// opaque while the linker reconstructs the original contiguous constant pool.

typedef s32 RwInt32;

struct RwV2d {
	f32 x;
	f32 y;
};

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

struct RwRGBA {
	u8 red;
	u8 green;
	u8 blue;
	u8 alpha;
};

// {u0, v0, u1, v1}
struct RwUV {
	f32 u0;
	f32 v0;
	f32 u1;
	f32 v1;
};

struct RwRect {
	s32 x;
	s32 y;
	s32 w;
	s32 h;
};

struct RwIm2DVertex {
	f32 x;
	f32 y;
	f32 z;
	RwRGBA color;
	f32 u;
	f32 v;
};

// Blob types for the unrolled template copies from .rodata (array members give
// the paired lwz/stw the original emits).
struct Blob8 {
	u32 w[2];
};
struct Blob12 {
	u32 w[3];
};
struct Blob32 {
	u32 w[8];
};
struct Blob48 {
	u32 w[12];
};
struct Blob64 {
	u32 w[16];
};
struct Blob108 {
	u32 w[27];
};
struct Blob144 {
	u32 w[36];
};

// --- RenderWare Im2D wrappers (other TUs of this module / the DOL) ---
extern "C" void fn_80194234(RwInt32 state, RwInt32 value);
extern "C" void fn_80194294(RwInt32 state, RwInt32* value);
extern "C" f32 fn_8019421C(void);
extern "C" void fn_801942C0(RwInt32 primType, RwIm2DVertex* verts, RwInt32 numVerts);
extern "C" s32 fn_800A9398(void* t, s32 v);

// The screen/camera accessor: *(void**)lbl_8042C9A4 -> camera; [0x80] = near Z.
extern "C" void** lbl_8042C9A4;

extern "C" u8 lbl_80303EC8[];
extern "C" s32 lbl_2_bss_54[];
extern "C" s32 RsGlobal[];

// Compiler-emitted aggregate templates that precede fn_2_2BC8's local
// RwV3d[9] template in .rodata.
extern "C" const Blob12 lbl_2_rodata_A0       = { { 0x41800000, 0x41800000, 0 } };
extern "C" const Blob12 lbl_2_rodata_AC       = { { 0, 0, 0 } };
extern "C" const Blob8 lbl_2_rodata_B8        = { { 0, 0x42000000 } };
extern "C" const Blob8 lbl_2_rodata_C0        = { { 0, 0 } };
extern "C" const Blob8 lbl_2_rodata_C8        = { { 0, 0 } };
extern "C" volatile const u32 lbl_2_rodata_D0 = 0xffffffff;
extern "C" const Blob8 lbl_2_rodata_D4        = { { 0, 0 } };
extern "C" const Blob48 lbl_2_rodata_DC       = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
extern "C" const Blob64 lbl_2_rodata_10C      = { {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
} };
#pragma force_active on
extern "C" const Blob8 lbl_2_rodata_14C = { { 0, 0 } };
#pragma force_active reset
extern "C" const Blob8 lbl_2_rodata_154 = { { 0x41800000, 0x41800000 } };
extern "C" const Blob8 lbl_2_rodata_15C = { { 0x41800000, 0x41800000 } };
extern "C" const Blob8 lbl_2_rodata_164 = { { 0, 0x41800000 } };
extern "C" const Blob8 lbl_2_rodata_16C = { { 0, 0 } };

// These follow the generated RwV3d[9] template. Their definitions are kept
// after fn_2_2BC8 so MWCC emits the section in the original order.
extern "C" const Blob144 lbl_2_rodata_1E0;
extern "C" const Blob8 lbl_2_rodata_270;
extern "C" const Blob48 lbl_2_rodata_278;
extern "C" const Blob32 lbl_2_rodata_2A8;
extern "C" const Blob8 lbl_2_rodata_2C8;
extern "C" const Blob48 lbl_2_rodata_2D0;
extern "C" const Blob32 lbl_2_rodata_300;
extern "C" const f32 lbl_2_rodata_328;
extern "C" const f32 lbl_2_rodata_32C;
extern "C" const f32 lbl_2_rodata_330;
extern "C" const f32 lbl_2_rodata_334;
extern "C" const f32 lbl_2_rodata_338;

// Leaf helpers defined at the bottom; forward-declared for their earlier callers.
extern "C" void fn_2_24FC(void* t);
extern "C" void fn_2_25A8(void* t);
extern "C" void fn_2_31F0(void* t, RwV3d* pos, RwV2d* size, RwUV* uv, f32 recipZ);

#define w(o) (*(s32*)((u8*)t + (o)))

static inline f32 recipCamZ()
{
	return lbl_2_rodata_328 / *(f32*)((u8*)*lbl_8042C9A4 + 0x80);
}

// 0x13744 - set the shared blend/priority state from a mode selector.

extern "C" void fn_2_26C0(void*, RwRect*, RwRGBA*);
extern "C" void fn_2_2868(void*, RwV3d*, RwV2d*);
extern "C" void fn_2_2A18(void*, RwV3d*, RwV2d*);
extern "C" void fn_2_2BC8(void*, const RwV3d*, const RwV2d*);
extern "C" void fn_2_2F94(void*, RwV3d*, RwV2d*);
extern "C" void fn_2_32F8(void*, RwV3d*, RwV2d*);
extern "C" void fn_2_3368(void*, RwV3d*, RwV2d*, s32);
extern "C" s32 fn_2_3404(void*);
extern "C" void fn_2_340C(void*);
extern "C" void fn_2_340C(void* t)
{
	RwRGBA col;
	RwRect rect;

	rect.x    = 0;
	rect.y    = 0;
	rect.w    = RsGlobal[1];
	rect.h    = RsGlobal[2];
	col.red   = 0;
	col.green = 0;
	col.blue  = 0;
	col.alpha = 0xa0;
	fn_2_26C0(t, &rect, &col);
}

extern "C" s32 fn_2_3404(void* t)
{
	return w(0x6c);
}

extern "C" void fn_2_3368(void* t, RwV3d* pos, RwV2d* size, s32 flag)
{
	fn_2_25A8(t);
	if (flag != 0)
		fn_80194234(1, lbl_2_bss_54[0]);
	else
		fn_80194234(1, lbl_2_bss_54[1]);
	fn_2_2868(t, pos, size);
	fn_2_24FC(t);
}

extern "C" void fn_2_32F8(void* t, RwV3d* pos, RwV2d* size)
{
	fn_2_25A8(t);
	fn_80194234(1, lbl_2_bss_54[4]);
	fn_2_2F94(t, pos, size);
	fn_2_24FC(t);
}

extern "C" void fn_2_31F0(void* t, RwV3d* pos, RwV2d* size, RwUV* uv, f32 recipZ)
{
	RwIm2DVertex v[4];
	RwRGBA white;
	RwIm2DVertex* q;

	*(u32*)&white = *(volatile const u32*)&lbl_2_rodata_D0;
	v[0].x        = pos->x;
	v[0].y        = pos->y;
	v[0].z        = pos->z;
	v[0].color    = white;
	v[0].u        = uv->u0;
	v[0].v        = uv->v0;
	v[1].x        = pos->x;
	v[1].y        = pos->y + size->y;
	v[1].z        = pos->z;
	q             = &v[1];
	q->color      = white;
	q->u          = uv->u0;
	v[1].v        = uv->v1;
	v[2].x        = pos->x + size->x;
	v[2].y        = pos->y;
	v[2].z        = pos->z;
	v[2].color    = white;
	v[2].u        = uv->u1;
	v[2].v        = uv->v0;
	v[3].x        = pos->x + size->x;
	v[3].y        = pos->y + size->y;
	v[3].z        = pos->z;
	v[3].color    = white;
	v[3].u        = uv->u1;
	v[3].v        = uv->v1;
	fn_801942C0(4, v, 4);
}

extern "C" void fn_2_2F94(void* t, RwV3d* pos, RwV2d* size)
{
	f32 recipZ = recipCamZ();
	RwV3d p[4];
	RwUV uv[4];
	RwV2d sz;
	f32 uu;
	f32 vv;
	const f32* texel;
	u8 sel;

	*(Blob8*)&sz = lbl_2_rodata_D4;
	sz.x         = lbl_2_rodata_32C * size->x;
	sz.y         = lbl_2_rodata_32C * size->y;
	// Loading the texel scale through a materialized pointer (rather than a
	// direct sda-less rodata load) shares the @ha base and fixes the FP
	// register allocation for uu/vv (permuter-recovered).
	uu           = size->x * (*(texel = &lbl_2_rodata_330));
	vv           = size->y * (*texel);
	*(Blob48*)p  = lbl_2_rodata_DC;
	p[0].x       = pos->x;
	p[0].y       = pos->y;
	p[0].z       = pos->z;
	p[1].x       = pos->x + sz.x;
	p[1].y       = pos->y;
	p[1].z       = pos->z;
	p[2].x       = pos->x;
	p[2].y       = pos->y + sz.y;
	p[2].z       = pos->z;
	p[3].x       = pos->x + sz.x;
	p[3].y       = pos->y + sz.y;
	p[3].z       = pos->z;
	*(Blob64*)uv = lbl_2_rodata_10C;
	uv[0].u1     = uu;
	uv[0].v1     = vv;
	uv[1].u0     = uu;
	uv[1].v1     = vv;
	uv[2].v0     = vv;
	uv[2].u1     = uu;
	uv[3].u0     = uu;
	uv[3].v0     = vv;
	fn_2_31F0(t, &p[0], &sz, &uv[0], recipZ);
	sel = 1;
	fn_2_31F0(t, &p[sel], &sz, &uv[sel], recipZ);
	sel = 2;
	fn_2_31F0(t, &p[sel], &sz, &uv[sel], recipZ);
	sel = 3;
	fn_2_31F0(t, &p[sel], &sz, &uv[sel], recipZ);
}

extern "C" void fn_2_2BC8(void* t, const RwV3d* pos, const RwV2d* size)
{
	f32 recipZ = recipCamZ();
	RwV2d szCorner;
	RwV2d szEdge;
	RwV2d szHBar;
	RwV2d szCenter;
	union {
		Blob144 b;
		RwUV uv[9];
	} uvs;
	f32 z;
	f32 y;
	f32 x;
	f32 innerY;
	f32 bottom;
	f32 cornerY;
	f32 lowerY;
	f32 cornerX;
	f32 uu;
	f32 vv;
	u8 sel;
	RwUV* uv4;
	RwV3d* p4;
	RwUV* uv5;
	RwV3d* p5;

	*(Blob8*)&szCorner = lbl_2_rodata_154;
	*(Blob8*)&szEdge   = lbl_2_rodata_15C;
	*(Blob8*)&szHBar   = lbl_2_rodata_164;
	szHBar.x           = size->x - lbl_2_rodata_334;
	*(Blob8*)&szCenter = lbl_2_rodata_16C;
	szCenter.x         = size->x - lbl_2_rodata_334;
	szCenter.y         = size->y - lbl_2_rodata_334;
	uu                 = size->x * lbl_2_rodata_330;
	vv                 = size->y * lbl_2_rodata_330;

	RwV3d pc[9] = {
		{ pos->x, pos->y, pos->z },
		{ pos->x + size->x - szCorner.x, pos->y, pos->z },
		{ pos->x, pos->y + size->y - szCorner.y, pos->z },
		{ pos->x + size->x - szCorner.x, pos->y + size->y - szCorner.y, pos->z },
		{ pos->x, pos->y + szCorner.y, pos->z },
		{ pos->x + size->x - szCorner.x, pos->y + szCorner.y, pos->z },
		{ pos->x + szCorner.x, pos->y, pos->z },
		{ pos->x + szCorner.x, pos->y + size->y - szHBar.y, pos->z },
		{ pos->x + szCorner.x, pos->y + szCorner.y, pos->z },
	};

	uvs.b        = lbl_2_rodata_1E0;
	uvs.uv[4].v0 = vv;
	uvs.uv[4].v1 = vv;
	uvs.uv[5].v0 = vv;
	uvs.uv[5].v1 = vv;
	uvs.uv[8].u0 = uu;
	uvs.uv[8].v0 = vv;
	uvs.uv[8].u1 = uu;
	uvs.uv[8].v1 = vv;

	fn_2_31F0(t, (RwV3d*)((u8*)pc + 0 * 12), &szCorner, &uvs.uv[0], recipZ);
	sel = 1;
	fn_2_31F0(t, (RwV3d*)((u8*)pc + sel * 12), &szCorner, &uvs.uv[sel], recipZ);
	sel = 2;
	fn_2_31F0(t, (RwV3d*)((u8*)pc + sel * 12), &szCorner, &uvs.uv[sel], recipZ);
	sel = 3;
	fn_2_31F0(t, (RwV3d*)((u8*)pc + sel * 12), &szCorner, &uvs.uv[sel], recipZ);

	uv4 = &uvs.uv[4];
	p4  = &pc[4];
	uv5 = &uvs.uv[5];
	p5  = &pc[5];
	while (p4->y <= pc[2].y - szEdge.y) {
		fn_2_31F0(t, p4, &szEdge, uv4, recipZ);
		fn_2_31F0(t, p5, &szEdge, uv5, recipZ);
		p4->y += szEdge.y;
		p5->y += szEdge.y;
	}
	{
		f32 fine = lbl_2_rodata_338;
		szEdge.y = fine;
		while (p4->y <= pc[2].y) {
			fn_2_31F0(t, p4, &szEdge, uv4, recipZ);
			fn_2_31F0(t, p5, &szEdge, uv5, recipZ);
			p4->y += fine;
			p5->y += fine;
		}
	}

	sel = 6;
	fn_2_31F0(t, (RwV3d*)((u8*)pc + sel * 12), &szHBar, &uvs.uv[sel], recipZ);
	sel = 7;
	fn_2_31F0(t, (RwV3d*)((u8*)pc + sel * 12), &szHBar, &uvs.uv[sel], recipZ);
	sel = 8;
	fn_2_31F0(t, (RwV3d*)((u8*)pc + sel * 12), &szCenter, &uvs.uv[sel], recipZ);
}

// These explicit objects follow fn_2_2BC8's compiler-generated RwV3d[9]
// template and complete this TU's original .rodata range.
extern "C" const Blob144 lbl_2_rodata_1E0 = { {
	0,
	0,
	0x3f800000,
	0x3f800000,
	0x3f800000,
	0,
	0,
	0x3f800000,
	0,
	0x3f800000,
	0x3f800000,
	0,
	0x3f800000,
	0x3f800000,
	0,
	0,
	0,
	0,
	0x3f800000,
	0,
	0x3f800000,
	0,
	0,
	0,
	0x3f800000,
	0,
	0x3f800000,
	0x3f840000,
	0x3f800000,
	0x3f840000,
	0x3f800000,
	0,
	0,
} };
extern "C" const Blob8 lbl_2_rodata_270   = { { 0, 0 } };
extern "C" const Blob48 lbl_2_rodata_278  = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
extern "C" const Blob32 lbl_2_rodata_2A8  = { {
	0,
	0,
	0,
	0x3f800000,
	0,
	0,
	0,
	0x3f800000,
} };
extern "C" const Blob8 lbl_2_rodata_2C8   = { { 0, 0 } };
extern "C" const Blob48 lbl_2_rodata_2D0  = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
extern "C" const Blob32 lbl_2_rodata_300  = { {
	0,
	0,
	0,
	0x3f800000,
	0,
	0,
	0,
	0x3f800000,
} };

extern "C" void fn_2_2A18(void* t, RwV3d* pos, RwV2d* size)
{
	f32 recipZ = recipCamZ();
	// `sel` indexes the second quad. A variable index (rather than the
	// constant 1) forces MWCC to re-derive &p[1]/&uv[1] at the call instead
	// of caching them in callee-saved registers (permuter-recovered shape).
	u8 sel;
	RwV2d sz;
	RwUV uv[2];
	RwV3d p[4];
	f32 u;

	*(Blob8*)&sz = lbl_2_rodata_270;
	sz.x         = lbl_2_rodata_32C * size->x;
	sz.y         = size->y;
	u            = size->x * lbl_2_rodata_330;
	*(Blob48*)p  = lbl_2_rodata_278;
	p[0].x       = pos->x;
	p[0].y       = pos->y;
	p[0].z       = pos->z;
	p[1].x       = pos->x + sz.x;
	p[1].y       = pos->y;
	p[1].z       = pos->z;
	*(Blob32*)uv = lbl_2_rodata_2A8;
	uv[0].u1     = u;
	uv[1].u0     = u;
	fn_2_31F0(t, &p[0], &sz, &uv[0], recipZ);
	sel = 1;
	fn_2_31F0(t, &p[sel], &sz, &uv[sel], recipZ);
}

extern "C" void fn_2_2868(void* t, RwV3d* pos, RwV2d* size)
{
	f32 recipZ = recipCamZ();
	union {
		Blob8 b;
		RwV2d v;
	} sz;
	union {
		Blob32 b;
		RwUV uv[2];
	} uvs;
	union {
		Blob48 b;
		RwV3d p[4];
	} ps;
	f32 u;
	// See fn_2_2A18: variable index defeats the sub-object address CSE.
	u8 sel;

	sz.b         = lbl_2_rodata_2C8;
	sz.v.x       = lbl_2_rodata_32C * size->x;
	sz.v.y       = size->y;
	u            = size->x * lbl_2_rodata_330;
	ps.b         = lbl_2_rodata_2D0;
	ps.p[0].x    = pos->x;
	ps.p[0].y    = pos->y;
	ps.p[0].z    = pos->z;
	ps.p[1].x    = pos->x + sz.v.x;
	ps.p[1].y    = pos->y;
	ps.p[1].z    = pos->z;
	uvs.b        = lbl_2_rodata_300;
	uvs.uv[0].u1 = u;
	uvs.uv[1].u0 = u;
	fn_2_31F0(t, &ps.p[0], &sz.v, &uvs.uv[0], recipZ);
	sel = 1;
	fn_2_31F0(t, &ps.p[sel], &sz.v, &uvs.uv[sel], recipZ);
}

extern "C" void fn_2_26C0(void* t, RwRect* rect, RwRGBA* color)
{
	RwIm2DVertex v[4];
	f32 z;

	fn_80194234(1, 0);
	fn_2_25A8(t);
	z          = fn_8019421C();
	v[0].x     = (f32)rect->x;
	v[0].y     = (f32)rect->y;
	v[0].z     = z;
	v[1].x     = (f32)rect->x;
	v[1].y     = (f32)(rect->y + rect->h);
	v[1].z     = z;
	v[2].x     = (f32)(rect->x + rect->w);
	v[2].y     = (f32)rect->y;
	v[2].z     = z;
	v[3].x     = (f32)(rect->x + rect->w);
	v[3].y     = (f32)(rect->y + rect->h);
	v[3].z     = z;
	v[0].color = *color;
	v[1].color = *color;
	v[2].color = *color;
	v[3].color = *color;
	fn_801942C0(4, v, 4);
	fn_2_24FC(t);
}

extern "C" void fn_2_25A8(void* t)
{
	fn_80194294(6, &w(0x810));
	fn_80194294(8, &w(0x814));
	fn_80194294(0xc, &w(0x818));
	fn_80194294(0xa, &w(0x81c));
	fn_80194294(0xb, &w(0x820));
	fn_80194294(9, &w(0x824));
	fn_80194294(0x14, &w(0x828));
	fn_80194294(3, &w(0x82c));
	fn_80194294(4, &w(0x830));
	fn_80194294(0xe, &w(0x834));
	fn_80194234(6, 0);
	fn_80194234(8, 0);
	fn_80194234(0xc, 1);
	fn_80194234(0xa, 5);
	fn_80194234(0xb, 6);
	fn_80194234(9, 1);
	fn_80194234(0x14, 1);
	fn_80194234(3, 3);
	fn_80194234(4, 3);
	fn_80194234(0xe, 0);
}

extern "C" void fn_2_24FC(void* t)
{
	fn_80194234(6, w(0x810));
	fn_80194234(8, w(0x814));
	fn_80194234(0xc, w(0x818));
	fn_80194234(0xa, w(0x81c));
	fn_80194234(0xb, w(0x820));
	fn_80194234(9, w(0x824));
	fn_80194234(0x14, w(0x828));
	fn_80194234(3, w(0x82c));
	fn_80194234(4, w(0x830));
	fn_80194234(0xe, w(0x834));
	fn_80194234(1, 0);
}

extern "C" void fn_2_2488(s32 mode)
{
	switch (mode) {
		case 1:
			fn_800A9398(lbl_80303EC8, 0);
			break;
		case 2:
			fn_800A9398(lbl_80303EC8, 1);
			break;
		case 0:
		default:
			fn_800A9398(lbl_80303EC8, -1);
			break;
	}
}
