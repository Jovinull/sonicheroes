#include "types.h"

// TObjEnemyPawn::EnemyMD_BiteNail (the PS2 build's name, by its member order):
// entering it (0) sets the nail-biting motion (0xB); while in it (1) the pawn
// bites its nails (BiteNail), playing their sound (0x400A) while it goes on and
// asking for mode 4 when it stops.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct Pawn {
	u8 unk000[0xD4];
	s32 motion; // 0x0D4
	u8 unk0D8[0x68];
	RwV3d pos; // 0x140
	u8 unk14C[0xFC];
	s32 nextMode; // 0x248
} Pawn;

extern "C" void* lbl_8042C388;

extern "C" int BiteNail__13TObjEnemyPawnFv(Pawn* pawn);
extern "C" void fn_800B4A38(void* sound, s32 id, RwV3d* pos, void* owner, s32 a, s32 b, s32 c);

extern "C" void EnemyMD_BiteNail__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(Pawn* pawn, int mode)
{
	switch (mode) {
		case 0:
			pawn->motion = 0xB;
			break;
		case 1:
			if (BiteNail__13TObjEnemyPawnFv(pawn) == 0) {
				pawn->nextMode = 4;
			} else if (lbl_8042C388 != NULL) {
				fn_800B4A38(lbl_8042C388, 0x400A, &pawn->pos, pawn, 3, 4, 4);
			}
			break;
		case 2:
			break;
		case 3:
			break;
	}
}
