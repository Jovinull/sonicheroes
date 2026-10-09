// TObjS03WalkWay, shared by rel/s03_walk_way_create.cpp, which defines S03_WALK_WAY_CTOR
// as inline so its factory inlines the constructor, and rel/s03_walk_way_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

struct S03WalkWayParam {
	f32 length;   // 0x00
	RwV3d extent; // 0x04
};

// The matrix stack helpers, declared here because game/matrix.h brings its
// own RwV3d.
struct RwMatrixTag;
void PushUnitMatrix();
void PopMatrixEx();
void RotateX(RwMatrixTag*, s32);
void RotateY(RwMatrixTag*, s32);
void RotateZ(RwMatrixTag*, s32);
void CalcVector(const RwMatrixTag*, const RwV3d*, RwV3d*);

extern "C" char* CL_TObjS03WalkWay;
extern "C" const f32 s03WalkWayZero[1];
extern "C" const f32 s03WalkWayLength[1];
extern "C" const f32 s03WalkWayHeight[1];
extern "C" const f32 s03WalkWayWidth[1];
extern "C" TObject* lbl_8042C110;

class TObjS03WalkWay : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;  // 0xB8
	sAngle ang; // 0xC4
	RwV3d dir;  // 0xD0

	TObjS03WalkWay(TObject* parent);
	virtual void Exec();
	virtual ~TObjS03WalkWay();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void InitColli();
	virtual void EditOnChange(SETDATA_PARAM*);
};

S03_WALK_WAY_CTOR TObjS03WalkWay::TObjS03WalkWay(TObject* parent)
    : TObject(parent)
{
	S03WalkWayParam* param = (S03WalkWayParam*)ObjParam->setData.setBuffer;

	ClassName = CL_TObjS03WalkWay;
	DispTime  = 0xDC;

	if (OnEdit()) {
		if (s03WalkWayZero[0] == param->extent.x && s03WalkWayZero[0] == param->extent.y
		    && s03WalkWayZero[0] == param->extent.z) {
			param->extent.x = s03WalkWayLength[0];
			param->extent.y = s03WalkWayHeight[0];
			param->extent.z = s03WalkWayWidth[0];
		}
	}

	pos = ObjParam->setData.pos;
	ang = ObjParam->setData.ang;

	dir.x = param->length;
	dir.y = dir.z = s03WalkWayZero[0];

	PushUnitMatrix();
	RotateZ(NULL, ang.z);
	RotateX(NULL, ang.x);
	RotateY(NULL, ang.y);
	CalcVector(NULL, &dir, &dir);
	PopMatrixEx();

	InitColli();
}
