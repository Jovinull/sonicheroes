#include "types.h"

// TObjEnemyPawn::EnemyMD_MgunReady (the PS2 build's name, by its member order):
// entering it (0) picks the gun sweep around the pawn's heading (a sixth to a
// quarter turn each way by gait, starting on the player's side; the direction
// check is CheckDirectionOfPlayerRangeIn, inlined) and sets motion 3; while in
// it (1) and active, the pawn turns to the sweep's start and raises its
// shoulder.

#include "src/rel/pawn_check_direction.inc"

int AdjustAngle(int value, int target, int step);

extern "C" void EnemyMD_MgunReady__13TObjEnemyPawnFQ29TObjEnemy10eCtrlSMode(Pawn* pawn, int mode)
{
	switch (mode) {
		case 0: {
			int side = 1;
			int sweep;

			if (!CheckDirectionOfPlayerRangeIn__13TObjEnemyPawnFv(pawn)) {
				side *= -1;
			}
			switch (pawn->gait) {
				case 3:
					sweep           = side * 0x2000;
					pawn->sweepFrom = sweep + pawn->heading;
					pawn->sweepTo   = pawn->heading - sweep;
					break;
				case 4:
					sweep           = side * 0x2AAA;
					pawn->sweepFrom = sweep + pawn->heading;
					pawn->sweepTo   = pawn->heading - sweep;
					break;
				case 5:
					sweep           = side * 0x3555;
					pawn->sweepFrom = sweep + pawn->heading;
					pawn->sweepTo   = pawn->heading - sweep;
					break;
				case 6:
					sweep           = side * 0x4000;
					pawn->sweepFrom = sweep + pawn->heading;
					pawn->sweepTo   = pawn->heading - sweep;
					break;
				default:
					sweep           = side * 0x2000;
					pawn->sweepFrom = sweep + pawn->heading;
					pawn->sweepTo   = pawn->heading - sweep;
					break;
			}
			pawn->motion = 3;
			break;
		}
		case 1:
			if (pawn->active != 0) {
				pawn->heading       = AdjustAngle(pawn->heading, pawn->sweepFrom, 0x100);
				pawn->shoulderPitch = AdjustAngle(pawn->shoulderPitch, -0x800, 0x100);
			}
			break;
		case 2:
		case 3:
			break;
	}
}
