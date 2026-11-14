// Normalises a 2D vector with the table-driven square root and inverse square root and returns
// its original length (HYPOTHESIS: RwV2dNormalize); a non-positive length (compared with the
// .sdata2 constant lbl_8042F6AC, HYPOTHESIS 0.0f) records core error 0x19. Built with GC/2.0
// (configure.py), like fn_801992A4; the squares are separate terms, so they are not fused.
#include "game/rw_engine.h"

// 2D vector (HYPOTHESIS: RwV2d).
struct RwV2d8019930C {
	f32 x;
	f32 y;
};

extern "C" {
extern f32 lbl_8042F6AC;

f32 fn_8019930C(RwV2d8019930C* out, const RwV2d8019930C* in)
{
	RwSplitBits length;
	RwSplitBits recip;
	f32 x             = in->x;
	f32 xx            = x * x;
	f32 yy            = in->y * in->y;
	f32 lengthSquared = xx + yy;

	length.value = lengthSquared;
	RW_SQRT_SPLIT(length);
	recip.value = lengthSquared;
	if (recip.bits != 0) {
		recip.bits += 0x800;
		recip.bits
		    = ((~recip.bits >> 1) & 0x3FC00000) + RW_INV_SQRT_TABLE[(recip.bits >> 12) & 0xFFF];
	}
	out->x = x * recip.value;
	out->y = in->y * recip.value;
	if (length.value <= lbl_8042F6AC) {
		RwError error;
		error.pluginID  = RW_ID_CORE_PLUGIN;
		error.errorCode = fn_8019408C(0x19);
		fn_80193FE8(&error);
	}
	return length.value;
}
}
