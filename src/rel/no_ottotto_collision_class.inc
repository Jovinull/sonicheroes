// TObjSetNoOttottoCollision, shared by rel/no_ottotto_collision_create.cpp, which defines NO_OTTOTTO_COLLISION_CTOR
// as inline so its factory inlines the constructor, and rel/no_ottotto_collision_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

struct NoOttottoParam {
	s32 shape; // 0x00
	f32 a;     // 0x04
	f32 b;     // 0x08
	f32 c;     // 0x0C
};

extern "C" char* CL_TObjSetNoOttottoCollision;
extern "C" CCL_INFO noOttottoCclInfo[2];
extern "C" TObject* lbl_8042C110;

class TObjSetNoOttottoCollision : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;  // 0xB8
	sAngle ang; // 0xC4

	TObjSetNoOttottoCollision(TObject* parent);
	virtual void Exec();
	virtual ~TObjSetNoOttottoCollision();
	virtual void TDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
};

NO_OTTOTTO_COLLISION_CTOR TObjSetNoOttottoCollision::TObjSetNoOttottoCollision(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjSetNoOttottoCollision;
	DispTime  = 0xD0;

	NoOttottoParam* param = (NoOttottoParam*)ObjParam->setData.setBuffer;
	pos                   = ObjParam->setData.pos;
	ang                   = ObjParam->setData.ang;

	noOttottoCclInfo[param->shape].a = param->a;
	noOttottoCclInfo[param->shape].b = param->b;
	noOttottoCclInfo[param->shape].c = param->c;
	Init(&noOttottoCclInfo[param->shape], 1, 4);
}
