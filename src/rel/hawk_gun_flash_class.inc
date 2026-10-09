// TObjHawkGunFlash, shared by rel/hawk_gun_flash_create.cpp and the units
// that define its out-of-line members. The constructor stays inline in the
// class: the factory inlines it.

#include "game/effect/eff_bomb.h"
#include "game/enemy/e_database.h"

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
	virtual void Exec();
	virtual ~TObjHawkGunFlash();
	virtual void TDisp();

	static TObjHawkGunFlash* Create(TObject* parent, RwV3d* position, sAngle* angle);
};
