#include "types.h"

// The unload and load hooks rel/flyer_collision_create.cpp's register puts in
// the editor record for TObjFlyerCollision. The volume loads nothing, so both
// are empty.

extern "C" void flyerColObjectUnload(void) { }

extern "C" void flyerColObjectLoad(void) { }
