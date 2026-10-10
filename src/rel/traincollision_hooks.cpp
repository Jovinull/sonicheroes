#include "types.h"

// The reset, unload and load hooks rel/traincollision_register.cpp puts in the
// traincollision's editor record. The empty hooks have nothing to do: the
// object loads nothing.

extern "C" void traincollisionReset(void) { }

extern "C" void traincollisionUnload(void) { }

extern "C" void traincollisionLoad(void) { }
