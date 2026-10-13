// HintBall's layout and CreateBalls, shared by rel/hint_ball_create_balls.cpp
// (the out-of-line copy) and rel/hint_ball_ctor.cpp (the constructor, which
// inlines it). It is inline here and defined plain by the unit that emits the
// copy. The particle base is the main build's PARTICLE_MATERIAL (its constructor
// takes the particle flags and sprite, as the PS2 build names it); its sixth
// virtual makes a particle instance. PARTICLE_MATERIAL's destructor matters: the
// constructor then guards the base, and its loop indexes the balls from `this`
// (an offset register) as the retail does.

struct RwV3d {
	f32 x, y, z;
};

struct sRealAngle3 {
	f32 x, y, z;
};

struct RwMatrixTag {
	u8 data[0x40];
};

enum Pt_FLAGS {
	PT_FLAGS_NONE
};

struct SPRITE_INFO;

struct PARTICLE_INSTANCE {
	u8 unk00[0xC];
	s16 spin;    // 0x0C
	s16 angle;   // 0x0E
	u8 unk10[0x4];
	f32 spread;  // 0x14
	f32 speed;   // 0x18
	RwV3d point; // 0x1C
	f32 unk28;   // 0x28
	u8 unk2C[0x4];
	RwV3d pos; // 0x30
	f32 life;  // 0x3C
};

class ParticleHeader
{
public:
	u8 unk00[0xC];
	s16 unkC; // 0x0C
	s16 unkE; // 0x0E
	u8 unk10[0x44];
};

class PARTICLE_MATERIAL : public ParticleHeader
{
public:
	PARTICLE_MATERIAL(Pt_FLAGS flags, SPRITE_INFO* sprite);
	~PARTICLE_MATERIAL();

	virtual void MoveManager();
	virtual void DispManager();
	virtual s32 Move(PARTICLE_INSTANCE* instance);
	virtual void Disp(PARTICLE_INSTANCE* instance);
	virtual PARTICLE_INSTANCE* AllocInstance();
	virtual PARTICLE_INSTANCE* CreateInstance();
};

class HintBall : public PARTICLE_MATERIAL
{
public:
	u8 unk58[0x24];
	PARTICLE_INSTANCE* balls[12]; // 0x7C

	HintBall(RwV3d* pos, sRealAngle3* angle, int start, float speed, float life, Pt_FLAGS flags,
	    SPRITE_INFO* sprite);
	void CreateBalls(RwV3d* pos, sRealAngle3* angle, int start, float speed, float life);
	virtual s32 Move(PARTICLE_INSTANCE* instance);
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
extern "C" void fn_80195790(RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_80195A74(RwMatrixTag* matrix, const RwV3d* axis, f32 angle, s32 combine);
extern "C" void fn_80196050(RwMatrixTag* matrix, RwV3d* translation, s32 combine);
void CalcPoint(const RwMatrixTag* matrix, const RwV3d* point, RwV3d* out);

#ifndef HINT_BALL_CREATE_INLINE
#define HINT_BALL_CREATE_INLINE inline
#endif

HINT_BALL_CREATE_INLINE void HintBall::CreateBalls(
    RwV3d* pos, sRealAngle3* angle, int start, float speed, float life)
{
	RwMatrixTag matrix;
	RwV3d offset;
	int i;

	for (i = 0; i < 12; i++) {
		f32 spread = hintBallSpreadScale[0] * speed;
		PARTICLE_INSTANCE* ball;

		balls[i] = CreateInstance();
		ball     = balls[i];
		if (ball == NULL) {
			return;
		}
		ball->angle = (u16)(start + i * 0x10000 / 12);
		fn_80196050(&matrix, pos, 0);
		fn_80195A74(&matrix, &AxisY, angle->y, 1);
		fn_80195790(&matrix, &AxisZ, hintBallOne[0] - fn_800D7AE4(ball->angle + 0x4000),
		    fn_800D7B00(ball->angle + 0x4000), 1);
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
