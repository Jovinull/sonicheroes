#include "types.h"

// The reset, unload and load hooks rel/trainappear_register.cpp puts in the
// trainappear's editor record. The empty hooks have nothing to do: the object
// loads nothing.

extern "C" void trainappearReset(void) { }

extern "C" void trainappearUnload(void) { }

extern "C" void trainappearLoad(void) { }
