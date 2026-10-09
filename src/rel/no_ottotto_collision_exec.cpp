// TObjSetNoOttottoCollision's TDisp (empty) and Exec. Out of range or due to
// be killed, the volume raises its kill bit; placed in the editor, it follows
// the placement; otherwise it keeps the collision's last position, moves the
// collision to its own position and angle and enters it (C_COLLI::Entry). The
// class is shared through no_ottotto_collision_class.inc.

#define NO_OTTOTTO_COLLISION_CTOR inline
#define NO_OTTOTTO_EDIT_FIRST
#include "src/rel/no_ottotto_collision_class.inc"

void TObjSetNoOttottoCollision::TDisp() { }

void TObjSetNoOttottoCollision::Exec()
{
	if (CheckRangeOut() || CheckMustKill()) {
		Signal |= 1;
	} else if (OnEdit()) {
		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;
	} else {
		C_COLLI::pre_pos = C_COLLI::pos;
		C_COLLI::pos     = pos;
		C_COLLI::ang     = ang;
		Entry();
	}
}
