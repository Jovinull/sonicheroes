#include "types.h"

// TObjEnemyPawn::WalkToAim (the PS2 build's name, by its member order):
// RunToAim's walking twin. It returns whether the pawn keeps walking (always
// for an inactive one); close to its aim or told to stop (status 4) it turns
// and stops, otherwise it heads on at the walking pace (0.5). After the enemy
// base's step and the landing check, a finished walk or, stopped or near the
// aim point, a pawn with nothing left to do picks its starting mode again
// (SelectInitialMode).

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct Pawn {
	u8 unk000[0x106];
	u16 status; // 0x106
	u8 unk108[0x38];
	RwV3d pos; // 0x140
	u8 unk14C[0x10];
	f32 riseSpeed; // 0x15C
	u8 unk160[0x48];
	f32 fallSpeed; // 0x1A8
	u8 unk1AC[0x38];
	RwV3d aim; // 0x1E4
	u8 unk1F0[0x58];
	s32 nextMode; // 0x248
	u8 unk24C[0x4];
	s32 runs; // 0x250
	u8 unk254[0x124];
	s32 active; // 0x378
} Pawn;

extern "C" const f32 pawnZero[1];
extern "C" const f32 pawnMinusOne[1];
extern "C" const f32 pawnLandScale[1];
extern "C" const f32 pawnRunReach[1];
extern "C" const f32 pawnAimReach[1];
extern "C" const f32 pawnWalkPace[1];

extern "C" f32 fn_800A5AC0(Pawn* pawn);
extern "C" void fn_800A4668(Pawn* pawn);
extern "C" void fn_800A4A8C(Pawn* pawn, f32 value);
extern "C" void fn_800A5C6C(Pawn* pawn, u32 flags);
extern "C" int fn_800A5888(Pawn* pawn, f32 value);
extern "C" void fn_800A5B50(Pawn* pawn, u32 flags);
extern "C" int fn_800A5998(Pawn* pawn);
extern "C" void SelectInitialMode__13TObjEnemyPawnFv(Pawn* pawn);
f32 DistanceP2P(const RwV3d* a, const RwV3d* b);

extern "C" int WalkToAim__13TObjEnemyPawnFv(Pawn* pawn)
{
	int walking = 1;

	if (pawn->active == 0) {
		return 1;
	}
	if (fn_800A5AC0(pawn) < pawnRunReach[0] || (pawn->status & 4)) {
		fn_800A4668(pawn);
		walking = 0;
	} else {
		fn_800A4A8C(pawn, pawnWalkPace[0]);
	}
	fn_800A5C6C(pawn, 0xF00);
	if ((pawn->status & 2) && pawn->riseSpeed < pawnLandScale[0] * pawn->fallSpeed) {
		pawn->riseSpeed = pawnZero[0];
	}
	if (fn_800A5888(pawn, pawnMinusOne[0])) {
		fn_800A5B50(pawn, 0xF00);
		SelectInitialMode__13TObjEnemyPawnFv(pawn);
	} else if ((pawn->status & 4) || DistanceP2P(&pawn->pos, &pawn->aim) < pawnAimReach[0]) {
		if (fn_800A5998(pawn) <= 0) {
			SelectInitialMode__13TObjEnemyPawnFv(pawn);
		}
	}
	return walking;
}
