#include "types.h"

// TObjHawkMachineGun (the PS2 build's class), the gun object that drives the
// Egg Hawk's HAWK_MGUN: Close, the setters, Exec, Stop and Run. It is
// TMachineGun's twin (rel/machine_gun_control.cpp; TMachineGun's Close is
// the pawnReleaseBuffer of the symbols). Close stops the gun and lets Exec
// end the object once no bullet is left; the setters pass the bullet speed,
// the firing interval, the aim, the angle or the position on to the gun (when
// it has one) and keep their own copy. The aim position setter
// (hawkMachineGunSetAimPosition here) is not in the PS2 build.

#include "src/rel/hawk_mgun.inc"

class TObjHawkMachineGun
{
public:
	void Close();
	void SetBulletSpeed(f32 speed);
	void SetInterval(s32 interval);
	void SetVector(const RwV3d* vector);
	void SetAngle(const sAngle* angle);
	void SetPosition(const RwV3d* position);
	void Exec();
	void Stop();
	void Run();

	u8 unk00[0x4];   // 0x00
	u16 signal;      // 0x04
	u8 unk06[0x22];  // 0x06
	HAWK_MGUN* mgun; // 0x28
	s32 running;     // 0x2C
	RwV3d pos;       // 0x30
	sAngle angle;    // 0x3C
	RwV3d aim;       // 0x48
	u8 unk54[0x4];   // 0x54
	s32 state;       // 0x58
};

void TObjHawkMachineGun::Close()
{
	if (mgun != NULL) {
		mgun->Off();
	}
	running = 0;
	state   = 2;
}

void TObjHawkMachineGun::SetBulletSpeed(f32 speed)
{
	if (mgun != NULL) {
		mgun->bulletSpeed = speed;
	}
}

void TObjHawkMachineGun::SetInterval(s32 interval)
{
	if (mgun != NULL) {
		mgun->interval = interval;
	}
}

void TObjHawkMachineGun::SetVector(const RwV3d* vector)
{
	if (mgun != NULL) {
		mgun->SetAimVector(vector);
	}
	aim = *vector;
}

extern "C" void hawkMachineGunSetAimPosition(TObjHawkMachineGun* gun, const RwV3d* target)
{
	if (gun->mgun != NULL) {
		gun->mgun->SetAimPosition(target);
	}
}

void TObjHawkMachineGun::SetAngle(const sAngle* angle)
{
	if (mgun != NULL) {
		mgun->angle = *angle;
	}
	this->angle = *angle;
}

void TObjHawkMachineGun::SetPosition(const RwV3d* position)
{
	if (mgun != NULL) {
		mgun->pos = *position;
	}
	pos = *position;
}

void TObjHawkMachineGun::Exec()
{
	switch (state) {
		case 0:
		case 1:
			break;
		case 2:
			if (mgun->EmptyBulletNum()) {
				state = 3;
			}
			break;
		case 3:
			signal |= 1;
			break;
	}
}

void TObjHawkMachineGun::Stop()
{
	if (mgun != NULL) {
		mgun->Off();
	}
	running = 0;
}

void TObjHawkMachineGun::Run()
{
	if (mgun != NULL) {
		mgun->On();
	}
	running = 1;
}
