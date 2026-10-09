// TObjS04FloatWay, shared by rel/s04_floating_path_create.cpp, which defines S04_FLOATING_PATH_CTOR
// as inline so its factory inlines the constructor, and rel/s04_floating_path_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

struct S04FloatWayParam {
	u8 pad0[8];
	RwV3d extent; // 0x08
};

extern "C" char* CL_TObjS04FloatWay;
extern "C" CCL_INFO s04FloatWayCclInfo;
extern "C" const f32 s04FloatWayHalf[1];
extern "C" const f32 s04FloatWayZero[1];
extern "C" s16 s04FloatWayUnkB8;
extern "C" TObject* lbl_8042C110;

class TObjS04FloatWay : public TObject, public TObjSetObj, public C_COLLI
{
public:
	s16 unkB8;   // 0xB8
	u8 padBA[2]; // 0xBA

	TObjS04FloatWay(TObject* parent);
	virtual ~TObjS04FloatWay();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

S04_FLOATING_PATH_CTOR TObjS04FloatWay::TObjS04FloatWay(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjS04FloatWay;
	DispTime  = 0xBC;

	S04FloatWayParam* param = (S04FloatWayParam*)ObjParam->setData.setBuffer;

	if (info == NULL) {
		Init(&s04FloatWayCclInfo, 1, 4);
	}

	CCL_INFO* shape = info;
	f32 half        = s04FloatWayHalf[0];
	shape->a        = half * param->extent.x;
	shape->b        = half * param->extent.y;
	shape->c        = half * param->extent.z;
	shape->center.x = s04FloatWayZero[0];
	shape->center.y = half * param->extent.y;
	shape->center.z = half * param->extent.z;
	CalcRange();

	unkB8 = s04FloatWayUnkB8;
}
