// TObjS04BallColli, shared by rel/s04_ball_colli_create.cpp, which defines S04_BALL_COLLI_CTOR
// as inline so its factory inlines the constructor, and rel/s04_ball_colli_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

struct S04BallColliParam {
	f32 radius; // 0x00
};

extern "C" char* CL_TObjS04BallColli;
extern "C" CCL_INFO s04BallColliCclInfo;
extern "C" const f32 s04BallColliZero[1];
extern "C" const f32 s04BallColliTen[1];
extern "C" TObject* lbl_8042C110;

class TObjS04BallColli : public TObject, public TObjSetObj, public C_COLLI
{
public:
	TObjS04BallColli(TObject* parent);
	virtual ~TObjS04BallColli();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

S04_BALL_COLLI_CTOR TObjS04BallColli::TObjS04BallColli(TObject* parent)
    : TObject(parent)
{
	S04BallColliParam* param = (S04BallColliParam*)ObjParam->setData.setBuffer;

	ClassName = CL_TObjS04BallColli;
	DispTime  = 0xB8;

	if (s04BallColliZero[0] == param->radius) {
		param->radius = s04BallColliTen[0];
	}

	Init(&s04BallColliCclInfo, 1, 4);
	info->a = param->radius;
	CalcRange();
	flag &= ~0x40;
}
