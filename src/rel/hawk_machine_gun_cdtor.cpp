#include "game/effect/eff_bomb.h"

// TObjHawkMachineGun's destructor, constructor and Create (the PS2 build's
// names), TMachineGun's (rel/machine_gun_cdtor.cpp) with the bullet model
// passed on. The destructor stops the gun and ends it. The constructor sets up
// a HAWK_MGUN at the given place with SetHawkMGun, firing at the given speed,
// with the gun stopped, at the origin and aiming down Z; Create inlines it.

#include "src/rel/hawk_mgun.inc"

extern "C" char* CL_TObjHawkMachineGun;
extern "C" const f32 hawkMachineGunZero[1];
extern "C" const f32 hawkMachineGunAimZ[1];

HAWK_MGUN* SetHawkMGun(
    TObject* parent, f32 speed, const RwV3d* place, const sAngle* turn, const RpClump* model);

// declared again here as the C++ class (rel/hawk_machine_gun_control.cpp has
// the plain layout); Exec comes first so that it is the key function and no
// unit of ours emits the vtable
class TObjHawkMachineGun : public TObject
{
public:
	virtual void Exec();
	virtual ~TObjHawkMachineGun();

	TObjHawkMachineGun(
	    TObject* parent, const RwV3d* place, const sAngle* turn, f32 speed, const RpClump* model);
	static TObjHawkMachineGun* Create(
	    TObject* parent, const RwV3d* place, const sAngle* turn, f32 speed, const RpClump* model);

	void Stop()
	{
		if (mgun != NULL) {
			mgun->Off();
		}
		running = 0;
	}

	HAWK_MGUN* mgun; // 0x28
	s32 running;     // 0x2C
	RwV3d pos;       // 0x30
	sAngle angle;    // 0x3C
	RwV3d aim;       // 0x48
	u8 unk54[0x4];   // 0x54
	s32 state;       // 0x58
}; // 0x5C

TObjHawkMachineGun::~TObjHawkMachineGun()
{
	if (mgun != NULL) {
		Stop();
		mgun->Signal |= 1;
		mgun = NULL;
	}
}

TObjHawkMachineGun::TObjHawkMachineGun(
    TObject* parent, const RwV3d* place, const sAngle* turn, f32 speed, const RpClump* model)
    : TObject(parent)
{
	ClassName = CL_TObjHawkMachineGun;
	DispTime  = sizeof(TObjHawkMachineGun);
	mgun      = SetHawkMGun(this, speed, place, turn, model);
	running   = 0;
	pos.x = pos.y = pos.z = hawkMachineGunZero[0];
	angle.x = angle.y = angle.z = 0;
	aim.x = aim.y = hawkMachineGunZero[0];
	aim.z         = hawkMachineGunAimZ[0];
	state         = 0;
}

TObjHawkMachineGun* TObjHawkMachineGun::Create(
    TObject* parent, const RwV3d* place, const sAngle* turn, f32 speed, const RpClump* model)
{
	return new TObjHawkMachineGun(parent, place, turn, speed, model);
}
