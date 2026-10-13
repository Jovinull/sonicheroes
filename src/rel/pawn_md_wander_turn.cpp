#include "types.h"

// TObjEnemyPawn::EnemyMD_WanderTurn (the PS2 build's name, by its member
// order): while in it (1) the pawn searches for the player (TurnToAim, inlined) and,
// unless that picks mode 0xB, asks for mode 0xC.

#include "src/rel/pawn_seek.inc"

extern "C" void EnemyMD_WanderTurn__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(Pawn* pawn, int mode)
{
	switch (mode) {
		case 0:
			break;
		case 1:
			if (TurnToAim__13TObjEnemyPawnFv(pawn) != 0xB) {
				pawn->nextMode = 0xC;
			}
			break;
		case 2:
			break;
		case 3:
			break;
	}
}
