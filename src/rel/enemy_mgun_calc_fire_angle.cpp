#include "types.h"

// ENEMY_MGUN::CalcFireAngle (the PS2 build's name): the firing angles from
// the aim vector, its pitch from the vector's height over its length and its
// yaw from its X and Z; all zero for a zero vector.

#include "src/rel/enemy_mgun.inc"

extern "C" const f32 enemyMGunZero[1];
extern "C" const f32 enemyMGunRadToAngle[1];

extern "C" f32 fn_801991B4(RwV3d* v);
extern "C" double asin(double x);
extern "C" double atan2(double y, double x);

void ENEMY_MGUN::CalcFireAngle()
{
	if (fn_801991B4(&aim) > enemyMGunZero[0]) {
		angle.x = enemyMGunRadToAngle[0] * (f32)asin(-aim.y / fn_801991B4(&aim));
		angle.y = enemyMGunRadToAngle[0] * (f32)atan2(aim.x, aim.z);
		angle.z = 0;
	} else {
		angle.x = angle.y = angle.z = 0;
	}
}
