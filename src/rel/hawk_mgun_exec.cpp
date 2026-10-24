#include "types.h"

// HAWK_MGUN's Exec, destructor and CalcFireAngle (the PS2 build's names).
// Exec ends the gun (its collision switched off) once its owner is gone;
// otherwise, unless the game is paused, it moves the bullets while the gun is
// alive and counts the frames. CalcFireAngle is ENEMY_MGUN's
// (rel/enemy_mgun_calc_fire_angle.cpp).

#include "src/rel/hawk_mgun.inc"

extern "C" TObject* lbl_8042C114;
extern "C" u8* lbl_8042C180;
extern "C" s32 fn_80017800(TObject* object);
extern "C" const f32 hawkMGunRadToAngle[1];

extern "C" f32 fn_801991B4(RwV3d* v);
extern "C" double asin(double x);
extern "C" double atan2(double y, double x);

void HAWK_MGUN::Exec()
{
	if (Parent != lbl_8042C114 && fn_80017800(Parent) == 0) {
		info->attr |= 0x10;
		Signal |= 1;
		return;
	}
	if ((s8)lbl_8042C180[0x1F] != 0) {
		return;
	}
	// a switch with only the first case: an if gives a single beq where the
	// retail branches into the case and jumps over it
	switch (done) {
		case 0:
			if (fn_80017800(this) != 0) {
				Normal();
			}
			break;
	}
	hits++;
}

HAWK_MGUN::~HAWK_MGUN() { }

void HAWK_MGUN::CalcFireAngle()
{
	if (fn_801991B4(&aim) > hawkMGunZero[0]) {
		angle.x = hawkMGunRadToAngle[0] * (f32)asin(-aim.y / fn_801991B4(&aim));
		angle.y = hawkMGunRadToAngle[0] * (f32)atan2(aim.x, aim.z);
		angle.z = 0;
	} else {
		angle.x = angle.y = angle.z = 0;
	}
}
