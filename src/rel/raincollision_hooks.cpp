#include "types.h"

// The reset, unload and load hooks rel/raincollision_register.cpp puts in the
// raincollision's editor record. The empty hooks have nothing to do: the object
// loads nothing.

extern "C" void raincollisionReset(void) { }

extern "C" void raincollisionUnload(void) { }

extern "C" void raincollisionLoad(void) { }
