#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// objSetparticleCreate, the factory the editor record for TObjSetParticle
// points at.
//
// It is the same 75 instructions in the thirteen stage modules that share the
// engine core, at a different address in each, so each module's splits.txt
// names its own range.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form.
//
// The placement's parameter block holds the effect number in its first byte
// and a scale at 0x10. In the editor, an unset scale becomes 1 and an effect
// number outside 0 to 63 becomes 0. Numbers below 50 name one table of effects
// and the rest a second one, counted from 50; whichever starts the effect
// returns the handle kept at 0x30. Both get the placement's position and angle.
//
// The two floats are the module's own constants, 0 and 1, shared with the rest
// of the class's code, so they are read as externals rather than written as
// literals the compiler would place in this file.

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

	TObjSetParticle(TObject* parent)
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
	virtual ~TObjSetParticle();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void objSetparticleCreate(void)
{
	new TObjSetParticle(lbl_8042C110);
}
