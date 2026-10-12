#include "types.h"

// The unload and load hooks rel/bob_jump_collision_register.cpp puts in the
// editor record for TObjBobJumpCollision. The jump loads nothing, so both are
// empty.

extern "C" void bobJumpCollisionObjectUnload(void) { }

extern "C" void bobJumpCollisionObjectLoad(void) { }
