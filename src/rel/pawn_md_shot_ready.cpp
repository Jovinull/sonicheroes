#include "types.h"

// TObjEnemyPawn::EnemyMD_ShotReady (the PS2 build's name, by its member
// order): entering it (0) clears the shot counter and sets the aiming motion
// (0x10); while in it (1) the pawn readies its shot (ExecShotReady).

typedef struct Pawn {
	u8 unk000[0xD4];
	s32 motion; // 0x0D4
	u8 unk0D8[0x18C];
	s32 shots; // 0x264
} Pawn;

extern "C" void ExecShotReady__13TObjEnemyPawnFv(Pawn* pawn);

extern "C" void EnemyMD_ShotReady__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(Pawn* pawn, int mode)
{
	switch (mode) {
		case 0:
			pawn->shots  = 0;
			pawn->motion = 0x10;
			break;
		case 1:
			ExecShotReady__13TObjEnemyPawnFv(pawn);
			break;
		case 2:
			break;
		case 3:
			break;
	}
}
