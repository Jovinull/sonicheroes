#include "types.h"

// TObjLensFlare's flag test. It reports whether the value it is given is
// non-zero, without branching: negating and OR-ing a value leaves the sign bit
// set for everything except zero, so shifting that bit down gives the answer.
//
// The claim is .text 0x00045A00 to 0x00045A10 and nothing else. It reads no
// constant, so it owns no rodata.
//
// The name is read from the layout: the run sits directly before
// lensFlareRegister in that family's block.
//
// The first parameter is unused, which is why the value arrives in r4.
//
// The run is the same in the nine stage modules that carry it, checked by
// normalising the disassembly and comparing across modules.

extern "C" s32 lensFlareIsSet(void* object, s32 value)
{
	return value != 0;
}
