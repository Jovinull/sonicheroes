#include "types.h"

// The unload hook rel/s02_break_ruin_s_register.cpp puts in S02 BREAKRUIN
// S's editor record: it releases the resources the stage's breakable
// objects share (s02BreakReleaseResources, still assembly).

extern "C" void s02BreakReleaseResources(void);

extern "C" void s02BreakruinSUnload(void)
{
	s02BreakReleaseResources();
}
