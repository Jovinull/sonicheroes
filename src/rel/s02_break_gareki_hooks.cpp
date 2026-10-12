#include "types.h"

// The unload and load hooks rel/s02_break_gareki_register.cpp puts in S02
// BREAK GAREKI's editor record: they release and load the resources the
// stage's breakable objects share (s02BreakReleaseResources and
// s02BreakLoadResources, still assembly).

extern "C" void s02BreakReleaseResources(void);
extern "C" void s02BreakLoadResources(void);

extern "C" void s02BreakGarekiUnload(void)
{
	s02BreakReleaseResources();
}

extern "C" void s02BreakGarekiLoad(void)
{
	s02BreakLoadResources();
}
