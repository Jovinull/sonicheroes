#include "game/enemy/e_database.h"

// TEnemyPowerCore::Initialize (the PS2 build's name), the same in the bonus
// stages (31D-33D): the power core's body and shine models and its UV
// animation come from the enemy database (kind 0); the body ignores lights,
// both models get the UV animation as their custom texture effect, and the
// animation frames restart.

struct UVFXInfo {
	RpUVAnimAnimation* anim; // 0x00
	u8 unk04[0x40];
}; // 0x44

struct PowerCoreAnim {
	s32 frame;      // 0x0
	s32 shineFrame; // 0x4
};

void SetClumpCustomFXTexture(RpClump* clump, UVFXInfo* info);
void objRpClumpForAllGeometrysToIgnoreLights(RpClump* clump);

extern "C" RpClump* powerCoreModels[2];
extern "C" RpUVAnimAnimation* powerCoreUVAnim;
extern "C" UVFXInfo powerCoreFX[2];
extern "C" PowerCoreAnim powerCoreAnimState;

extern "C" void Initialize__15TEnemyPowerCoreFv(void)
{
	powerCoreModels[0] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)0, 0xC);
	powerCoreModels[1] = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)0, 0xE);
	powerCoreUVAnim    = TEnemyDataBase::GetInstance()->SearchUVAnim((eEnemyDataBase)0, 0xD);
	if (powerCoreModels[0] != NULL) {
		objRpClumpForAllGeometrysToIgnoreLights(powerCoreModels[0]);
	}
	if (powerCoreModels[0] != NULL && powerCoreUVAnim != NULL) {
		powerCoreFX[0].anim = powerCoreUVAnim;
		SetClumpCustomFXTexture(powerCoreModels[0], &powerCoreFX[0]);
	}
	if (powerCoreModels[1] != NULL && powerCoreUVAnim != NULL) {
		powerCoreFX[1].anim = powerCoreUVAnim;
		SetClumpCustomFXTexture(powerCoreModels[1], &powerCoreFX[1]);
	}
	powerCoreAnimState.frame      = 0;
	powerCoreAnimState.shineFrame = 0;
}
