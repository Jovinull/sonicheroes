// Stores in out the vector in scaled to unit length with fn_80199248 (table reciprocal square root
// of its squared length).
// Built with GC/2.0 (configure.py): GC/1.3.2 schedules the squared-length arithmetic differently.
// HYPOTHESIS: RenderWare was built with GC/2.x (see fn_8019D0CC).
#include "game/rw_engine.h"

extern "C" {
// HYPOTHESIS: rwInvSqrt (table-driven reciprocal square root).
f32 fn_80199248(f32 value);

void fn_80199064(RwV3d* out, const RwV3d* in)
{
	f32 recip = fn_80199248(in->x * in->x + in->y * in->y + in->z * in->z);
	out->x    = in->x * recip;
	out->y    = in->y * recip;
	out->z    = in->z * recip;
}
}
