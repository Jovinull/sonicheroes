#include "types.h"

// TObjEnemyPawn::AddScore (the PS2 build's name, by its member order): gives
// whoever broke the pawn its score: 400 (kinds 2 and 3) or 200, raised to 500
// or 300 for the stronger variant (0x38C).

class TEnemyScoreMan
{
public:
	static void CreateInstance();
	static TEnemyScoreMan* EnemyScoreMan;
	void AddScore(s32 playernumber, s32 score);
};

typedef struct Pawn {
	u8 unk000[0x230];
	s32 breaker; // 0x230
	u8 unk234[0x158];
	s8 variant; // 0x38C
	s8 kind;    // 0x38D
} Pawn;

static inline TEnemyScoreMan* pawnScoreMan()
{
	if (TEnemyScoreMan::EnemyScoreMan == NULL) {
		TEnemyScoreMan::CreateInstance();
	}
	return TEnemyScoreMan::EnemyScoreMan;
}

extern "C" void AddScore__13TObjEnemyPawnFv(Pawn* pawn)
{
	if (pawn->variant == 0) {
		switch (pawn->kind) {
			case 2:
			case 3:
				pawnScoreMan()->AddScore(pawn->breaker, 400);
				break;
			default:
				pawnScoreMan()->AddScore(pawn->breaker, 200);
				break;
		}
	} else {
		switch (pawn->kind) {
			case 2:
			case 3:
				pawnScoreMan()->AddScore(pawn->breaker, 500);
				break;
			default:
				pawnScoreMan()->AddScore(pawn->breaker, 300);
				break;
		}
	}
}
