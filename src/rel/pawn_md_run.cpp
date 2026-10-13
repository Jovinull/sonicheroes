#include "types.h"

// TObjEnemyPawn::EnemyMD_Run (the PS2 build's name, by its member order):
// while in it (1) the pawn runs (motion 4), or in its other gait (0x24E == 1)
// switches to the dash motion (0xE, unless already in 0xE/0xF) with its sound
// (0x400B); it runs to its aim and asks for mode 10 once there.

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
	u8 unk24C[0x2];
	s8 gait; // 0x24E
} Pawn;

extern "C" void* lbl_8042C388;

extern "C" int RunToAim__13TObjEnemyPawnFv(Pawn* pawn);
extern "C" void fn_800B4A38(void* sound, s32 id, RwV3d* pos, void* owner, s32 a, s32 b, s32 c);

extern "C" void EnemyMD_Run__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(Pawn* pawn, int mode)
{
	switch (mode) {
		case 0:
			break;
		case 1:
			if (pawn->gait != 1) {
				pawn->motion = 4;
			} else if (pawn->currentMotion != 0xE && pawn->currentMotion != 0xF) {
				pawn->motion = 0xE;
				if (lbl_8042C388 != NULL) {
					fn_800B4A38(lbl_8042C388, 0x400B, &pawn->pos, pawn, 3, 0, 0x3C);
				}
			}
			if (RunToAim__13TObjEnemyPawnFv(pawn) == 0) {
				pawn->nextMode = 10;
			}
			break;
		case 2:
			break;
		case 3:
			break;
	}
}
