#include "types.h"

// TObjEnemyPawn::EnemyMD_Ctrl (the PS2 build's name, by its member order):
// entering it (0) sets the walking motion (3) and clears the wander timer;
// while in it (1), in stage 0x15 only, it counts up and after 300 frames asks
// for mode 0x1D (fewer than three rounds so far) or starts over.

typedef struct GameState {
	u8 unk00[0x2C];
	s32 stage; // 0x2C
} GameState;

typedef struct Pawn {
	u8 unk000[0xD4];
	s32 motion; // 0x0D4
	u8 unk0D8[0x170];
	s32 nextMode; // 0x248
	u8 unk24C[0xB4];
	s32 wanderTimer; // 0x300
	u8 unk304[0x80];
	s32 ctrlTimer; // 0x384
	s32 rounds;    // 0x388
} Pawn;

namespace nSystem
{
void IncreaseTimer(int& timer);
}

extern "C" GameState lbl_8029C310;

extern "C" void EnemyMD_Ctrl__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(Pawn* pawn, int mode)
{
	switch (mode) {
		case 0:
			pawn->motion      = 3;
			pawn->wanderTimer = 0;
			break;
		case 1:
			if (lbl_8029C310.stage == 0x15) {
				nSystem::IncreaseTimer(pawn->ctrlTimer);
				if (pawn->ctrlTimer >= 300) {
					if (pawn->rounds < 3) {
						pawn->nextMode = 0x1D;
					} else {
						pawn->ctrlTimer = 0;
						pawn->rounds    = 0;
					}
				}
			}
			break;
		case 2:
			break;
		case 3:
			break;
	}
}
