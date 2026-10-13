#include "types.h"

// TObjEnemyPawn::EnemyMD_Turn (the PS2 build's name, by its member order):
// entering it (0) starts the turn (fn_800A51E4 with 5 and -1), sets the walking
// motion (3), clears the wander timer and sets the falling speed; while in it
// (1) the pawn searches for the player (pawnSeek) and asks for the new mode
// when it changed.

#include "src/rel/pawn_seek.inc"

extern "C" const f32 pawnWanderFall[1];

extern "C" void fn_800A51E4(Pawn* pawn, int a, int b);

extern "C" void EnemyMD_Turn__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(Pawn* pawn, int mode)
{
	switch (mode) {
		case 0:
			fn_800A51E4(pawn, 5, -1);
			pawn->motion      = 3;
			pawn->wanderTimer = 0;
			pawn->riseSpeed   = pawnWanderFall[0];
			break;
		case 1: {
			int old  = pawn->state;
			int next = pawnSeek(pawn, old);

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
