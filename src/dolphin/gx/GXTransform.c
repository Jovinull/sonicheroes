#include "types.h"
#include <dolphin/gx.h>
#include <dolphin/os.h>

#include "__gx.h"

// GX matrix / projection / viewport / scissor state, 0x801F7420 to 0x801F7910.
// Transcribed from the Apr 2003 Dolphin SDK GXTransform.c (release build, no
// debugger). Only the entry points the game links survive dead-strip: GXProject,
// GXSetProjection, the *Indx / *3x3 matrix loaders, GXGetViewportv,
// GXSetZScaleOffset and GXGetScissor are not referenced, so they are omitted.
// The paired-single asm helpers and __GXSetProjection are fully inlined (no
// out-of-line bodies remain).

static void WriteProjPS(const register f32 proj[6], register volatile void* dest)
{
	register f32 p01, p23, p45;

	// clang-format off
    asm {
        psq_l  p01,  0(proj), 0, 0
        psq_l  p23,  8(proj), 0, 0
        psq_l  p45, 16(proj), 0, 0
        psq_st p01,  0(dest), 0, 0
        psq_st p23,  0(dest), 0, 0
        psq_st p45,  0(dest), 0, 0
    }
	// clang-format on
}

static void Copy6Floats(const register f32 src[6], register volatile f32* dest)
{
	register f32 ps01, ps23, ps45;

	// clang-format off
    asm {
        psq_l  ps01,  0(src), 0, 0
        psq_l  ps23,  8(src), 0, 0
        psq_l  ps45, 16(src), 0, 0
        psq_st ps01,  0(dest), 0, 0
        psq_st ps23,  8(dest), 0, 0
        psq_st ps45, 16(dest), 0, 0
    }
	// clang-format on
}

static void __GXSetProjection(void)
{
	u32 reg = 0x00061020;
	GX_WRITE_U8(0x10);
	GX_WRITE_U32(reg);
	WriteProjPS(__GXData->projMtx, (volatile void*)GXFIFO_ADDR);
	GX_WRITE_U32(__GXData->projType);
}

void GXSetProjectionv(const f32* ptr)
{
	CHECK_GXBEGIN(339, "GXSetProjectionv");

	__GXData->projType = ptr[0] == 0.0f ? GX_PERSPECTIVE : GX_ORTHOGRAPHIC;

	Copy6Floats(&ptr[1], __GXData->projMtx);

	__GXSetProjection();
	__GXData->bpSentNot = 1;
}

void GXGetProjectionv(f32* ptr)
{
	ASSERTMSGLINE(370, ptr, "GXGet*: invalid null pointer");

	ptr[0] = (u32)__GXData->projType != GX_PERSPECTIVE ? 1.0f : 0.0f;

	Copy6Floats(__GXData->projMtx, &ptr[1]);
}

#define qr0 0

static void WriteMTXPS4x3(const register f32 mtx[3][4], register volatile f32* dest)
{
	register f32 a00_a01;
	register f32 a02_a03;
	register f32 a10_a11;
	register f32 a12_a13;
	register f32 a20_a21;
	register f32 a22_a23;

	// clang-format off
    asm {
        psq_l a00_a01, 0x00(mtx), 0, qr0
        psq_l a02_a03, 0x08(mtx), 0, qr0
        psq_l a10_a11, 0x10(mtx), 0, qr0
        psq_l a12_a13, 0x18(mtx), 0, qr0
        psq_l a20_a21, 0x20(mtx), 0, qr0
        psq_l a22_a23, 0x28(mtx), 0, qr0
        psq_st a00_a01, 0(dest), 0, qr0
        psq_st a02_a03, 0(dest), 0, qr0
        psq_st a10_a11, 0(dest), 0, qr0
        psq_st a12_a13, 0(dest), 0, qr0
        psq_st a20_a21, 0(dest), 0, qr0
        psq_st a22_a23, 0(dest), 0, qr0
    }
	// clang-format on
}

