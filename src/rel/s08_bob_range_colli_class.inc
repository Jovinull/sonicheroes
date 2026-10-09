// TObjS08BobRangeColli, shared by rel/s08_bob_range_colli_create.cpp and the units
// that define its out-of-line members. The constructor stays inline in the
// class: the factory inlines it.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

struct RangeColliParam {
	f32 radius; // 0x00
};

struct RangeColliRecord {
	s32 count; // 0x00
};

extern "C" char* CL_TObjS08BobRangeColli;
extern "C" CCL_INFO s08BobRangeColliCclInfo;
extern "C" TObject* lbl_8042C110;

class TObjS08BobRangeColli : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;  // 0xB8
	f32 radius; // 0xC4
	s32 unkC8;  // 0xC8

	TObjS08BobRangeColli(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjS08BobRangeColli;
		DispTime  = 0xCC;

		RangeColliParam* param = (RangeColliParam*)ObjParam->setData.setBuffer;

		pos    = ObjParam->setData.pos;
		radius = param->radius;
		unkC8  = -1;

		Init(&s08BobRangeColliCclInfo, 1, 4);
		info->a = radius;

		if (ObjParam->originalWork == NULL) {
			RangeColliRecord* record = new RangeColliRecord;
			ObjParam->originalWork   = record;
			record->count            = 0;
		}
	}
	virtual void Exec();
	virtual ~TObjS08BobRangeColli();
	virtual void EditOnChange(SETDATA_PARAM*);
};
