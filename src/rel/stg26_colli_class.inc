// TObjStg26Colli, stage26D's collision marker, shared by
// rel/stg26_colli_cp_create.cpp and rel/stg26_colli_cc_create.cpp: its
// constructor (inlined into both factories) copies the set data's position
// and angle and, when the set data has a parameter block, its two words and
// its radius, at least the module's minimum. The minimum is read through a
// pointer in the comparison, as notes/tools/clampgen.py writes it: that is
// what loads the radius into f1 and the minimum into f0.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// the set data's parameters
struct Stg26ColliParam {
	f32 radius; // 0x00
	s32 a;      // 0x04
	s32 b;      // 0x08
};

extern "C" char* CL_TObjStg26Colli;
extern "C" const f32 stg26ColliMinRadius;

class TObjStg26Colli : public TObject, public TObjSetObj
{
public:
	RwV3d pos;  // 0x30
	sAngle ang; // 0x3C
	f32 radius; // 0x48
	s32 a;      // 0x4C
	s32 b;      // 0x50

	TObjStg26Colli(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjStg26Colli;
		DispTime  = 0x54;

		SETOBJ_PARAM* objParam = ObjParam;

		if (objParam != NULL) {
			Stg26ColliParam* param = (Stg26ColliParam*)objParam->setData.setBuffer;

			pos = ObjParam->setData.pos;
			ang = ObjParam->setData.ang;
			if (param != NULL) {
				const f32* limit;

				a      = param->a;
				b      = param->b;
				radius = param->radius;
				if (radius < *(limit = &stg26ColliMinRadius)) {
					radius = *limit;
				}
			}
		}
	}
	virtual ~TObjStg26Colli();
};
