// Empty function in the PARTICLE_MATERIAL code region. Its role and parameters are UNKNOWN; the
// GameCube body is a bare return (HYPOTHESIS: an empty virtual hook of the particle material
// classes, like PARTICLE_MATERIAL::Disp next to it).
#include "types.h"

// No relocation in the retail DOL refers to this function, but the linker kept it; force_active
// keeps mwld from dead-stripping our copy.
#pragma force_active on
extern "C" void fn_800643E4(void) { }
#pragma force_active reset
