#include "types.h"

// TObjEnemyPawn::EnemyMD_FallLand (the PS2 build's name, by its member order):
// entering it (0) sets the landing motion (6); while in it (1), once the
// landing motion is over the pawn asks for mode 1.

typedef struct Pawn {
	u8 unk000[0xD0];
	s32 currentMotion; // 0x0D0
	s32 motion;        // 0x0D4
	u8 unk0D8[0x170];
	s32 nextMode; // 0x248
} Pawn;

extern "C" void EnemyMD_FallLand__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(Pawn* pawn, int mode)
{
	switch (mode) {
		case 0:
			pawn->motion = 6;
			break;
		case 1:
			if (pawn->currentMotion != 6) {
				pawn->nextMode = 1;
			}
			break;
		case 2:
			break;
		case 3:
			break;
	}
}
