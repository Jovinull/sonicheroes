#include "types.h"

// HAWK_MGUN's Normal and PDisp (the PS2 build's names): Normal moves the gun
// while it is firing and then the bullets; PDisp draws nothing.

#include "src/rel/hawk_mgun.inc"

void HAWK_MGUN::Normal()
{
	if (active == 1) {
		Move();
	}
	CalcBullet();
}

void HAWK_MGUN::PDisp() { }
