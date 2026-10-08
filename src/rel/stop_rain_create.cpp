#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// stoprainCreate, the factory the editor record for TObjStopRain points at, in
// stage09D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form. C_COLLI is the third base, as in rel/warp_create.cpp.
//
// The placement's parameter block holds the box's three extents; the module's
// shape takes each halved, by the module's constant 0.5, before it goes to the
// collision base. The parameter block pointer is read first, before the class
// name, and the constant once.

struct StopRainParam {
	RwV3d extent; // 0x00
};

extern "C" char* CL_TObjStopRain;
extern "C" CCL_INFO stopRainCclInfo;
extern "C" const f32 stopRainHalf[1];
extern "C" TObject* lbl_8042C110;

class TObjStopRain : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;   // 0xB8
	sAngle ang;  // 0xC4
	u8 unkD0[4]; // 0xD0

	TObjStopRain(TObject* parent)
	    : TObject(parent)
	{
		StopRainParam* param = (StopRainParam*)ObjParam->setData.setBuffer;

		ClassName = CL_TObjStopRain;
		DispTime  = 0xD4;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;

		stopRainCclInfo.a = stopRainHalf[0] * param->extent.x;
		stopRainCclInfo.b = stopRainHalf[0] * param->extent.y;
		stopRainCclInfo.c = stopRainHalf[0] * param->extent.z;
		Init(&stopRainCclInfo, 1, 4);
	}
	virtual ~TObjStopRain();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void stoprainCreate(void)
{
	new TObjStopRain(lbl_8042C110);
}
