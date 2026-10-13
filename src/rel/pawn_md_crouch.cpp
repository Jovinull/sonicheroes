#include "types.h"

// TObjEnemyPawn::EnemyMD_Crouch (the PS2 build's name, by its member order):
// entering the mode (0) sets the crouching motion (1); the other phases (1 to 3)
// do nothing.

typedef struct Pawn {
	u8 unk00[0xD4];
	s32 motion; // 0xD4
} Pawn;

extern "C" void EnemyMD_Crouch__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(Pawn* pawn, int mode)
{
	switch (mode) {
		case 0:
			pawn->motion = 1;
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
	}
}
