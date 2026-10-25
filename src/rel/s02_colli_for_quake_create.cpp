#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s02ColliForQuakeCreate, the factory rel/s02_colli_for_quake_register.cpp puts
// in the editor record: a new TObjS02Cquake (the class name its constructor
// stores). While the editor is on, a set data with no size gets 100 x 100 x 10,
// one with no strength gets 1 and one with no duration gets 60. It keeps the
// size, starts its collision block (its third base) with only the set data's
// Y angle and gives the set data a work word (cleared) when it has none. The
// allocation is a real new-expression of the class (rel/sample1_create.cpp).

// the set data's parameters (rel/s02_colli_for_quake_edit.cpp)
typedef struct S02ColliForQuakeParams {
	f32 f00; // 0x00
	f32 f04; // 0x04
	f32 f08; // 0x08
	f32 f0C; // 0x0C
	s32 f10; // 0x10
} S02ColliForQuakeParams;

extern "C" char* CL_TObjS02Cquake;
extern "C" const f32 s02ColliForQuakeBound0[1];
extern "C" const f32 s02ColliForQuakeDefaultSide;
extern "C" const f32 s02ColliForQuakeDefaultHeight;
extern "C" const f32 s02ColliForQuakeDefaultStrength;
extern "C" TObject* lbl_8042C110;

class TObjS02Cquake : public TObject, public TObjSetObj, public C_COLLI
{
public:
	s32 unkB8;  // 0xB8
	RwV3d size; // 0xBC
	u8 padC8[0x4];

	TObjS02Cquake(TObject* parent)
	    : TObject(parent)
	{
		S02ColliForQuakeParams* params = (S02ColliForQuakeParams*)ObjParam->setData.setBuffer;

		ClassName = CL_TObjS02Cquake;
		DispTime  = 0xCC;
		info      = NULL;
		if (OnEdit()) {
			if (*s02ColliForQuakeBound0 == params->f00 && *s02ColliForQuakeBound0 == params->f04
			    && *s02ColliForQuakeBound0 == params->f08) {
				params->f04 = params->f00 = s02ColliForQuakeDefaultSide;
				params->f08               = s02ColliForQuakeDefaultHeight;
			}
			if (*s02ColliForQuakeBound0 == params->f0C) {
				params->f0C = s02ColliForQuakeDefaultStrength;
			}
			if (params->f10 == 0) {
				params->f10 = 60;
			}
		}
		size.x = params->f00;
		size.y = params->f04;
		size.z = params->f08;
		ang.x = ang.z = 0;
		ang.y         = ObjParam->setData.ang.y;
		if (ObjParam->originalWork == NULL) {
			s32* work              = new s32;
			ObjParam->originalWork = work;
			*work                  = 0;
		}
		unkB8 = 0;
	}
	virtual ~TObjS02Cquake();
};

extern "C" void s02ColliForQuakeCreate(void)
{
	new TObjS02Cquake(lbl_8042C110);
}
