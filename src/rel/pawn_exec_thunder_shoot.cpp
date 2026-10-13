#include "types.h"

// TObjEnemyPawn::ExecThunderShoot (the PS2 build's name, by its member order):
// unless the pawn is in action 6 it runs the enemy base's step (fn_800A4F34)
// and eases its height towards the target one at its vertical speed; then it
// counts the shot down, returning 1 (and clearing the shooting flag) when it
// is over.

typedef struct Pawn {
	u8 unk000[0x144];
	f32 height; // 0x144
	u8 unk148[0x14];
	f32 riseSpeed; // 0x15C
	u8 unk160[0xEC];
	s8 action; // 0x24C
	u8 unk24D[0x47];
	f32 targetHeight; // 0x294
	u8 unk298[0x4C];
	s32 timer;    // 0x2E4
	s32 shooting; // 0x2E8
} Pawn;

extern "C" const f32 pawnNoHeight[1];

extern "C" void fn_800A4F34(Pawn* pawn);
f32 AdjustFloat(f32 value, f32 target, f32 rate);
extern "C" double __fabs(double x);

extern "C" int ExecThunderShoot__13TObjEnemyPawnFv(Pawn* pawn)
{
	if (pawn->action != 6) {
		fn_800A4F34(pawn);
		if (pawnNoHeight[0] != pawn->targetHeight) {
			double rate = __fabs(pawn->riseSpeed);

			pawn->height = AdjustFloat(pawn->height, pawn->targetHeight, rate);
		}
	}
	if (--pawn->timer < 0) {
		pawn->shooting = 0;
		return 1;
	}
	pawn->shooting = 1;
	return 0;
}
