// TObjEnemy::Exec (symbol name from the retail map): an enemy that must be killed raises bit 0 of
// its TObject signal (HYPOTHESIS: the delete request); an asleep one only clears its collision
// info; otherwise the eight timers at +0x191 count down to 0 and Update runs.
#include "game/enemy/e_obj_enemy.h"

void TObjEnemy::Exec()
{
	if (KillMySelf()) {
		Signal |= 1;
	} else if (IsSleep()) {
		ClearInfo();
	} else {
		for (int i = 0; i < 8; i++) {
			if (timers[i] > 0) {
				timers[i]--;
			}
		}
		Update();
	}
}