static void WriteMTXPS3x3from3x4(register f32 mtx[3][4], register volatile f32* dest)
{
	register f32 a00_a01;
	register f32 a02_a03;
	register f32 a10_a11;
	register f32 a12_a13;
	register f32 a20_a21;
	register f32 a22_a23;

	// clang-format off
    asm {
        psq_l  a00_a01, 0x00(mtx), 0, qr0
        lfs    a02_a03, 0x08(mtx)
        psq_l  a10_a11, 0x10(mtx), 0, qr0
        lfs    a12_a13, 0x18(mtx)
        psq_l  a20_a21, 0x20(mtx), 0, qr0
        lfs    a22_a23, 0x28(mtx)
        psq_st a00_a01, 0(dest), 0, qr0
        stfs   a02_a03, 0(dest)
        psq_st a10_a11, 0(dest), 0, qr0
        stfs   a12_a13, 0(dest)
        psq_st a20_a21, 0(dest), 0, qr0
        stfs   a22_a23, 0(dest)
    }
	// clang-format on
}

static void WriteMTXPS4x2(const register f32 mtx[2][4], register volatile f32* dest)
{
	register f32 a00_a01;
	register f32 a02_a03;
	register f32 a10_a11;
	register f32 a12_a13;

	// clang-format off
    asm {
        psq_l a00_a01, 0x00(mtx), 0, qr0
        psq_l a02_a03, 0x08(mtx), 0, qr0
        psq_l a10_a11, 0x10(mtx), 0, qr0
        psq_l a12_a13, 0x18(mtx), 0, qr0
        psq_st a00_a01, 0(dest), 0, qr0
        psq_st a02_a03, 0(dest), 0, qr0
        psq_st a10_a11, 0(dest), 0, qr0
        psq_st a12_a13, 0(dest), 0, qr0
    }
	// clang-format on
}

void GXLoadPosMtxImm(const f32 mtx[3][4], u32 id)
{
	u32 reg;
	u32 addr;

	CHECK_GXBEGIN(507, "GXLoadPosMtxImm");

	addr = id * 4;
	reg  = addr | 0xB0000;

	GX_WRITE_U8(0x10);
	GX_WRITE_U32(reg);
	WriteMTXPS4x3(mtx, &GXWGFifo.f32);
}

void GXLoadNrmMtxImm(const f32 mtx[3][4], u32 id)
{
	u32 reg;
	u32 addr;

	CHECK_GXBEGIN(588, "GXLoadNrmMtxImm");

	addr = id * 3 + 0x400;
	reg  = addr | 0x80000;

	GX_WRITE_U8(0x10);
	GX_WRITE_U32(reg);
	WriteMTXPS3x3from3x4((void*)mtx, &GXWGFifo.f32);
}

void GXSetCurrentMtx(u32 id)
{
	CHECK_GXBEGIN(708, "GXSetCurrentMtx");
	SET_REG_FIELD(712, __GXData->matIdxA, 6, 0, id);
	__GXSetMatrixIndex(GX_VA_PNMTXIDX);
}

void GXLoadTexMtxImm(const f32 mtx[][4], u32 id, GXTexMtxType type)
{
	u32 reg;
	u32 addr;
	u32 count;

	CHECK_GXBEGIN(741, "GXLoadTexMtxImm");

	if (id >= GX_PTTEXMTX0) {
		addr = (id - GX_PTTEXMTX0) * 4 + 0x500;
		ASSERTMSGLINE(751, type == GX_MTX3x4, "GXLoadTexMtx: Invalid matrix type");
	} else {
		addr = id * 4;
	}
	count = (type == GX_MTX2x4) ? 8 : 12;
	reg   = addr | ((count - 1) << 16);

	GX_WRITE_U8(0x10);
	GX_WRITE_U32(reg);
	if (type == GX_MTX3x4) {
		WriteMTXPS4x3(mtx, &GXWGFifo.f32);
	} else {
		WriteMTXPS4x2(mtx, &GXWGFifo.f32);
	}
}

void __GXSetViewport(void)
{
	f32 sx;
	f32 sy;
	f32 sz;
	f32 ox;
	f32 oy;
	f32 oz;
	f32 zmin;
	f32 zmax;
	u32 reg;

	sx = __GXData->vpWd / 2.0f;
	sy = -__GXData->vpHt / 2.0f;
	ox = 342.0f + (__GXData->vpLeft + (__GXData->vpWd / 2.0f));
	oy = 342.0f + (__GXData->vpTop + (__GXData->vpHt / 2.0f));

	zmin = __GXData->vpNearz * __GXData->zScale;
	zmax = __GXData->vpFarz * __GXData->zScale;

	sz = zmax - zmin;
	oz = zmax + __GXData->zOffset;

	reg = 0x5101A;
	GX_WRITE_U8(0x10);
	GX_WRITE_U32(reg);
	GX_WRITE_XF_REG_F(26, sx);
	GX_WRITE_XF_REG_F(27, sy);
	GX_WRITE_XF_REG_F(28, sz);
	GX_WRITE_XF_REG_F(29, ox);
	GX_WRITE_XF_REG_F(30, oy);
	GX_WRITE_XF_REG_F(31, oz);
}

