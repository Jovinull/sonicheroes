#include "types.h"

// HintBall::CreateBalls, the PS2 build's name and signature. It makes the hint
// ring's twelve balls round the ring: each new ball (from the emitter's own
// virtual) gets its angle round the ring from the given start, its point (the
// ball offset turned about Y by the ring's yaw and about Z by its angle, at the
// ring's position), the ring's position, the given speed and its spread, a
// spin from the yaw, and the given life. It stops at the first ball it cannot
// get.

struct RwV3d {
	f32 x, y, z;
};

struct sRealAngle3 {
	f32 x, y, z;
};

struct RwMatrixTag {
	u8 data[0x40];
};

struct HintBallParticle {
	u8 unk00[0xC];
	s16 spin;  // 0x0C
	s16 angle; // 0x0E
	u8 unk10[0x4];
	f32 spread;  // 0x14
	f32 speed;   // 0x18
	RwV3d point; // 0x1C
	f32 unk28;   // 0x28
	u8 unk2C[0x4];
	RwV3d pos; // 0x30
	f32 life;  // 0x3C
};

class HintBall
{
public:
	u8 unk00[0x54];
	virtual void vslot0();
	virtual void vslot1();
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual HintBallParticle* NewParticle();
	u8 unk58[0x24];
	HintBallParticle* balls[12]; // 0x7C

	void CreateBalls(RwV3d* pos, sRealAngle3* angle, int start, float speed, float life);
};

extern "C" const RwV3d AxisY;
extern "C" const RwV3d AxisZ;
extern "C" const f32 hintBallOne[1];
extern "C" const f32 hintBallOffsetXZ[1];
extern "C" const f32 hintBallOffsetY[1];
extern "C" const f32 hintBallSpinScale[1];
extern "C" const f32 hintBallSpreadScale[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80195A74(RwMatrixTag* matrix, const RwV3d* axis, f32 angle, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, RwV3d* translation, s32 combine);
void CalcPoint(const RwMatrixTag* matrix, const RwV3d* point, RwV3d* out);

void HintBall::CreateBalls(RwV3d* pos, sRealAngle3* angle, int start, float speed, float life)
{
	RwMatrixTag matrix;
	RwV3d offset;
	int i;

	for (i = 0; i < 12; i++) {
		f32 sin;
		f32 spread = hintBallSpreadScale[0] * speed;
		HintBallParticle* ball;

		balls[i] = NewParticle();
		ball     = balls[i];
		if (ball == NULL) {
			return;
		}
		ball->angle = (u16)(start + i * 0x10000 / 12);
		fn_80196050(&matrix, pos, 0);
		fn_80195A74(&matrix, &AxisY, angle->y, 1);
		sin = fn_800D7B00(ball->angle + 0x4000);
		fn_80195790(&matrix, &AxisZ, hintBallOne[0] - fn_800D7AE4(ball->angle + 0x4000), sin, 1);
		offset.x = offset.z = hintBallOffsetXZ[0];
		offset.y            = hintBallOffsetY[0];
		CalcPoint(&matrix, &offset, &ball->point);
		ball->pos    = *pos;
		ball->speed  = speed;
		ball->spread = spread;
		ball->spin   = (s16)(s32)(hintBallSpinScale[0] * angle->y);
		ball->unk28  = hintBallOffsetXZ[0];
		ball->life   = life;
	}
}
