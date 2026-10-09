// TObjS03Train, shared by rel/s03_train_create.cpp, which defines S03_TRAIN_CTOR
// as inline so its factory inlines the constructor, and rel/s03_train_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

struct S03TrainParam {
	RwV3d extent; // 0x00
};

extern "C" char* CL_TObjS03Train;
extern "C" CCL_INFO s03TrainCclInfo;
extern "C" const f32 s03TrainZero[1];
extern "C" const f32 s03TrainWide[1];
extern "C" const f32 s03TrainHigh[1];
extern "C" TObject* lbl_8042C110;

class TObjS03Train : public TObject, public TObjSetObj, public C_COLLI
{
public:
	u8 unkB8; // 0xB8
	u8 unkB9; // 0xB9
	u8 padBA[2];
	s32 unkBC; // 0xBC

	TObjS03Train(TObject* parent);

	void SetColliParameter()
	{
		S03TrainParam* param = (S03TrainParam*)ObjParam->setData.setBuffer;

		if (info == NULL) {
			Init(&s03TrainCclInfo, 1, 4);
			CCL_INFO* shape = info;
			shape->a        = param->extent.x;
			shape->b        = param->extent.y;
			shape->c        = param->extent.z;
			CalcRange();
		}
	}

	virtual void Exec();
	virtual ~TObjS03Train();
	virtual void EditOnChange(SETDATA_PARAM*);
};

S03_TRAIN_CTOR TObjS03Train::TObjS03Train(TObject* parent)
    : TObject(parent)
{
	S03TrainParam* param = (S03TrainParam*)ObjParam->setData.setBuffer;

	ClassName = CL_TObjS03Train;
	DispTime  = 0xC0;

	if (OnEdit()) {
		if (s03TrainZero[0] == param->extent.x && s03TrainZero[0] == param->extent.y
		    && s03TrainZero[0] == param->extent.z) {
			param->extent.x = s03TrainWide[0];
			param->extent.y = s03TrainWide[0];
			param->extent.z = s03TrainHigh[0];
		}
	}

	unkB8 = 0;
	unkBC = 0;
	unkB9 = 0;
	SetColliParameter();
}
