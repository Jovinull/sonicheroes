// ENEMY_MGUN (the PS2 build's class): the machine gun's bullets and muzzle
// flash, which TMachineGun drives; like ENEMY_SHOT it is a TObject with
// ground movement and a collision.

#ifndef ENEMY_MGUN_INC
#define ENEMY_MGUN_INC

#include "game/effect/eff_bomb.h"
#include "game/object.h"

// sMachineGunBullet (the PS2 build's struct): one bullet, flying along the
// gun's fire vector until it passes its range or its life runs out.
struct sMachineGunBullet {
	sMachineGunBullet();

	f32 speed; // 0x0
	f32 dist;  // 0x4
	f32 range; // 0x8
	s32 life;  // 0xC

	s32 Alive()
	{
		if (life < 0) {
			return 0;
		}
		if (range < dist) {
			return 0;
		}
		return 1;
	}

	void Move()
	{
		dist += speed;
		life--;
	}
};

// EmptyBulletNum's own unit returns a bool (no zero extension of the compare)
// while its callers test an int (cmpwi, not clrlwi + cmplwi): the unit that
// defines it sets ENEMY_MGUN_EMPTY_TYPE to bool.
#ifndef ENEMY_MGUN_EMPTY_TYPE
#define ENEMY_MGUN_EMPTY_TYPE s32
#endif

class ENEMY_MGUN : public TObject, public OBJ_MoveOnGround, public C_COLLI
{
public:
	// Exec comes first so that it is the key function: no unit of ours emits
	// the vtable, which stays in each module's data
	virtual void Exec();
	virtual ~ENEMY_MGUN();
	ENEMY_MGUN(TObject* parent);
	ENEMY_MGUN_EMPTY_TYPE EmptyBulletNum();
	void Off();
	void On();
	void CalcFireAngle();
	void CalcFireVector();
	void CalcBullet();

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
	s32 done;                      // 0x0E8
	s16 hits;                      // 0x0EC
	RwV3d pos;                     // 0x0F0
	RwV3d aim;                     // 0x0FC
	sAngle angle;                  // 0x108
	f32 size;                      // 0x114
	f32 speed;                     // 0x118
	u32 flags;                     // 0x11C
	u8 unk120[0x4];                // 0x120
	s32 bulletNum;                 // 0x124
	s32 unk128;                    // 0x128
	sMachineGunBullet bullets[32]; // 0x12C
	s32 unk32C;                    // 0x32C
	struct RpClump* clump;         // 0x330
	s32 active;                    // 0x334
	s32 unk338;                    // 0x338
}; // 0x33C

#endif
