// Normalizes a vector (HYPOTHESIS: RwV3dNormalize): scales in by the table reciprocal square root
// of its squared length into out and returns the length (table square root). A length not above
// lbl_8042F6AC (zero) records core error 0x19 (HYPOTHESIS: zero-length vector).
// Built with GC/2.0 (configure.py): GC/1.3.2 schedules the squared length differently (7 words
// differ). HYPOTHESIS: RenderWare was built with GC/2.x (see fn_8019D0CC).
#include "game/rw_engine.h"

#define RW_ERROR_ZERO_LENGTH 0x19

extern "C" {
// .sdata2 constant 0.0f of the vector code (non-const: loaded as an ordinary global).
extern f32 lbl_8042F6AC;
// HYPOTHESIS: rwSqrt and rwInvSqrt.
f32 fn_801991F4(f32 value);
f32 fn_80199248(f32 value);

f32 fn_801990E0(RwV3d* out, const RwV3d* in)
{
	f32 lengthSq = in->x * in->x + in->y * in->y + in->z * in->z;
	f32 length   = fn_801991F4(lengthSq);
	f32 recip    = fn_80199248(lengthSq);
	out->x       = in->x * recip;
	out->y       = in->y * recip;
	out->z       = in->z * recip;
	if (length <= lbl_8042F6AC) {
		RwError error;
		error.pluginID  = RW_ID_CORE_PLUGIN;
		error.errorCode = fn_8019408C(RW_ERROR_ZERO_LENGTH);
		fn_80193FE8(&error);
	}
	return length;
}
}
