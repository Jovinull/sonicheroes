#include "types.h"

// TObjEnemyPawn::EnemyMD_WarpOut (the PS2 build's name, by its member order):
// entering it (0) starts the warp effect (fn_80062894 kind 0x20) at the pawn
// and clears the warp counter; leaving it (3) plays the warp sound (0x405E).

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct Pawn {
	u8 unk000[0x140];
	RwV3d pos; // 0x140
	u8 unk14C[0x104];
	s32 warpCount; // 0x250
} Pawn;

extern "C" void* lbl_8042C388;
extern "C" const RwV3d pawnWarpAngle;

extern "C" void fn_80062894(s32 kind, RwV3d* pos, RwV3d* angle);
extern "C" void fn_800B4A38(void* sound, s32 id, RwV3d* pos, void* owner, s32 a, s32 b, s32 c);

extern "C" void EnemyMD_WarpOut__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(Pawn* pawn, int mode)
{
	switch (mode) {
		case 0: {
			RwV3d angle = pawnWarpAngle;

			fn_80062894(0x20, &pawn->pos, &angle);
			pawn->warpCount = 0;
			break;
		}
		case 3:
			if (lbl_8042C388 != NULL) {
				fn_800B4A38(lbl_8042C388, 0x405E, &pawn->pos, NULL, 1, 0, 0);
			}
			break;
	}
}
