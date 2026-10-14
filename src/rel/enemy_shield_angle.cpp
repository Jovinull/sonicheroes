#include "types.h"

// ENEMY_SHIELD::CalcShieldAngle (the PS2 build's name): turns the shield to
// face along its direction vector, or flat when the vector is null.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

typedef struct EnemyShield {
	u8 unk000[0x110];
	sAngle ang; // 0x110
	u8 unk11C[0x4];
	RwV3d dir; // 0x120
} EnemyShield;

extern "C" const f32 enemyShieldZero[1];
extern "C" const f32 enemyShieldRadToAngle[1];

extern "C" f32 fn_801991B4(RwV3d* v);
extern "C" double asin(double x);
extern "C" double atan2(double y, double x);

extern "C" void CalcShieldAngle__12ENEMY_SHIELDFv(EnemyShield* shield)
{
	if (fn_801991B4(&shield->dir) > enemyShieldZero[0]) {
		shield->ang.x
		    = enemyShieldRadToAngle[0] * (f32)asin(-shield->dir.y / fn_801991B4(&shield->dir));
		shield->ang.y = enemyShieldRadToAngle[0] * (f32)atan2(shield->dir.x, shield->dir.z);
		shield->ang.z = 0;
	} else {
		shield->ang.x = shield->ang.y = shield->ang.z = 0;
	}
}
