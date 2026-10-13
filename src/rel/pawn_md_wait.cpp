#include "types.h"

// TObjEnemyPawn::EnemyMD_Wait (the PS2 build's name, by its member order):
// while in it (1), when the enemy base says the wait is over (fn_800A32AC) the
// pawn moves on (fn_800A4668) with the standing motion (0); otherwise it walks
// (motion 3) with the wander timer cleared.

typedef struct Pawn {
	u8 unk000[0xD4];
	s32 motion; // 0x0D4
	u8 unk0D8[0x228];
	s32 wanderTimer; // 0x300
} Pawn;

extern "C" int fn_800A32AC(Pawn* pawn);
extern "C" void fn_800A4668(Pawn* pawn);

extern "C" void EnemyMD_Wait__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(Pawn* pawn, int mode)
{
	switch (mode) {
		case 0:
			break;
		case 1:
			if (fn_800A32AC(pawn)) {
				fn_800A4668(pawn);
				pawn->motion = 0;
			} else {
				pawn->motion      = 3;
				pawn->wanderTimer = 0;
			}
			break;
		case 2:
			break;
		case 3:
			break;
	}
}
