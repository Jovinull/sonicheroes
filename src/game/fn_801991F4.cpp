// Table-driven square root (HYPOTHESIS: rwSqrt).
#include "game/rw_engine.h"

extern "C" {
f32 fn_801991F4(f32 value)
{
	RwSplitBits split;
	split.value = value;
	RW_SQRT_SPLIT(split);
	return split.value;
}
}
