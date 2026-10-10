// TObjBobJumpCollision's BobJumpCollisionParameter and SetParameter (the PS2
// build's names): the box's shape from its extents, and the placement's
// position, angle and parameters. The constructor
// (rel/bob_jump_collision_ctor.inc) does both inline; these copies have no
// caller and are kept with force_active. The class is in
// game/obj_bob_jump_collision.h.

#include "game/obj_bob_jump_collision.h"

void TObjBobJumpCollision::BobJumpCollisionParameter()
{
	if (info != NULL) {
		info->a        = a;
		info->b        = b;
		info->c        = c;
		info->center.z = c;
		CalcRange();
	}
}

void TObjBobJumpCollision::SetParameter()
{
	BobJumpParam* param = (BobJumpParam*)ObjParam->setData.setBuffer;
	pos                 = ObjParam->setData.pos;
	ang                 = ObjParam->setData.ang;

	a     = param->a;
	b     = param->b;
	c     = param->c;
	depth = param->depth;
}
