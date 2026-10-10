#include "types.h"

// The reset, unload and load hooks rel/s23_warppos_register.cpp puts in the
// s23Warppos's editor record. The empty hooks have nothing to do: the object
// loads nothing.

extern "C" void s23WarpposReset(void) { }

extern "C" void s23WarpposUnload(void) { }

extern "C" void s23WarpposLoad(void) { }
