#include "types.h"

// BMODEL's compressed geometry setup (VtxFmtInit and
// RpClumpForAllGeometrysToSetCompressedGeometry are the PS2 build's names,
// from STAGE.BIN), the same in the four stage modules that carry BMODEL: the
// module's vertex format is set up once, and every geometry of a clump (or
// one atomic's) is set to use it.

struct RpGeometry;
struct RpClump;

struct RpAtomic {
	u8 unk00[0x18];
	RpGeometry* geometry; // 0x18
};

typedef struct BModelVtxFmt BModelVtxFmt;

class BMODEL
{
public:
	static void VtxFmtInit();
	static void RpClumpForAllGeometrysToSetCompressedGeometry(RpClump* clump);
	static void RpAtomicToSetCompressedGeometry(RpAtomic* atomic);
};

extern "C" {
extern BModelVtxFmt bmodelVtxFmt;
extern s32 bmodelVtxFmtReady;
void fn_8015C728(BModelVtxFmt* format);
void fn_8015C6F8(BModelVtxFmt* format, s32 attr, s32 type);
void fn_8015C704(BModelVtxFmt* format, s32 attr, s32 type);
void fn_8015C710(BModelVtxFmt* format, s32 attr, s32 count, s32 frac);
void fn_8015C720(BModelVtxFmt* format, s32 attr);
void fn_8015C878(RpGeometry* geometry, BModelVtxFmt* format);
void fn_8014FFBC(RpClump* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);
}

void BMODEL::VtxFmtInit()
{
	if (bmodelVtxFmtReady != 1) {
		fn_8015C728(&bmodelVtxFmt);
		fn_8015C6F8(&bmodelVtxFmt, 3, 6);
		fn_8015C704(&bmodelVtxFmt, 3, 0);
		fn_8015C710(&bmodelVtxFmt, 1, 3, 0xA);
		fn_8015C720(&bmodelVtxFmt, 3);
		bmodelVtxFmtReady = 1;
	}
}

RpAtomic* callbackSetCompressedGeometry(RpAtomic* atomic, void* data);

void BMODEL::RpClumpForAllGeometrysToSetCompressedGeometry(RpClump* clump)
{
	fn_8014FFBC(clump, callbackSetCompressedGeometry, NULL);
}

RpAtomic* callbackSetCompressedGeometry(RpAtomic* atomic, void* data)
{
	fn_8015C878(atomic->geometry, &bmodelVtxFmt);
	return atomic;
}

void BMODEL::RpAtomicToSetCompressedGeometry(RpAtomic* atomic)
{
	fn_8015C878(atomic->geometry, &bmodelVtxFmt);
}
