#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s03WalkWayCreate, the factory the editor record for TObjS03WalkWay points
// at, in stage03D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// In the editor an all-zero box in the placement's parameter block becomes
// 150 by 10 by 50, the module's constants. The walkway's direction is the
// parameter block's first float along x, turned by the placement's angle in
// the order Z, X, Y on the matrix stack. It then sets up its collision through
// InitColli, the class's own virtual: the PS2 build lists it after
// EditOnChange in the vtable slots this one calls at 0x38, so it is declared
// first here. The parameter block pointer is read first, before the class
// name.

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

	TObjS03WalkWay(TObject* parent)
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
	virtual ~TObjS03WalkWay();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void InitColli();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void s03WalkWayCreate(void)
{
	new TObjS03WalkWay(lbl_8042C110);
}
