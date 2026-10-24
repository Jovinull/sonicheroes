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

	s32 Alive();

	void Move();
};

// Alive and Move (the PS2 build's names), which the gun inlines;
// rel/enemy_mgun_bullet_alive.cpp has the out-of-line copies
// (ENEMY_MGUN_BULLET_ALIVE_INLINE empty)
#ifndef ENEMY_MGUN_BULLET_ALIVE_INLINE
#define ENEMY_MGUN_BULLET_ALIVE_INLINE inline
#endif

ENEMY_MGUN_BULLET_ALIVE_INLINE s32 sMachineGunBullet::Alive()
{
	if (life < 0) {
		return 0;
	}
	if (range < dist) {
		return 0;
	}
	return 1;
}

ENEMY_MGUN_BULLET_ALIVE_INLINE void sMachineGunBullet::Move()
{
	dist += speed;
	life--;
}

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
	void Init(const RwV3d* place, const sAngle* turn);

	void SetFlagVectorHasBeenAlreadyCalculated() { flags |= 4; }
	void SetFlagToCheckGround() { flags |= 1; }
	void ClearFlagToCheckGround() { flags &= ~1; }

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
	f32 height;                    // 0x120
	s32 bulletNum;                 // 0x124
	s32 unk128;                    // 0x128
	sMachineGunBullet bullets[32]; // 0x12C
	RpClump* model;                // 0x32C
	struct RpClump* clump;         // 0x330
	s32 active;                    // 0x334
	s32 unk338;                    // 0x338
}; // 0x33C

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

// CalcFireVector (the PS2 build's name): the aim vector from the firing
// angles, the bullet speed along Z turned by the pitch and then the yaw. Init
// inlines it; rel/enemy_mgun_calc_fire_vector.cpp has the out-of-line copy
// (ENEMY_MGUN_CALC_FIRE_VECTOR_INLINE empty).
#ifndef ENEMY_MGUN_CALC_FIRE_VECTOR_INLINE
#define ENEMY_MGUN_CALC_FIRE_VECTOR_INLINE inline
#endif

ENEMY_MGUN_CALC_FIRE_VECTOR_INLINE void ENEMY_MGUN::CalcFireVector()
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

#include "game/enemy/e_database.h"

extern "C" char* CL_EnemyMGun;
extern "C" CCL_INFO enemyMGunCclInfo[];
extern "C" const f32 enemyMGunSpeed[1];
extern "C" const f32 enemyMGunSize[1];
extern "C" const f32 enemyMGunRangePad[1];

extern "C" void* memset(void* dst, s32 value, u32 size);
extern "C" RpClump* fn_80150588(RpClump* clump);
void objRpClumpForAllGeometrysToIgnoreLights(RpClump* clump);

// The constructor and Init, which SetEnemyMGun inlines;
// rel/enemy_mgun_ctor.cpp and rel/enemy_mgun_init.cpp have the out-of-line
// copies (ENEMY_MGUN_CTOR_INLINE and ENEMY_MGUN_INIT_INLINE empty). The
// constructor is like ENEMY_SHOT's: a collision of one sphere (attribute bit
// 0x40 cleared), the bullet speed and size, and the gun stopped with no
// models. Init places and turns the gun, sizes its collision for the bullet
// speed, works out its fire vector, clears the bullets, and takes the common
// enemy file's models 8 (as it is) and 9 (a copy), both drawn without lights.
#ifndef ENEMY_MGUN_CTOR_INLINE
#define ENEMY_MGUN_CTOR_INLINE inline
#endif
#ifndef ENEMY_MGUN_INIT_INLINE
#define ENEMY_MGUN_INIT_INLINE inline
#endif

ENEMY_MGUN_CTOR_INLINE ENEMY_MGUN::ENEMY_MGUN(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_EnemyMGun;
	DispTime  = sizeof(ENEMY_MGUN);
	hits      = 0;
	done      = 0;
	C_COLLI::Init(enemyMGunCclInfo, 1, 3);
	flag &= ~0x40;
	speed     = enemyMGunSpeed[0];
	size      = enemyMGunSize[0];
	radObject = enemyMGunOne[0];
	active    = 0;
	unk338    = 0;
	model     = NULL;
	clump     = NULL;
}

ENEMY_MGUN_INIT_INLINE void ENEMY_MGUN::Init(const RwV3d* place, const sAngle* turn)
{
	pos.x = place->x;
	pos.y = place->y;
	pos.z = place->z;
	angle = *turn;
	SetRange(enemyMGunRangePad[0] + speed);
	CalcFireVector();
	posCenter.x = pos.x;
	posCenter.y = pos.y;
	posCenter.z = pos.z;
	unk128      = 4;
	bulletNum   = 0;
	memset(bullets, 0, sizeof(bullets));
	model = TEnemyDataBase::GetInstance()->SearchClump(ENEMY_DB_COMMON, 8);
	if (model != NULL) {
		objRpClumpForAllGeometrysToIgnoreLights(model);
	}
	RpClump* source = TEnemyDataBase::GetInstance()->SearchClump(ENEMY_DB_COMMON, 9);
	if (source != NULL) {
		clump = fn_80150588(source);
		objRpClumpForAllGeometrysToIgnoreLights(clump);
	}
}

#endif
