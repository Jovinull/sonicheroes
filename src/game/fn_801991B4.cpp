// Returns the length of a vector: fn_801991F4 (table square root) of its squared length
// (HYPOTHESIS: RwV3dLength).
// Built with GC/2.0 (configure.py): GC/1.3.2 schedules the squared-length arithmetic differently.
// HYPOTHESIS: RenderWare was built with GC/2.x (see fn_8019D0CC).
#include "game/rw_engine.h"

extern "C" {
// HYPOTHESIS: rwSqrt (table-driven square root).
f32 fn_801991F4(f32 value);

f32 fn_801991B4(const RwV3d* v)
{
	return fn_801991F4(v->x * v->x + v->y * v->y + v->z * v->z);
}
}
