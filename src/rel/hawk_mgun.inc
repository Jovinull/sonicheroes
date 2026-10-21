// HAWK_MGUN (the PS2 build's class): the Egg Hawk's machine gun, which
// TObjHawkMachineGun drives. Like ENEMY_MGUN (rel/enemy_mgun.inc) it is a
// TObject with ground movement and a collision, with the same layout up to the
// bullet count; its bullets carry their own collisions.

#ifndef HAWK_MGUN_INC
#define HAWK_MGUN_INC

#include "game/effect/eff_bomb.h"
#include "game/object.h"

extern "C" void fn_8003BF04(C_COLLI* colli, CCL_INFO* info, int count, u8 kind);
extern "C" const f32 hawkMGunZero[1];
extern "C" CCL_INFO hawkMGunCclInfo;

// bMachineGunBullet (the PS2 build's struct): one bullet with its own
// collision, flying along its velocity until its life runs out.
struct bMachineGunBullet : public C_COLLI {
	bMachineGunBullet();
	~bMachineGunBullet();
	void Init();
	bool Alive();
	void Move();

	RwV3d pos; // 0x88
	RwV3d vel; // 0x94
	s32 life;  // 0xA0
}; // 0xA4

// Init (the PS2 build's name): at rest at the origin, and the collision set up
// (one sphere, attribute bit 0x40 cleared) the first time. HAWK_MGUN::On and
// the constructor inline it; rel/hawk_mgun_bullet.cpp has the out-of-line copy
// (HAWK_MGUN_BULLET_INIT_INLINE empty).
#ifndef HAWK_MGUN_BULLET_INIT_INLINE
#define HAWK_MGUN_BULLET_INIT_INLINE inline
#endif

HAWK_MGUN_BULLET_INIT_INLINE void bMachineGunBullet::Init()
{
	f32 zero = hawkMGunZero[0];

	pos.x = pos.y = pos.z = zero;
	vel.x = vel.y = vel.z = zero;
	life                  = 0;
	if (info == NULL) {
		fn_8003BF04(this, &hawkMGunCclInfo, 1, 3);
		flag &= ~0x40;
	}
}

// EmptyBulletNum's own unit returns a bool while its callers test an int, as
// with ENEMY_MGUN (rel/enemy_mgun.inc)
#ifndef HAWK_MGUN_EMPTY_TYPE
#define HAWK_MGUN_EMPTY_TYPE s32
#endif

class HAWK_MGUN : public TObject, public OBJ_MoveOnGround, public C_COLLI
{
public:
	// declared first, and defined nowhere (HAWK_MGUN has no Debug of its own),
	// so that it is the key function: no unit of ours emits the vtable, which
	// stays in each module's data
	virtual void Debug();
	virtual void Exec();
	virtual ~HAWK_MGUN();
	HAWK_MGUN(TObject* parent);
	void Normal();
	void Move();
	void CalcBullet();
	virtual void PDisp();
	virtual void Disp();
	HAWK_MGUN_EMPTY_TYPE EmptyBulletNum();
	void Off();
	void On();
	void CalcFireAngle();
	static void SetBulletClump(RpClump* clump);

	static RpClump* pSrcClumpBullet;

	void SetFlagVectorHasBeenAlreadyCalculated() { flags |= 4; }

	// aims along the vector
	void SetAimVector(const RwV3d* vector)
	{
		aim = *vector;
		CalcFireAngle();
		SetFlagVectorHasBeenAlreadyCalculated();
	}

	// aims at the position, from the gun
	void SetAimPosition(const RwV3d* target)
	{
		aim.x = target->x - pos.x;
		aim.y = target->y - pos.y;
		aim.z = target->z - pos.z;
		CalcFireAngle();
		SetFlagVectorHasBeenAlreadyCalculated();
	}

	// OBJ_MoveOnGround at 0x028, C_COLLI at 0x060
	s32 done;                  // 0x0E8
	s16 hits;                  // 0x0EC
	RwV3d pos;                 // 0x0F0
	RwV3d aim;                 // 0x0FC
	sAngle angle;              // 0x108
	f32 size;                  // 0x114
	f32 speed;                 // 0x118
	u32 flags;                 // 0x11C
	f32 height;                // 0x120
	s32 bulletNum;             // 0x124
	s32 unk128;                // 0x128
	s32 interval;              // 0x12C
	f32 bulletSpeed;           // 0x130
	bMachineGunBullet bullets[40]; // 0x134
	u8 unk1AD4[0xC];           // 0x1AD4
	s32 active;                // 0x1AE0
};

#endif
