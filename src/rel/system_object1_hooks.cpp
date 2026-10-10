#include "types.h"

// The reset, unload and load hooks rel/system_object1_register.cpp puts in the
// systemObject1's editor record. The empty hooks have nothing to do: the object
// loads nothing.

extern "C" void systemObject1Reset(void) { }

extern "C" void systemObject1Unload(void) { }

extern "C" void systemObject1Load(void) { }
