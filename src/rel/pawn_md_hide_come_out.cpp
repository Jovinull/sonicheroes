#include "types.h"

// TObjEnemyPawn::EnemyMD_HideComeOut (the PS2 build's name, by its member
// order): entering it (0) sets the running motion (4); while in it (1) the
// pawn searches for the player (TurnToAim, inlined) and asks for the new mode when it
// changed.

#include "src/rel/pawn_seek.inc"

extern "C" void EnemyMD_HideComeOut__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(Pawn* pawn, int mode)
{
	switch (mode) {
		case 0:
			pawn->motion = 4;
			break;
		case 1: {
			int old  = pawn->state;
			int next = TurnToAim__13TObjEnemyPawnFv(pawn);

			if (old != next) {
				pawn->nextMode = next;
			}
			break;
		}
		case 2:
			break;
		case 3:
			break;
	}
}
