#include "game/effect/eff_bomb.h"
#include "game/enemy/e_database.h"

// TObjHawkGunFlash::Create, the static factory the PS2 build names
// Create__16TObjHawkGunFlashFP7TObjectP5RwV3dP6sAngle: the muzzle flash of the
// Egg Hawk's gun, in stage01D and stage07D. It returns the new object.
//
// The allocation is a real new-expression of the C++ class with its
// constructor inlined; the arguments live in saved registers across the
// allocation, which is why this one keeps the object in r28. The class has a
// single base and sets neither a class name nor a size.
//
// The constructor takes the flash's model from the enemy database (the common
// set, entry 9) through TEnemyDataBase::GetInstance, which creates the database
// on first use, makes it ignore lights, keeps its first two atomics, and copies
// the position and angle it is given. The running flag is cleared twice, once
// at the top and once at the end, as the original does.

struct RpAtomic;

RpAtomic* objRpClumpGetAtomic(RpClump*, RpAtomic*);
void objRpClumpForAllGeometrysToIgnoreLights(RpClump*);

class TObjHawkGunFlash : public TObject
{
public:
	s32 unk28;        // 0x28
	s32 running;      // 0x2C
	s32 unk30;        // 0x30
	s32 unk34;        // 0x34
	RwV3d pos;        // 0x38
	sAngle ang;       // 0x44
	RpClump* clump;   // 0x50
	RpAtomic* flash;  // 0x54
	RpAtomic* flash2; // 0x58

	TObjHawkGunFlash(TObject* parent, RwV3d* position, sAngle* angle)
	    : TObject(parent)
	{
		running = 0;
		clump   = TEnemyDataBase::GetInstance()->SearchClump(ENEMY_DB_COMMON, 9);
		if (clump != NULL) {
			objRpClumpForAllGeometrysToIgnoreLights(clump);
			flash  = objRpClumpGetAtomic(clump, NULL);
			flash2 = objRpClumpGetAtomic(clump, flash);
		}
		unk30 = unk34 = 0;
		pos           = *position;
		ang           = *angle;
		running       = 0;
	}
	virtual ~TObjHawkGunFlash();
	virtual void Exec();
	virtual void TDisp();

	static TObjHawkGunFlash* Create(TObject* parent, RwV3d* position, sAngle* angle);
};

TObjHawkGunFlash* TObjHawkGunFlash::Create(TObject* parent, RwV3d* position, sAngle* angle)
{
	return new TObjHawkGunFlash(parent, position, angle);
}
