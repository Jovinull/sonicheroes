// Stores the three matrix tolerances (normal, orthogonal, identity) in the matrix module globals
// at +0xC (HYPOTHESIS: RwMatrixSetTolerance). Always returns 1.
// Built with GC/2.0 (configure.py): GC/1.3.2 orders the three-word copy differently (9 words differ).
// HYPOTHESIS: the RenderWare library was built with a GC/2.x compiler (see fn_8019D0CC).
#include "game/rw_engine.h"

// Matrix tolerances (HYPOTHESIS: RwMatrixTolerance).
struct RwMatrixTolerance8019541C {
	f32 normal;
	f32 orthogonal;
	f32 identity;
};

// The retail code copies the tolerances as three plain words; a struct copy of the float triple
// goes through floating-point registers instead.
struct RwMatrixToleranceWords8019541C {
	u32 w[3];
};

extern "C" {
// Matrix module bookkeeping (HYPOTHESIS: matrixModule).
extern RwModuleInfo lbl_8042C958;

s32 fn_8019541C(const RwMatrixTolerance8019541C* tolerance)
{
	RwMatrixToleranceWords8019541C* dst
	    = (RwMatrixToleranceWords8019541C*)((u8*)lbl_8042C9A4 + lbl_8042C958.globalsOffset + 0xC);
	*dst = *(const RwMatrixToleranceWords8019541C*)tolerance;
	return 1;
}
}
