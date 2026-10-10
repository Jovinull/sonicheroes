#include "types.h"

// The reset, unload and load hooks rel/system_object4_register.cpp puts in the
// systemObject4's editor record. The empty hooks have nothing to do: the object
// loads nothing.

extern "C" void systemObject4Reset(void) { }

extern "C" void systemObject4Unload(void) { }

extern "C" void systemObject4Load(void) { }
