// Returns the length of a 2D vector with the table-driven square root (HYPOTHESIS: RwV2dLength).
// Built with GC/2.0 (configure.py): GC/1.3.2 orders the squared-length arithmetic differently
// (4 words differ). HYPOTHESIS: RenderWare was built with GC/2.x (see fn_8019D0CC).
#include "game/rw_engine.h"

// 2D vector (HYPOTHESIS: RwV2d).
struct RwV2d801992A4 {
	f32 x;
	f32 y;
};

extern "C" {
f32 fn_801992A4(const RwV2d801992A4* v)
{
	RwSplitBits split;
	split.value = v->x * v->x + v->y * v->y;
	RW_SQRT_SPLIT(split);
	return split.value;
}
}
