#include "game/effect/eff_bomb.h"

// TMachineGun's destructor, constructor and Create (the PS2 build's names).
// The destructor closes the gun: it stops it and ends it. The constructor sets
// up an ENEMY_MGUN at the given place, firing at the given speed, with the
// gun stopped, at the origin and aiming down Z; Create inlines it.

#include "src/rel/enemy_mgun.inc"

extern "C" char* CL_TMachineGun;
extern "C" const f32 machineGunZero[1];
extern "C" const f32 machineGunAimZ[1];

ENEMY_MGUN* SetEnemyMGun(TObject* parent, f32 speed, const RwV3d* place, const sAngle* turn);

// declared again here as the C++ class (rel/machine_gun_control.cpp has the
// plain layout); Exec comes first so that it is the key function and no unit
// of ours emits the vtable
class TMachineGun : public TObject
{
public:
	virtual void Exec();
	virtual ~TMachineGun();

	TMachineGun(TObject* parent, const RwV3d* place, const sAngle* turn, f32 speed);
	static TMachineGun* Create(TObject* parent, const RwV3d* place, const sAngle* turn, f32 speed);

	void Stop()
	{
		if (mgun != NULL) {
			mgun->Off();
		}
		running = 0;
	}

	void Close()
	{
		if (mgun != NULL) {
			Stop();
			mgun->Signal |= 1;
			mgun = NULL;
		}
	}

	ENEMY_MGUN* mgun; // 0x28
	s32 running;      // 0x2C
	RwV3d pos;        // 0x30
	sAngle angle;     // 0x3C
	RwV3d aim;        // 0x48
	u8 unk54[0x4];    // 0x54
	s32 state;        // 0x58
}; // 0x5C

TMachineGun::~TMachineGun()
{
	Close();
}

TMachineGun::TMachineGun(TObject* parent, const RwV3d* place, const sAngle* turn, f32 speed)
    : TObject(parent)
{
	ClassName = CL_TMachineGun;
	DispTime  = sizeof(TMachineGun);
	mgun      = SetEnemyMGun(this, speed, place, turn);
	running   = 0;
	pos.x = pos.y = pos.z = machineGunZero[0];
	angle.x = angle.y = angle.z = 0;
	aim.x = aim.y = machineGunZero[0];
	aim.z         = machineGunAimZ[0];
	state         = 0;
}

TMachineGun* TMachineGun::Create(TObject* parent, const RwV3d* place, const sAngle* turn, f32 speed)
{
	return new TMachineGun(parent, place, turn, speed);
}
