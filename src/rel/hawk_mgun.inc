// HAWK_MGUN (the PS2 build's class): the Egg Hawk's machine gun, which
// TObjHawkMachineGun drives. Like ENEMY_MGUN (rel/enemy_mgun.inc) it is a
// TObject with ground movement and a collision, with the same layout up to the
// bullet count; its bullets carry their own collisions.

#ifndef HAWK_MGUN_INC
#define HAWK_MGUN_INC

#include "game/effect/eff_bomb.h"
#include "game/object.h"

// EmptyBulletNum's own unit returns a bool while its callers test an int, as
// with ENEMY_MGUN (rel/enemy_mgun.inc)
#ifndef HAWK_MGUN_EMPTY_TYPE
#define HAWK_MGUN_EMPTY_TYPE s32
#endif

class HAWK_MGUN : public TObject, public OBJ_MoveOnGround, public C_COLLI
{
public:
	// Exec comes first so that it is the key function: no unit of ours emits
	// the vtable, which stays in each module's data
	virtual void Exec();
	virtual ~HAWK_MGUN();
	HAWK_MGUN_EMPTY_TYPE EmptyBulletNum();
	void Off();
	void On();
	void CalcFireAngle();

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
	f32 unk118;                // 0x118
	u32 flags;                 // 0x11C
	f32 height;                // 0x120
	s32 bulletNum;             // 0x124
	s32 unk128;                // 0x128
	s32 interval;              // 0x12C
	f32 speed;                 // 0x130
	u8 bullets[40][0xA4];      // 0x134
	u8 unk1AD4[0xC];           // 0x1AD4
	s32 active;                // 0x1AE0
};

#endif
