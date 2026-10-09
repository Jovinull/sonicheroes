// TObjBobJumpCollision's constructor, shared by rel/bob_jump_collision_create.cpp,
// which defines BOB_JUMP_COLLISION_CTOR as inline so the factory inlines it, and
// rel/bob_jump_collision_ctor.cpp, which defines it empty to emit the
// out-of-line copy each module also keeps.

BOB_JUMP_COLLISION_CTOR TObjBobJumpCollision::TObjBobJumpCollision(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjBobJumpCollision;
	DispTime  = 0xF8;

	BobJumpParam* param = (BobJumpParam*)ObjParam->setData.setBuffer;
	pos                 = ObjParam->setData.pos;
	ang                 = ObjParam->setData.ang;

	a     = param->a;
	b     = param->b;
	c     = param->c;
	depth = param->depth;
	unkB8 = 1;

	Init(&bobJumpCclInfo, 1, 4);
	if (info != NULL) {
		info->a        = a;
		info->b        = b;
		info->c        = c;
		info->center.z = c;
		CalcRange();
	}

	unkE4 = unkE8 = 0;
	unkEC = unkF0 = 0;

	preJump = new TObjBobPreJumpCollision(this);
}
