#include "types.h"

// HAWK_MGUN::CalcBullet (the PS2 build's name): the bullets whose life ran out
// are replaced by the last one, then every bullet left moves.

#include "src/rel/hawk_mgun.inc"

void HAWK_MGUN::CalcBullet()
{
	s32 i;

	for (i = 0; i < bulletNum;) {
		if (bullets[i].Alive() == false) {
			bullets[i] = bullets[bulletNum - 1];
			bulletNum--;
		} else {
			i++;
		}
	}
	for (i = 0; i < bulletNum; i++) {
		bullets[i].Move();
	}
}
