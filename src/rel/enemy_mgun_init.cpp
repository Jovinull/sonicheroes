#include "types.h"

// ENEMY_MGUN::Init (the PS2 build's name): places and turns the gun, sizes its
// collision for the bullet speed, works out its fire vector, clears the
// bullets, and takes the common enemy file's models 8 (as it is) and 9 (a
// copy), both drawn without lights.

#include "src/rel/enemy_mgun.inc"
#include "game/enemy/e_database.h"

extern "C" const f32 enemyMGunRangePad[1];

extern "C" void* memset(void* dst, s32 value, u32 size);
extern "C" RpClump* fn_80150588(RpClump* clump);
void objRpClumpForAllGeometrysToIgnoreLights(RpClump* clump);

void ENEMY_MGUN::Init(const RwV3d* place, const sAngle* turn)
{
	pos.x = place->x;
	pos.y = place->y;
	pos.z = place->z;
	angle = *turn;
	SetRange(enemyMGunRangePad[0] + speed);
	CalcFireVector();
	posCenter.x = pos.x;
	posCenter.y = pos.y;
	posCenter.z = pos.z;
	unk128      = 4;
	bulletNum   = 0;
	memset(bullets, 0, sizeof(bullets));
	model = TEnemyDataBase::GetInstance()->SearchClump(ENEMY_DB_COMMON, 8);
	if (model != NULL) {
		objRpClumpForAllGeometrysToIgnoreLights(model);
	}
	RpClump* source = TEnemyDataBase::GetInstance()->SearchClump(ENEMY_DB_COMMON, 9);
	if (source != NULL) {
		clump = fn_80150588(source);
		objRpClumpForAllGeometrysToIgnoreLights(clump);
	}
}
