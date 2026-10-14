#include "game/effect/eff_bomb.h"
#include "game/object.h"

// enemyShieldCalcDirection (ours; the PS2 build has no such ENEMY_SHIELD member):
// the shield's direction, the forward axis turned by its X then Y angles.

#include "src/rel/enemy_shield.inc"

struct RwMatrixTag {
	u8 data[0x40];
};

extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" const f32 enemyShieldRadToAngle[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019947C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);
extern "C" f32 fn_801991B4(RwV3d* v);
extern "C" double asin(double x);
extern "C" double atan2(double y, double x);

extern "C" void enemyShieldCalcDirection(ENEMY_SHIELD* shield)
{
	RwV3d forward;
	RwMatrixTag matrix;

	forward.z = enemyShieldOne[0];
	forward.y = forward.x = enemyShieldZero[0];
	fn_80195790(&matrix, &AxisX, enemyShieldOne[0] - fn_800D7AE4(shield->ang.x),
	    fn_800D7B00(shield->ang.x), 0);
	fn_80195790(&matrix, &AxisY, enemyShieldOne[0] - fn_800D7AE4(shield->ang.y),
	    fn_800D7B00(shield->ang.y), 2);
	fn_8019947C(&shield->dir, &forward, 1, &matrix);
}
