#include "types.h"

// The unload and load hooks rel/capture_collision_register.cpp puts in the
// editor record for TObjCaptureCollision. The volume loads nothing, so both are
// empty.

extern "C" void captureCollisionUnload(void) { }

extern "C" void captureCollisionLoad(void) { }
