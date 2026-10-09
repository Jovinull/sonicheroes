#include "game/obj_bob_jump_collision.h"

// bobJumpCollisionObjectCreate, the factory the editor record for
// TObjBobJumpCollision points at; the classes are in
// game/obj_bob_jump_collision.h.
//
// It is the same 143 instructions in twelve of the stage modules that share the
// engine core, at their own address in each, so each module's splits.txt names
// its own range.
//
// Both allocations are real new-expressions of C++ classes with constructors
// the compiler inlines, which is what gives the original's `mr r0, r3` and then
// a copy into the register the construction runs on; rel/sample1_create.cpp
// has the long form.

#define BOB_JUMP_COLLISION_CTOR inline
#include "src/rel/bob_jump_collision_ctor.inc"

extern "C" void bobJumpCollisionObjectCreate(void)
{
	new TObjBobJumpCollision(lbl_8042C110);
}
