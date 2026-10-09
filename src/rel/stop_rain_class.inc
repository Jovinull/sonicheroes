// TObjStopRain, shared by rel/stop_rain_create.cpp, which defines STOP_RAIN_CTOR
// as inline so its factory inlines the constructor, and rel/stop_rain_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

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

	TObjStopRain(TObject* parent);
	virtual void Exec();
	virtual ~TObjStopRain();
	virtual void TDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
};

STOP_RAIN_CTOR TObjStopRain::TObjStopRain(TObject* parent)
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
