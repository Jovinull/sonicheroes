#include "types.h"

// TObjEnemyPawn::EnemyMD_MgunFire (the PS2 build's name, by its member order):
// entering it (0) starts the gun; while in it (1) and active, the pawn turns
// towards its aim heading and keeps the gun on the muzzle and aimed
// (ExecMachineGun, inlined); leaving it (3) stops the gun.

#include "src/rel/pawn_machine_gun.inc"

int AdjustAngle(int value, int target, int step);

extern "C" void EnemyMD_MgunFire__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(Pawn* pawn, int mode)
{
	switch (mode) {
		case 0:
			if (pawn->gun != NULL) {
				pawn->gun->Run();
			}
			break;
		case 1:
			if (pawn->active != 0) {
				pawn->heading = AdjustAngle(pawn->heading, pawn->aimHeading, 0x100);
				ExecMachineGun__13TObjEnemyPawnFv(pawn);
			}
			break;
		case 2:
			break;
		case 3:
			if (pawn->gun != NULL) {
				pawn->gun->Stop();
			}
			break;
	}
}
