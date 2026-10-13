#include "types.h"

// TObjEnemyPawn::EnemyMD_Wander (the PS2 build's name, by its member order):
// entering it (0) sets the walking motion (3), clears the wander timer and
// sets the falling speed (-0.06); while in it (1) the enemy base picks a new
// heading (fn_800A50C0 with -1), the target slot is cleared and the pawn asks
// for mode 0xB.

typedef struct Pawn {
	u8 unk000[0xD4];
	s32 motion; // 0x0D4
	u8 unk0D8[0x84];
	f32 riseSpeed; // 0x15C
	u8 unk160[0x30];
	s8 target; // 0x190
	u8 unk191[0xB7];
	s32 nextMode; // 0x248
	u8 unk24C[0xB4];
	s32 wanderTimer; // 0x300
} Pawn;

extern "C" const f32 pawnWanderFall[1];
extern "C" const f32 pawnMinusOne[1];

extern "C" void fn_800A50C0(Pawn* pawn, f32 value);

extern "C" void EnemyMD_Wander__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(Pawn* pawn, int mode)
{
	switch (mode) {
		case 0:
			pawn->motion      = 3;
			pawn->wanderTimer = 0;
			pawn->riseSpeed   = pawnWanderFall[0];
			break;
		case 1:
			fn_800A50C0(pawn, pawnMinusOne[0]);
			pawn->target   = -1;
			pawn->nextMode = 0xB;
			break;
		case 2:
			break;
		case 3:
			break;
	}
}
