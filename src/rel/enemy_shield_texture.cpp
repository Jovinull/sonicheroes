#include "game/enemy/e_database.h"

// ReleaseEnemyShieldTexture and LoadEnemyShieldTexture (the PS2 build's names):
// forget / find in the enemy database's pawn files (kind 6) the five models
// the broken shield's splinters are drawn with.

extern "C" RpClump* shieldSplinterModels[5];
extern "C" u32 shieldSplinterModelIds[5];

void ReleaseEnemyShieldTexture()
{
	int i;

	for (i = 0; i < 5; i++) {
		shieldSplinterModels[i] = NULL;
	}
}

void LoadEnemyShieldTexture()
{
	int i;

	for (i = 0; i < 5; i++) {
		shieldSplinterModels[i] = TEnemyDataBase::GetInstance()->SearchClump(
		    (eEnemyDataBase)6, shieldSplinterModelIds[i]);
	}
}
