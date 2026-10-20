#include "types.h"

// ENEMY_MGUN::CalcBullet (the PS2 build's name): drops every dead bullet (the
// last one takes its place) and moves the rest.

#include "src/rel/enemy_mgun.inc"

void ENEMY_MGUN::CalcBullet()
{
	int i;

	for (i = 0; i < bulletNum;) {
		if (!bullets[i].Alive()) {
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
