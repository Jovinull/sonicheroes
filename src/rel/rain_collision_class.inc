// TObjRainCollision, shared by rel/rain_collision_create.cpp, which defines RAIN_COLLISION_CTOR
// as inline so its factory inlines the constructor, and rel/rain_collision_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

struct RainCollisionParam {
	f32 radius; // 0x00
};

extern "C" char* CL_TObjRainCollision;
extern "C" CCL_INFO rainCollisionCclInfo;
extern "C" TObject* lbl_8042C110;

class TObjRainCollision : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;  // 0xB8
	sAngle ang; // 0xC4

	TObjRainCollision(TObject* parent);
	virtual void Exec();
	virtual ~TObjRainCollision();
	virtual void EditOnChange(SETDATA_PARAM*);
};

RAIN_COLLISION_CTOR TObjRainCollision::TObjRainCollision(TObject* parent)
    : TObject(parent)
{
	RainCollisionParam* param = (RainCollisionParam*)ObjParam->setData.setBuffer;

	ClassName = CL_TObjRainCollision;
	DispTime  = 0xD0;

	pos = ObjParam->setData.pos;
	ang = ObjParam->setData.ang;

	Init(&rainCollisionCclInfo, 1, 4);
	info->a = param->radius;
	CalcRange();
}
