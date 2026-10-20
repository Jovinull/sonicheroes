#include "types.h"

// TMachineGun (the PS2 build's class), the gun object that drives an
// ENEMY_MGUN: its setters, Exec, Stop and Run. The setters pass the aim, the
// position or the angle on to the gun (when it has one) and keep their own
// copy; the aim vector and angle setters (machineGunSetAimVector and
// machineGunSetAngle here) are not in the PS2 build. Exec ends the object
// once the stopped gun has no bullet left; Stop and Run switch the gun.

#include "src/rel/enemy_mgun.inc"

class TMachineGun
{
public:
	void SetAimPosition(const RwV3d* target);
	void SetPosition(const RwV3d* position);
	void Exec();
	void Stop();
	void Run();

	u8 unk00[0x4];    // 0x00
	u16 signal;       // 0x04
	u8 unk06[0x22];   // 0x06
	ENEMY_MGUN* mgun; // 0x28
	s32 running;      // 0x2C
	RwV3d pos;        // 0x30
	sAngle angle;     // 0x3C
	RwV3d aim;        // 0x48
	u8 unk54[0x4];    // 0x54
	s32 state;        // 0x58
};

extern "C" void machineGunSetAimVector(TMachineGun* gun, const RwV3d* vector)
{
	if (gun->mgun != NULL) {
		gun->mgun->SetAimVector(vector);
	}
	gun->aim = *vector;
}

extern "C" void machineGunSetAngle(TMachineGun* gun, const sAngle* angle)
{
	if (gun->mgun != NULL) {
		gun->mgun->angle = *angle;
	}
	gun->angle = *angle;
}

void TMachineGun::SetAimPosition(const RwV3d* target)
{
	if (mgun != NULL) {
		mgun->SetAimPosition(target);
	}
}

void TMachineGun::SetPosition(const RwV3d* position)
{
	if (mgun != NULL) {
		mgun->pos = *position;
	}
	pos = *position;
}

void TMachineGun::Exec()
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

void TMachineGun::Stop()
{
	if (mgun != NULL) {
		mgun->Off();
	}
	running = 0;
}

void TMachineGun::Run()
{
	if (mgun != NULL) {
		mgun->On();
	}
	running = 1;
}