void GXSetViewportJitter(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz, u32 field)
{
	CHECK_GXBEGIN(903, "GXSetViewport"); // not the correct function name

	if (field == 0) {
		top -= 0.5f;
	}

	__GXData->vpLeft  = left;
	__GXData->vpTop   = top;
	__GXData->vpWd    = wd;
	__GXData->vpHt    = ht;
	__GXData->vpNearz = nearz;
	__GXData->vpFarz  = farz;

	__GXSetViewport();
	__GXData->bpSentNot = 1;
}

void GXSetViewport(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz)
{
	GXSetViewportJitter(left, top, wd, ht, nearz, farz, 1);
}

void GXSetScissor(u32 left, u32 top, u32 wd, u32 ht)
{
	u32 tp;
	u32 lf;
	u32 bm;
	u32 rt;

	CHECK_GXBEGIN(1048, "GXSetScissor");
	ASSERTMSGLINE(1049, left < 1706, "GXSetScissor: Left origin > 1708");
	ASSERTMSGLINE(1050, top < 1706, "GXSetScissor: top origin > 1708");
	ASSERTMSGLINE(1051, left + wd < 1706, "GXSetScissor: right edge > 1708");
	ASSERTMSGLINE(1052, top + ht < 1706, "GXSetScissor: bottom edge > 1708");

	tp = top + 342;
	lf = left + 342;
	bm = tp + ht - 1;
	rt = lf + wd - 1;

	SET_REG_FIELD(1059, __GXData->suScis0, 11, 0, tp);
	SET_REG_FIELD(1060, __GXData->suScis0, 11, 12, lf);
	SET_REG_FIELD(1062, __GXData->suScis1, 11, 0, bm);
	SET_REG_FIELD(1063, __GXData->suScis1, 11, 12, rt);

	GX_WRITE_RAS_REG(__GXData->suScis0);
	GX_WRITE_RAS_REG(__GXData->suScis1);
	__GXData->bpSentNot = 0;
}

void GXSetScissorBoxOffset(s32 x_off, s32 y_off)
{
	u32 reg = 0;
	u32 hx;
	u32 hy;

	CHECK_GXBEGIN(1119, "GXSetScissorBoxOffset");

	ASSERTMSGLINE(1122, (u32)(x_off + 342) < 2048, "GXSetScissorBoxOffset: Invalid X offset");
	ASSERTMSGLINE(1124, (u32)(y_off + 342) < 2048, "GXSetScissorBoxOffset: Invalid Y offset");

	hx = (u32)(x_off + 342) >> 1;
	hy = (u32)(y_off + 342) >> 1;

	SET_REG_FIELD(1129, reg, 10, 0, hx);
	SET_REG_FIELD(1130, reg, 10, 10, hy);
	SET_REG_FIELD(1131, reg, 8, 24, 0x59);
	GX_WRITE_RAS_REG(reg);
	__GXData->bpSentNot = 0;
}

void GXSetClipMode(GXClipMode mode)
{
	CHECK_GXBEGIN(1151, "GXSetClipMode");
	GX_WRITE_XF_REG(5, mode);
	__GXData->bpSentNot = 1;
}

void __GXSetMatrixIndex(GXAttr matIdxAttr)
{
	if (matIdxAttr < GX_VA_TEX4MTXIDX) {
		GX_WRITE_SOME_REG4(8, 0x30, __GXData->matIdxA, -12);
		GX_WRITE_XF_REG(24, __GXData->matIdxA);
	} else {
		GX_WRITE_SOME_REG4(8, 0x40, __GXData->matIdxB, -12);
		GX_WRITE_XF_REG(25, __GXData->matIdxB);
	}
	__GXData->bpSentNot = 1;
}
