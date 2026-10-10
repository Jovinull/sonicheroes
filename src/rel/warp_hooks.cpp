#include "types.h"

// The reset, unload and load hooks rel/warp_register.cpp puts in the editor
// record for TObjWarp. The warp loads nothing, so all three are empty.

extern "C" void warpReset(void) { }

extern "C" void warpUnload(void) { }

extern "C" void warpLoad(void) { }
