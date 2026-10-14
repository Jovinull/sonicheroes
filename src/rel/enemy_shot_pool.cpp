#include "game/enemy/e_database.h"

// EndEnemyShot and InitEnemyShot (the PS2 build's names): forget / find the
// enemy shot's two models (the shot and its glow, from the common enemy file),
// the glow's textured material and the shot's two atomics, with lighting off,
// and clear the live shot count. The enemyShot* names are ours.

struct RpAtomic;
struct RpMaterial;

RpMaterial* objRpClumpGetMaterialWithSpecificTexture(RpClump* clump, RpMaterial* after, char* name);
RpAtomic* objRpClumpGetAtomic(RpClump* clump, RpAtomic* after);
void objRpClumpForAllGeometrysToIgnoreLights(RpClump* clump);

extern "C" const u32 enemyShotModelIds[2];
extern "C" RpClump* enemyShotClumps[2];
extern "C" RpAtomic* enemyShotAtomics[2];
extern "C" RpMaterial* enemyShotMaterial;
extern "C" s16 enemyShotCount;

void EndEnemyShot()
{
	int i;

	for (i = 0; i < 2; i++) {
		if (enemyShotClumps[i] != NULL) {
			enemyShotClumps[i] = NULL;
		}
	}
	enemyShotAtomics[0] = enemyShotAtomics[1] = NULL;
	enemyShotCount                            = 0;
}

void InitEnemyShot()
{
	RpClump* clump;
	int i;

	for (i = 0; i < 2; i++) {
		enemyShotClumps[i]
		    = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)0, enemyShotModelIds[i]);
	}
	if (enemyShotClumps[1] != NULL) {
		enemyShotMaterial
		    = objRpClumpGetMaterialWithSpecificTexture(enemyShotClumps[1], NULL, NULL);
		objRpClumpForAllGeometrysToIgnoreLights(enemyShotClumps[1]);
	}
	if ((clump = enemyShotClumps[0]) != NULL) {
		enemyShotAtomics[0] = objRpClumpGetAtomic(clump, NULL);
		enemyShotAtomics[1] = objRpClumpGetAtomic(clump, enemyShotAtomics[0]);
		objRpClumpForAllGeometrysToIgnoreLights(enemyShotClumps[0]);
	}
	enemyShotCount = 0;
}
