#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s12doorColliObjectCreate, the factory the editor record for TObjS12DoorRangeColli points
// at, in stage11D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// The placement gives the position and, in the first word of its parameter
// block, the radius the module's shape takes. The first range collision of a
// placement also leaves a one-word record on it, built with the global operator
// new and cleared.

struct RangeColliParam {
	f32 radius; // 0x00
};

struct RangeColliRecord {
	s32 count; // 0x00
};

extern "C" char* CL_TObjS12DoorRangeColli;
extern "C" CCL_INFO s12DoorRangeColliCclInfo;
extern "C" TObject* lbl_8042C110;

class TObjS12DoorRangeColli : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;  // 0xB8
	f32 radius; // 0xC4
	s32 unkC8;  // 0xC8

	TObjS12DoorRangeColli(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjS12DoorRangeColli;
		DispTime  = 0xCC;

		RangeColliParam* param = (RangeColliParam*)ObjParam->setData.setBuffer;

		pos    = ObjParam->setData.pos;
		radius = param->radius;
		unkC8  = -1;

		Init(&s12DoorRangeColliCclInfo, 1, 4);
		info->a = radius;

		if (ObjParam->originalWork == NULL) {
			RangeColliRecord* record = new RangeColliRecord;
			ObjParam->originalWork   = record;
			record->count            = 0;
		}
	}
	virtual ~TObjS12DoorRangeColli();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void s12doorColliObjectCreate(void)
{
	new TObjS12DoorRangeColli(lbl_8042C110);
}
