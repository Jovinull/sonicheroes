#include "types.h"

// TObjEnemyPawn::EnemyMD_ShotFire (the PS2 build's name, by its member order):
// entering it (0) clears the shot counter, sets the firing motion (0x11) and
// tells the weapon to fire (3); while in it (1), once the weapon is done (state
// 2, or state 3 with its flag 2) the pawn asks for mode 10.

typedef struct PawnWeapon {
	u8 unk00[0x10];
	u32 flags; // 0x10
	u8 unk14[0x4];
	s32 state;   // 0x18
	s32 command; // 0x1C
} PawnWeapon;

typedef struct Pawn {
	u8 unk000[0xD4];
	s32 motion; // 0x0D4
	u8 unk0D8[0x170];
	s32 nextMode; // 0x248
	u8 unk24C[0x18];
	s32 shots; // 0x264
	u8 unk268[0x18];
	PawnWeapon* weapon; // 0x280
} Pawn;

extern "C" void EnemyMD_ShotFire__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(Pawn* pawn, int mode)
{
	switch (mode) {
		case 0:
			pawn->shots           = 0;
			pawn->motion          = 0x11;
			pawn->weapon->command = 3;
			break;
		case 1: {
			PawnWeapon* weapon = pawn->weapon;

			if (weapon->state == 2 || (weapon->state == 3 && (weapon->flags & 2))) {
				pawn->nextMode = 10;
			}
			break;
		}
		case 2:
			break;
		case 3:
			break;
	}
}
