// TObjSetParticle::Exec (the PS2 build's name), the same in the thirteen stage
// modules that share the engine core. A particle that has died is forgotten.
// Out of range or due to be killed, the object asks to be killed; while the
// game runs it follows its placement on an edit (a still particle is moved
// there), makes its particle again when the editor asks (types from 0x32 come
// from the second bank), and gives a live particle the placement's speed when
// that is not zero. The speed is built from the unit's own aggregate template
// (.rodata), as the retail does. The class is shared through
// obj_set_particle_class.inc.

#define OBJ_SET_PARTICLE_CTOR inline
#define OBJ_SET_PARTICLE_EDIT_FIRST
#include "src/rel/obj_set_particle_class.inc"

struct SetParticleEffect {
	u8 unk00[0x80];
	RwV3d pos;   // 0x80
	sAngle ang;  // 0x8C
	RwV3d speed; // 0x98

	inline void SetPosition(const RwV3d* newPos, const sAngle* newAng)
	{
		if (newPos != NULL) {
			pos = *newPos;
		}
		if (newAng != NULL) {
			ang = *newAng;
		}
	}
};

struct SetParticleSpeedParam {
	s8 type; // 0x00
	u8 pad01[0x3];
	RwV3d speed; // 0x04
};

typedef struct HintTableRow {
	u32 flags; // 0x00
	u8 unk04[0x48];
} HintTableRow; // 0x4C

typedef struct GameTable {
	u8 unk00[0x50];
	HintTableRow rows[1]; // 0x50
} GameTable;

extern "C" u8* lbl_8042C180;
extern "C" GameTable lbl_8029BBD0;
extern "C" s32 lbl_802408F8[];
extern "C" s32 fn_80017800(void* object);
extern "C" void fn_8005FD8C(void* particle, s32 arg);
extern "C" void* fn_8006298C(s32 type, RwV3d* pos, sAngle* ang);
extern "C" void* fn_800628D0(s32 type, RwV3d* pos, sAngle* ang);

void TObjSetParticle::Exec()
{
	if (particle != NULL && fn_80017800(particle) == 0) {
		particle = NULL;
	}
	SetParticleSpeedParam* param = (SetParticleSpeedParam*)ObjParam->setData.setBuffer;

	if (CheckRangeOut() || CheckMustKill()) {
		Signal |= 1;
		return;
	}
	if ((s8)lbl_8042C180[0x1F] != 0) {
		return;
	}
	if (OnEdit()) {
		SetParticleEffect* effect = (SetParticleEffect*)particle;

		if (effect != NULL && setParticleZero[0] == param->speed.x
		    && setParticleZero[0] == param->speed.y && setParticleZero[0] == param->speed.z) {
			effect->SetPosition(&ObjParam->setData.pos, &ObjParam->setData.ang);
		}
		if (lbl_8029BBD0.rows[lbl_802408F8[0]].flags & 0x100) {
			if (particle != NULL) {
				fn_8005FD8C(particle, 0);
			}
			if (param->type < 0x32) {
				particle = fn_8006298C(param->type, &ObjParam->setData.pos, &ObjParam->setData.ang);
			} else {
				particle = fn_800628D0(
				    param->type - 0x32, &ObjParam->setData.pos, &ObjParam->setData.ang);
			}
		}
	}
	if (particle != NULL
	    && !(setParticleZero[0] == *(volatile f32*)&param->speed.x
	        && setParticleZero[0] == param->speed.y && setParticleZero[0] == param->speed.z)) {
		RwV3d speed = { param->speed.x, param->speed.y, param->speed.z };

		// volatile is a reconstruction aid: the retail reads the particle and
		// the speed's x again rather than reusing them from the test.
		(*(SetParticleEffect* volatile*)&particle)->speed = speed;
	}
}
