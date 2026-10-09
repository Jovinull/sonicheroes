// TObjSetParticle, shared by rel/obj_set_particle_create.cpp, which defines OBJ_SET_PARTICLE_CTOR
// as inline so its factory inlines the constructor, and rel/obj_set_particle_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

struct SetParticleParam {
	s8 type; // 0x00
	u8 pad01[0xF];
	f32 scale; // 0x10
};

extern "C" char* CL_TObjSetParticle;
extern "C" const f32 setParticleZero[1];
extern "C" const f32 setParticleOne[1];
extern "C" TObject* lbl_8042C110;
extern "C" void* fn_800627BC(s32 type, RwV3d* pos, sAngle* ang);
extern "C" void* fn_80062720(s32 type, RwV3d* pos, sAngle* ang);

class TObjSetParticle : public TObject, public TObjSetObj
{
public:
	void* particle; // 0x30

	TObjSetParticle(TObject* parent);
	virtual void Exec();
	virtual ~TObjSetParticle();
	virtual void EditOnChange(SETDATA_PARAM*);
};

OBJ_SET_PARTICLE_CTOR TObjSetParticle::TObjSetParticle(TObject* parent)
    : TObject(parent)
{
	SetParticleParam* param = (SetParticleParam*)ObjParam->setData.setBuffer;

	ClassName = CL_TObjSetParticle;
	DispTime  = 0x34;

	if (OnEdit()) {
		if (setParticleZero[0] == param->scale) {
			param->scale = setParticleOne[0];
		}
		if (param->type < 0 || param->type >= 0x40) {
			param->type = 0;
		}
	}
	if (param->type < 0x32) {
		particle = fn_800627BC(param->type, &ObjParam->setData.pos, &ObjParam->setData.ang);
	} else {
		particle
		    = fn_80062720(param->type - 0x32, &ObjParam->setData.pos, &ObjParam->setData.ang);
	}
}
