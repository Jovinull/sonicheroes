// TObjBobPreJumpCollision::BobJumpCollisionParameter (the PS2 build's name):
// the pre-jump box takes its size from the jump it belongs to, mirrored forward
// of it. The constructor in game/obj_bob_jump_collision.h does the same inline;
// this copy has no caller and is kept with force_active.

#include "game/obj_bob_jump_collision.h"

void TObjBobPreJumpCollision::BobJumpCollisionParameter()
{
	if (info != NULL) {
		info->a        = owner->a;
		info->b        = owner->b;
		info->c        = owner->depth;
		info->center.z = -owner->depth;
		CalcRange();
	}
}
