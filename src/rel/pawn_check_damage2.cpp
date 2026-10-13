#include "types.h"

// TObjEnemyPawn::CheckDamage2 (the PS2 build's name, by its member order): a
// broken pawn loses all its hit points and counts as damaged; otherwise the
// enemy base decides (CheckDamage2__9TObjEnemyFv).

typedef struct Pawn {
	u8 unk000[0x1A4];
	f32 hp; // 0x1A4
	u8 unk1A8[0x1D8];
	s32 broken; // 0x380
} Pawn;

extern "C" const f32 pawnZero[1];

extern "C" int CheckDamage2__9TObjEnemyFv(Pawn* pawn);

extern "C" int CheckDamage2__13TObjEnemyPawnFv(Pawn* pawn)
{
	if (pawn->broken != 0) {
		pawn->hp = pawnZero[0];
		return 1;
	}
	return CheckDamage2__9TObjEnemyFv(pawn);
}
