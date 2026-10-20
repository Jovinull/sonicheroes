#include "types.h"

// ENEMY_MGUN::CalcFireVector (the PS2 build's name): the aim vector from the
// firing angles, the bullet speed along Z turned by the pitch and then the
// yaw.

#include "src/rel/enemy_mgun.inc"

struct RwMatrixTag {
	u8 data[0x40];
};

extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const f32 enemyMGunZero[1];
extern "C" const f32 enemyMGunOne[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019947C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);

void ENEMY_MGUN::CalcFireVector()
{
	RwV3d vector;
	RwMatrixTag matrix;
	f32 sin;

	vector.z = speed;
	vector.y = vector.x = enemyMGunZero[0];
	sin                 = fn_800D7B00(angle.x);
	fn_80195790(&matrix, &AxisX, enemyMGunOne[0] - fn_800D7AE4(angle.x), sin, 0);
	sin = fn_800D7B00(angle.y);
	fn_80195790(&matrix, &AxisY, enemyMGunOne[0] - fn_800D7AE4(angle.y), sin, 2);
	fn_8019947C(&aim, &vector, 1, &matrix);
}
