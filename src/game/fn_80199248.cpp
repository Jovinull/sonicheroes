// Table-driven reciprocal square root (HYPOTHESIS: rwInvSqrt): rounds the float's bit pattern,
// negates and halves its exponent and adds the reciprocal-table entry selected by the low exponent
// bit and the top mantissa bits.
#include "game/rw_engine.h"

extern "C" {
f32 fn_80199248(f32 value)
{
	RwSplitBits split;
	split.value = value;
	if (split.bits != 0) {
		split.bits += 0x800;
		split.bits
		    = ((~split.bits >> 1) & 0x3FC00000) + RW_INV_SQRT_TABLE[(split.bits >> 12) & 0xFFF];
	}
	return split.value;
}
}
