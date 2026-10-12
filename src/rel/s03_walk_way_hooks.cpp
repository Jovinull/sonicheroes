#include "types.h"

// The unload and load hooks rel/s03_walk_way_register.cpp puts in the
// s03WalkWay's editor record. The empty hooks have nothing to do: the object
// loads nothing.

extern "C" void s03WalkWayUnload(void) { }

extern "C" void s03WalkWayLoad(void) { }
