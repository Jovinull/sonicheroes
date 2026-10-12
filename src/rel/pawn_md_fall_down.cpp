#include "types.h"

// TObjEnemyPawn::EnemyMD_FallDown (the PS2 build's name, by its member order):
// entering it (0) sets the falling motion (5), shows the model, flags the fall
// and its shadow; while in it (1) the pawn asks for mode 0x13 once the enemy
// base says it has landed (fn_800A3684).

typedef struct RpClump RpClump;

typedef struct PawnShadow {
	u8 unk000[0x184];
	s32 active; // 0x184
} PawnShadow;

typedef struct Pawn {
	u8 unk000[0xD4];
	s32 motion; // 0x0D4
	u8 unk0D8[0x10];
	RpClump* clump; // 0x0E8
	u8 unk0EC[0x15C];
	s32 nextMode; // 0x248
	u8 unk24C[0x1C];
	PawnShadow* shadow; // 0x268
	u8 unk26C[0x80];
	s32 falling; // 0x2EC
} Pawn;

void objRpClumpForAllAtomicsToRender(RpClump* clump);
extern "C" int fn_800A3684(Pawn* pawn);

extern "C" void EnemyMD_FallDown__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(Pawn* pawn, int mode)
{
	switch (mode) {
		case 0:
			pawn->motion = 5;
			objRpClumpForAllAtomicsToRender(pawn->clump);
			pawn->falling = 1;
			if (pawn->shadow != NULL) {
				pawn->shadow->active = 1;
			}
			break;
		case 1:
			if (fn_800A3684(pawn)) {
				pawn->nextMode = 0x13;
			}
			break;
		case 2:
			break;
		case 3:
			break;
	}
}
