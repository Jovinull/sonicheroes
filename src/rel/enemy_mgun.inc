// ENEMY_MGUN (the PS2 build's class): the machine gun's bullets and muzzle
// flash, which TMachineGun drives. Declared with the fields its small members
// use; its virtual members (Exec, TDisp, the destructor) are elsewhere.

#ifndef ENEMY_MGUN_INC
#define ENEMY_MGUN_INC

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

struct EnemyMGunFlash {
	u8 unk00[0x4]; // 0x00
	u32 flags;     // 0x04
};

// EmptyBulletNum's own unit returns a bool (no zero extension of the compare)
// while its callers test an int (cmpwi, not clrlwi + cmplwi): the unit that
// defines it sets ENEMY_MGUN_EMPTY_TYPE to bool.
#ifndef ENEMY_MGUN_EMPTY_TYPE
#define ENEMY_MGUN_EMPTY_TYPE s32
#endif

class ENEMY_MGUN
{
public:
	ENEMY_MGUN_EMPTY_TYPE EmptyBulletNum();
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

	u8 unk000[0x70];       // 0x000
	EnemyMGunFlash* flash; // 0x070
	u8 unk074[0x7C];       // 0x074
	RwV3d pos;             // 0x0F0
	RwV3d aim;             // 0x0FC
	sAngle angle;          // 0x108
	u8 unk114[0x8];        // 0x114
	u32 flags;             // 0x11C
	u8 unk120[0x4];        // 0x120
	s32 bulletNum;         // 0x124
	s32 unk128;            // 0x128
	u8 bullets[0x200];     // 0x12C
	u8 unk32C[0x8];        // 0x32C
	s32 active;            // 0x334
};

#endif
