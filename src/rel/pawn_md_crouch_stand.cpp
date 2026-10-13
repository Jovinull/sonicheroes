#include "types.h"

// TObjEnemyPawn::EnemyMD_CrouchStand (the PS2 build's name, by its member
// order): entering it (0) sets the standing-up motion (2) and plays its sound
// (0x4007) at the pawn; while in it (1), once that motion is over the pawn
// asks for mode 1.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct Pawn {
	u8 unk000[0xD0];
	s32 currentMotion; // 0x0D0
	s32 motion;        // 0x0D4
	u8 unk0D8[0x68];
	RwV3d pos; // 0x140
	u8 unk14C[0xFC];
	s32 nextMode; // 0x248
} Pawn;

extern "C" void* lbl_8042C388;

extern "C" void fn_800B4A38(void* sound, s32 id, RwV3d* pos, void* owner, s32 a, s32 b, s32 c);

extern "C" void EnemyMD_CrouchStand__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(Pawn* pawn, int mode)
{
	switch (mode) {
		case 0:
			pawn->motion = 2;
			if (lbl_8042C388 != NULL) {
				fn_800B4A38(lbl_8042C388, 0x4007, &pawn->pos, NULL, 1, 0, 0);
			}
			break;
		case 1:
			if (pawn->currentMotion != 2) {
				pawn->nextMode = 1;
			}
			break;
		case 2:
			break;
		case 3:
			break;
	}
}
