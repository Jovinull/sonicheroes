#include "game/effect/eff_bomb.h"
#include "game/object.h"

// ENEMY_SHIELD::Normal (the PS2 build's name): the shield's normal state: it
// faces along its direction (CalcShieldAngle, inlined) and resizes its
// collision when its scale changed.

#include "src/rel/enemy_shield.inc"

extern "C" const f32 enemyShieldRadToAngle[1];

extern "C" f32 fn_801991B4(RwV3d* v);
extern "C" double asin(double x);
extern "C" double atan2(double y, double x);

void ENEMY_SHIELD::Normal()
{
	if (fn_801991B4(&dir) > enemyShieldZero[0]) {
		ang.x = enemyShieldRadToAngle[0] * (f32)asin(-dir.y / fn_801991B4(&dir));
		ang.y = enemyShieldRadToAngle[0] * (f32)atan2(dir.x, dir.z);
		ang.z = 0;
	} else {
		ang.x = ang.y = ang.z = 0;
	}
	if (info->a != scale) {
		info->a = scale;
		CalcRange();
	}
}
