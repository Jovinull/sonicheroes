#include "game/obj_bob_jump_collision.h"

// TObjBobJumpCollision's constructor, out of line: the copy each of the twelve
// modules keeps next to the inlined one in bobJumpCollisionObjectCreate
// (rel/bob_jump_collision_create.cpp). The body is shared through
// bob_jump_collision_ctor.inc.

#define BOB_JUMP_COLLISION_CTOR
#include "src/rel/bob_jump_collision_ctor.inc"
